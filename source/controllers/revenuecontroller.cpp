#include "revenuecontroller.h"

RevenueController::RevenueController(QObject *parent) : QObject(parent)
{
    this->m_transactionList = QList<Transaction*>();
}

QQmlListProperty<Transaction> RevenueController::transactionList()
{
    return QQmlListProperty<Transaction>(this,&this->m_transactionList);
}

QString RevenueController::todayIncome()
{
    int sum = 0;
    for(int i=0;i<this->m_transactionList.size();i++){
        sum += this->m_transactionList.at(i)->getValue();
    }

    //return Utility::;
    return "";
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

