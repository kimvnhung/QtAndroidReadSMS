#include "revenuecontroller.h"

RevenueController::RevenueController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = DatabaseHandler::instance()->getTransactionList();
}

QQmlListProperty<Transaction> RevenueController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}
