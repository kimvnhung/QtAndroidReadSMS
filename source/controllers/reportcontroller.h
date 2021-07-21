#ifndef REPORTCONTROLLER_H
#define REPORTCONTROLLER_H

#include <QObject>
#include <QDate>

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
public slots:
    void showCalendar();
    void dateAccepted(QDate newValue);
    void dateCancel();
private:
    QDate *mSelectedDate{nullptr};
    bool mIsCalendarVisible = false;
};

#endif // REPORTCONTROLLER_H
