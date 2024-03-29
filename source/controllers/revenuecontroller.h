#ifndef REVENUECONTROLLER_H
#define REVENUECONTROLLER_H

#include <QObject>
#include <QQmlListProperty>


#include "model/transaction.h"
#include "database/databasehandler.h"

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
public slots:
    void updateList();
private:
    QList<Transaction*> m_transactionList;

};

#endif // REVENUECONTROLLER_H
