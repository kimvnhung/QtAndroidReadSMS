#include "reportcontroller.h"

#include <QDebug>
#include "utility.h"

ReportController::ReportController(QObject *parent) :
    QObject(parent)
{
    QDate cur = QDate::currentDate();
    this->mSelectedDate = new QDate();
    this->mSelectedDate->setDate(cur.year(),cur.month(),cur.day());
    this->mIsCalendarVisible = false;
    this->listTrans = QList<Transaction*>();
    emit selectedDateChanged();
}

ReportController::~ReportController()
{

}

QString ReportController::getSelectedDate()
{
    int delta = this->mSelectedDate->daysTo(QDate::currentDate());
    if ( delta == 0){
        return "Today";
    }else if(delta == 1){
        return "Yesterday";
    }else if (delta == -1) {
        return "Tomorrow";
    }
    return this->mSelectedDate->toString("dd/MM/yy");
}

QDate ReportController::getSelected_Date()
{
    return *this->mSelectedDate;
}

bool ReportController::isCalendarVisible()
{
    return mIsCalendarVisible;
}

QString ReportController::getTotalTransaction()
{
    return QString::number(this->listTrans.size());
}

QString ReportController::getTotalRevenue()
{
    int sum = 0;
    for(int i=0; i<this->listTrans.size();i++){
        sum += this->listTrans.at(i)->getValue();
    }

    return Utility::getDisplayValue(sum);
}

//slots
void ReportController::dateAccepted(QDate newValue)
{
    this->mSelectedDate->setDate(newValue.year(),newValue.month(),newValue.day());
    this->mIsCalendarVisible = false;
    emit selectedDateChanged();
    emit isCalendarVisibleChanged();
    emit requestData(*mSelectedDate);
}

void ReportController::dateCancel()
{
    this->mIsCalendarVisible = false;
    emit isCalendarVisibleChanged();
}

void ReportController::showCalendar()
{
    this->mIsCalendarVisible = true;
    emit isCalendarVisibleChanged();
}

//privates
void ReportController::updateList(QList<Transaction*> updatedList)
{
    this->listTrans.clear();
    if(updatedList.size() > 0){
        this->listTrans.append(updatedList);
        qDebug()<<"List tran size"<<this->listTrans.size();
        emit totalRevenueChanged();
        emit totalTransactionChanged();
    }
}
