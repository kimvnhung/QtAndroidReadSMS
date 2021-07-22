#include "historycontroller.h"

#include <QDir>

HistoryController::HistoryController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
    this->apiRequester = new WebAPIRequest(this,"assets:/approval-api.pfx");
    connect(apiRequester, &WebAPIRequest::networkResponsed, this, &HistoryController::onNetworkResonsed);
}

HistoryController::~HistoryController()
{

}

QQmlListProperty<Transaction> HistoryController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}

void HistoryController::loadCertificatePath(QString path)
{
    qDebug()<<"cert path : "<<path;
    //QDir dir(path.remove("/databases/AutoLikeAgency.db"));
//    QDir dir("assets:/");
//    foreach(QString name , dir.entryList()){
//        qDebug()<<"cert "<<name;
//    }
//    this->apiRequester = new WebAPIRequest(this,path);
//    connect(apiRequester, &WebAPIRequest::networkResponsed, this, &HistoryController::onNetworkResonsed);
}

void HistoryController::traverse(const QString &pattern, const QString &dirname, int level)
{
    QDir dir(dirname);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);

    static const QStringList stringList = pattern.split('/');
    foreach (QFileInfo fileInfo, dir.entryInfoList(stringList.mid(level, 1))) {
        if (fileInfo.isDir() && fileInfo.isReadable())
            traverse(pattern, fileInfo.filePath(), level+1);
        else if (stringList.size() == (level + 1))
            qDebug() << fileInfo.filePath();
    }
}

//slots
void HistoryController::updateList()
{
    this->m_transactionList.clear();
    if(DatabaseHandler::instance() != nullptr){
        this->m_transactionList.append(DatabaseHandler::instance()->getTransactionList());
        emit transactionListChanged();
        if(apiRequester != nullptr){
            updateTransactionToServer();
        }
    }

}

void HistoryController::updateTransactionToServer()
{
    qDebug()<<"Updating";
    for(int i = 0;i<this->m_transactionList.size();i++){
        Transaction *cur = this->m_transactionList.at(i);
        if(cur->getStatus() == Transaction::PENDING){
            QJsonObject obj;
            obj.insert("code",cur->getCode());
            obj.insert("money",cur->getValue());
            apiRequester->setBody(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            apiRequester->post();
            break;
        }
    }
}

void HistoryController::onNetworkResonsed(QString data)
{
    qDebug()<<data;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        QJsonObject dataObj = obj["data"].toObject();
        if(dataObj.isEmpty()){

        }
    }
    updateTransactionToServer();
}
