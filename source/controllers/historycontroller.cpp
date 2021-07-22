#include "historycontroller.h"

HistoryController::HistoryController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
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
    }
}
