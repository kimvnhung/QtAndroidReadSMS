#include "revenuecontroller.h"

RevenueController::RevenueController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = DatabaseHandler::instance()->getTransactionList();
}

QQmlListProperty<Transaction> RevenueController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}


//slots
void RevenueController::updateList()
{
    this->m_transactionList = DatabaseHandler::instance()->getTransactionList();
    emit transactionListChanged();
}

