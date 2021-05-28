#include "revenuecontroller.h"

RevenueController::RevenueController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
}

QQmlListProperty<Transaction> RevenueController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}


//slots
void RevenueController::updateList()
{
    this->m_transactionList.clear();
    if(DatabaseHandler::instance() != nullptr){
        this->m_transactionList.append(DatabaseHandler::instance()->getTransactionList());
        emit transactionListChanged();
    }
}

