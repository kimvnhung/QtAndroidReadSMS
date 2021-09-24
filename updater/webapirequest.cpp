#include "webapirequest.h"

#include <QDomDocument>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslKey>
#include <QUrlQuery>


const QString WebAPIRequest::AUTOFARMER_CERTIFICATE_PATH = "assets:/approval-api.pfx";
const QString WebAPIRequest::AUTOLIKE_CERTIFICATE_PATH = "assets:/approval.pfx";
const QString WebAPIRequest::MT_CERTIFICATE_PATH = "assets:/approval-mt.pfx";
const QString WebAPIRequest::AUTOFARMER_PASS = "approval-api";
const QString WebAPIRequest::AUTOLIKE_PASS = "approval";
const QString WebAPIRequest::MT_PASS = "approval";

bool WebAPIRequest::isWaitingResponse = false;
WebAPIRequest::RequestQueueItem* WebAPIRequest::currentRequestItem = nullptr;

WebAPIRequest::WebAPIRequest(QObject *parent) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &WebAPIRequest::onNetworkResponsed);

    anotherManager = new QNetworkAccessManager(this);
    connect(anotherManager, &QNetworkAccessManager::finished, [](QNetworkReply *reply){
       LOGD("Another reply");
       LOGD("%s",reply->readAll().data());
    });

    requestQueue = QList<RequestQueueItem*>();

    //load cert
    if(loadPfxCertificate(AUTOLIKE_CERTIFICATE_PATH,AUTOLIKE_PASS)){
        qDebug()<<"import autolike";
    }

    if(loadPfxCertificate(AUTOFARMER_CERTIFICATE_PATH,AUTOFARMER_PASS)){
        qDebug()<<"Imported auto farm";
    }

    if(loadPfxCertificate(MT_CERTIFICATE_PATH,MT_PASS)){
        qDebug()<<"Imported MT";
    }
}

WebAPIRequest::~WebAPIRequest()
{
    if(manager != nullptr){
        delete manager;
    }

}

//publics
void WebAPIRequest::setBody(QString body)
{
    this->body = body;
}


bool WebAPIRequest::loadPfxCertificate(QString certFilename, QString passphrase) {

    QFile certFile(certFilename);
    certFile.open(QFile::ReadOnly);
    QSslCertificate certificate;
    QSslKey key;
    QList<QSslCertificate> importedCerts;
    qDebug()<<__FUNCTION__<<__LINE__;
    bool imported = QSslCertificate::importPkcs12(&certFile, &key, &certificate, &importedCerts, QByteArray::fromStdString(passphrase.toStdString()));

    certFile.close();

    qDebug() << "Imported cert:" << imported;

    if (imported) {
        QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
        QList<QSslCertificate> certs = sslConfig.caCertificates();
        QList<QSslCertificate> localCerts = sslConfig.localCertificateChain();
        localCerts.append(certificate);
        certs.append(importedCerts);

        sslConfig.setLocalCertificateChain(localCerts);
        sslConfig.setCaCertificates(certs);
        sslConfig.setPrivateKey(key);
        if(certFilename == AUTOFARMER_CERTIFICATE_PATH){
            AUTOFARMER_SSL_CONF = sslConfig;
        }else if(certFilename == AUTOLIKE_CERTIFICATE_PATH){
            AUTOLIKE_SSL_CONF = sslConfig;
        }else {
            MT_SSL_CONF = sslConfig;
        }
    }

    return imported;
}

void WebAPIRequest::sendReport(Transaction *transaction)
{
    QNetworkRequest request;
    QUrl url = QUrl("https://script.google.com/macros/s/AKfycbyYdD0A0koNfGuN4PU4cocGwtTQkA9-3lrGdRVK2OlM6gbicYSaGf6q0Q/exec");
    QUrlQuery query;
    query.addQueryItem("date",QDateTime::currentDateTime().toString("yyyy/MM/dd HH:mm"));
    query.addQueryItem("key",transaction->getCode());
    query.addQueryItem("amount",QString::number(transaction->getValue()));
    query.addQueryItem("success",transaction->getStatus() == Transaction::ACCEPTED?"OK":"Failed");
    query.addQueryItem("smsbody",transaction->getSmsContent());
    query.addQueryItem("sheet_name",transaction->getCode().contains("MT")?"M1":"gicungduoc");

    url.setQuery(query);

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    anotherManager->get(request);
}

