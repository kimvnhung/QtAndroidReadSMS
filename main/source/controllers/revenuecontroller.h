#ifndef REVENUECONTROLLER_H
#define REVENUECONTROLLER_H

#include <QObject>
#include <QQmlListProperty>


#include "model/transaction.h"

class RevenueController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Transaction> ui_transactionList READ transactionList NOTIFY transactionListChanged)
    Q_PROPERTY(QString ui_todayIncome READ todayIncome NOTIFY todayIncomeChanged)
public:
    explicit RevenueController(QObject *parent = nullptr);

    QQmlListProperty<Transaction> transactionList();
    QString todayIncome();
signals:
    void transactionListChanged();
    void todayIncomeChanged();
    void requestData(QDate date);
public slots:
    void updateList(QList<Transaction*> updatedList);
private:
    QList<Transaction*> m_transactionList;

};

#endif // REVENUECONTROLLER_H
