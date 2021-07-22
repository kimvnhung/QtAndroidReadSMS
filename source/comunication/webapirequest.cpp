#include "webapirequest.h"

#include <QDomDocument>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSslKey>

WebAPIRequest::WebAPIRequest(QObject *parent, QString certPath) :
    QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &WebAPIRequest::onNetworkResponsed);

    bool imported = loadPfxCertifcate(certPath,"approval-api");
    if(imported){
        qDebug()<<"Imported";
    }
}

//publics
void WebAPIRequest::setBody(QString body)
{
    this->body = body;
}


bool WebAPIRequest::loadPfxCertifcate(QString certFilename, QString passphrase) {

    QFile certFile(certFilename);
    certFile.open(QFile::ReadOnly);
    QSslCertificate certificate;
    QSslKey key;
    QList<QSslCertificate> importedCerts;

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
        QSslConfiguration::setDefaultConfiguration(sslConfig);
    }

    return imported;
}

void WebAPIRequest::post(){
    QNetworkRequest request(QUrl("https://approval-api.autofarmer.net/v1/transactions/active")); // without ID
    request.setRawHeader("Content-Type", "application/json");
    request.setRawHeader("Mobile-Secret-Key","3953390b-42bb-11eb-9f8b-1111914b71be");
    request.setRawHeader("Cache-Control","No-cache");
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());



    manager->post(request,body.toUtf8());
}

void WebAPIRequest::onNetworkResponsed(QNetworkReply *reply)
{
    if(reply != nullptr){
        QByteArray data = reply->readAll();
        qDebug()<<data;

        emit networkResponsed(data);
    }
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
