#include "reportcontroller.h"

#include <QDebug>

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
    updateList();
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
void ReportController::updateList()
{
    this->listTrans.clear();
    if(DatabaseHandler::instance() != nullptr){
        this->listTrans.append(DatabaseHandler::instance()->getTransactionListByDate(*this->mSelectedDate));
        qDebug()<<"List tran size"<<this->listTrans.size();
        emit totalRevenueChanged();
        emit totalTransactionChanged();
    }
}
