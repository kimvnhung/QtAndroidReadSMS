#include "historycontroller.h"

#include <QDir>
#include <QNetworkConfigurationManager>

HistoryController::HistoryController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
//    this->apiRequester = new WebAPIRequest(this);
//    connect(apiRequester, &WebAPIRequest::networkResponsed, this, &HistoryController::onNetworkResonsed);
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

        for(int i=0; i<m_transactionList.size(); i++){
            if(m_transactionList.at(i)->getStatus() == Transaction::PENDING){
                emit updateToServer();
                break;
            }
        }
    }
}
