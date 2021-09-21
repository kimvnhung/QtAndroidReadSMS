#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>

#include "transaction.h"

class HistoryController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Transaction> ui_transactionList READ transactionList NOTIFY transactionListChanged)
public:
    explicit HistoryController(QObject *parent = nullptr);
    ~HistoryController();
    QQmlListProperty<Transaction> transactionList();
signals:
    void transactionListChanged();
    void updateToServer();
    void requestData();
public slots:
    void updateList(QList<Transaction*> updatedList);
private:
    QList<Transaction*> m_transactionList;
};

#endif // HISTORYCONTROLLER_H
