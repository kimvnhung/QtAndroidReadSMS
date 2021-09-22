#include "revenuecontroller.h"

#include <QDebug>
#include "utility.h"

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
void RevenueController::updateList(QList<Transaction*> updatedList)
{
    this->m_transactionList.clear();
    if(updatedList.size() > 0){
        this->m_transactionList.append(updatedList);
        emit transactionListChanged();
        emit todayIncomeChanged();
    }
    foreach(Transaction *item, m_transactionList ){
        qDebug()<<item->getUpdateTime();
        qDebug()<<"id : "<<item->getId()<<"_"<<item->getStatus();
    }
}

