#include "reportcontroller.h"

ReportController::ReportController(QObject *parent) :
    QObject(parent)
{
    QDate cur = QDate::currentDate();
    this->mSelectedDate = new QDate();
    this->mSelectedDate->setDate(cur.year(),cur.month(),cur.day());
    this->mIsCalendarVisible = false;
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
    return "153";
}

QString ReportController::getTotalRevenue()
{
    return "2,333,00";
}

//slots
void ReportController::dateAccepted(QDate newValue)
{
    this->mSelectedDate->setDate(newValue.year(),newValue.month(),newValue.day());
    this->mIsCalendarVisible = false;
    emit selectedDateChanged();
    emit isCalendarVisibleChanged();
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