QNetworkRequest WebAPIRequest::getRequest()
{
    QNetworkRequest request;
    if(body.toUpper().contains("ALIKE")){
        request.setUrl(QUrl("https://adminapi-autolike.congaubeo.us/api/v1/transactions/active"));
        request.setRawHeader("Authorization","Basic Y29uZ2F1YmVvQDEyMzpjb25nYXViZW9AMTIz");
        if(!AUTOLIKE_SSL_CONF.isNull()){
            request.setSslConfiguration(AUTOLIKE_SSL_CONF);
        }
    }else if(body.toUpper().contains("AFARM")){
        request.setUrl(QUrl("https://approval-api.autofarmer.net/v1/transactions/active"));// without ID
        request.setRawHeader("Cache-Control","No-cache");
        if(!AUTOFARMER_SSL_CONF.isNull()){
            request.setSslConfiguration(AUTOFARMER_SSL_CONF);
        }
    }else if(body.toUpper().contains("MT")){
        request.setUrl(QUrl("https://approval.mottrieu.com/api/v1/transactions/active"));
        request.setRawHeader("Authorization","Basic Y29uZ2F1YmVvQDEyMzpjb25nYXViZW9AMTIz");
        if(!AUTOLIKE_SSL_CONF.isNull()){
            request.setSslConfiguration(MT_SSL_CONF);
        }
    }
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Mobile-Secret-Key","3953390b-42bb-11eb-9f8b-1111914b71be");
    return request;
}

void WebAPIRequest::addPostRequest(QString body)
{
    this->setBody(body);
    QNetworkRequest request = getRequest();
    requestQueue.append(new RequestQueueItem(request,body));
    body = "";
}

void WebAPIRequest::postAsync()
{
    if(!isWaitingResponse
            && requestQueue.size() > 0){
        LOGD("");
        manager->post(requestQueue.first()->request,requestQueue.first()->body.toUtf8());
        currentRequestItem = requestQueue.first();
        requestQueue.removeFirst();
        isWaitingResponse = true;
    }
}

QString WebAPIRequest::getAsynBody()
{
    if(currentRequestItem != nullptr){
        return currentRequestItem->body;
    }
    return "";
}

void WebAPIRequest::post(){
    QNetworkRequest request = getRequest();

    manager->post(request,body.toUtf8());
}

void WebAPIRequest::onNetworkResponsed(QNetworkReply *reply)
{
    if(reply != nullptr){
        QByteArray data = reply->readAll();
        LOGD("%s",data.data());
        emit networkResponsed(data);
    }
    isWaitingResponse = false;
    currentRequestItem = nullptr;
    postAsync();
}

//private
QString WebAPIRequest::xmlToHtml(QString xml)
{
    QDomDocument htmlDoc;
    QDomElement htmlRoot = htmlDoc.createElement("html");

    QDomDocument xmlDoc;
    xmlDoc.setContent(xml);
    QDomElement xmlRoot = xmlDoc.documentElement();
    QDomElement xmlItem = xmlRoot.firstChild().toElement();

    while(!xmlItem.isNull())
    {
        //read xml
        int itemId = xmlItem.attribute("id", "0").toInt();
        QString itemName = xmlItem.attribute("Name", "");

        QDomElement xmlImg = xmlItem.firstChild().toElement();
        QString imgSrc;
        int imgId = 0;
        if (!xmlImg.isNull()) {
            imgSrc = xmlImg.attribute("src", "");
            imgId = xmlImg.attribute("id", "0").toInt();
        }

        //create html
        QDomElement htmlItem = htmlDoc.createElement("p");

        QDomElement htmlImg = htmlDoc.createElement("img");
        htmlImg.setAttribute("src", imgSrc);

        QDomElement htmlText = htmlDoc.createElement("p");
        QDomText textName = htmlDoc.createTextNode(itemName);
        htmlText.appendChild(textName);

        htmlItem.appendChild(htmlImg);
        htmlItem.appendChild(htmlText);
        htmlRoot.appendChild(htmlItem);

        //next
        xmlItem = xmlItem.nextSibling().toElement();
    }

    htmlDoc.appendChild(htmlRoot);

    return htmlDoc.toString();
}
