#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include <QObject>
#include <QDate>
#include <model/transaction.h>

class ReportController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_selectedDate READ getSelectedDate NOTIFY selectedDateChanged)
    Q_PROPERTY(bool ui_isCalendarVisible READ isCalendarVisible NOTIFY isCalendarVisibleChanged)
    Q_PROPERTY(QString ui_totalTransaction READ getTotalTransaction NOTIFY totalTransactionChanged)
    Q_PROPERTY(QString ui_totalRevenue READ getTotalRevenue NOTIFY totalRevenueChanged)
public:
    explicit ReportController(QObject *parent = nullptr);
    ~ReportController();

    QString getSelectedDate();
    bool isCalendarVisible();
    QString getTotalTransaction();
    QString getTotalRevenue();
signals:
    void selectedDateChanged();
    void isCalendarVisibleChanged();
    void totalTransactionChanged();
    void totalRevenueChanged();
    void requestData(QDate date);
public slots:
    void showCalendar();
    void dateAccepted(QDate newValue);
    void dateCancel();
    void updateList(QList<Transaction*> updatedList);
private:
    QDate *mSelectedDate{nullptr};
    bool mIsCalendarVisible = false;
    QList<Transaction*> listTrans;

};

#endif // REPORTCONTROLLER_H
