#include "historycontroller.h"

#include <QDir>
#include <QNetworkConfigurationManager>

HistoryController::HistoryController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
    this->apiRequester = new WebAPIRequest(this);
    connect(apiRequester, &WebAPIRequest::networkResponsed, this, &HistoryController::onNetworkResonsed);
}

HistoryController::~HistoryController()
{

}

QQmlListProperty<Transaction> HistoryController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}


//slots
void HistoryController::updateList()
{
    this->m_transactionList.clear();
    if(DatabaseHandler::instance() != nullptr){
        this->m_transactionList.append(DatabaseHandler::instance()->getTransactionList());
        emit transactionListChanged();
        int counter = 0;
        foreach(Transaction* trans,this->m_transactionList){
            qDebug()<<__FUNCTION__<<trans->getUpdateTime();
            qDebug()<<__FUNCTION__<<trans->getStatus();
            if(trans->getStatus() == Transaction::PENDING){
                counter++;
            }
            if(counter >= 1){
                updateTransactionToServer();
                break;
            }
        }
    }

}

void HistoryController::updateTransactionToServer()
{
    qDebug()<<"Updating";

    for(int i = 0;i<this->m_transactionList.size();i++){
        Transaction *cur = this->m_transactionList.at(i);
        qDebug()<<"UpdateToServerIndex : "<<i;
        if(cur->getStatus() == Transaction::PENDING){
            QJsonObject obj;
            obj.insert("code",cur->getCode());
            obj.insert("money",cur->getValue());
            apiRequester->setBody(QJsonDocument(obj).toJson(QJsonDocument::Compact));
            apiRequester->post();
            temp = cur;
            break;
        }
        if(i == this->m_transactionList.size()-1){
            temp = nullptr;
        }
    }
}

void HistoryController::onNetworkResonsed(QString data)
{
    qDebug()<<__FUNCTION__;

    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    if(doc.isObject()){
        QJsonObject obj = doc.object();
        QJsonObject dataObj = obj["data"].toObject();
        qDebug()<<"Data"<<QJsonDocument(dataObj).toJson(QJsonDocument::Compact);
        if(temp != nullptr){
            updateCounter++;
            if(dataObj.isEmpty()){
                    temp->setStatus(Transaction::REJECT);
                    DatabaseHandler::instance()->update(temp);
            }else {
                QString status = dataObj["status"].toString();
                if(status == "Active"){

                    temp->setStatus(Transaction::ACCEPTED);
                    QString updatedDate = dataObj["updated_at"].toString();
                    QDateTime updateDate = QDateTime::fromString(updatedDate,"yyyy-MM-ddTHH:mm:ss.zzzZ");
                    if(updateDate.isValid()){
                        qDebug()<<"update success";
                        temp->set_UpdateTime(updateDate);
                        DatabaseHandler::instance()->update(temp);
                    }
                }else{
                    qDebug()<<"update failed";
                }
            }
        }

        if(updateCounter <= this->m_transactionList.size()){
            qDebug()<<"Counter :"<<updateCounter;
            updateTransactionToServer();
        }
    }

}
