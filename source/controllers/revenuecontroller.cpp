#include "revenuecontroller.h"

#include <QDebug>

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

    return Utility::getDisplayValue(sum);
}

//slots
void RevenueController::updateList()
{
    this->m_transactionList.clear();
    if(DatabaseHandler::instance() != nullptr){
        this->m_transactionList.append(DatabaseHandler::instance()->getTransactionListByDate(QDate::currentDate()));
        emit transactionListChanged();
        emit todayIncomeChanged();
    }
    foreach(Transaction *item, m_transactionList ){
        qDebug()<<"id : "<<item->getId()<<"_"<<item->getStatus();
    }
}

