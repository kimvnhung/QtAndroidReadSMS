#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include <QObject>
#include <QQmlListProperty>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>

#include "model/transaction.h"
#include "database/databasehandler.h"
#include "comunication/webapirequest.h"

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
public slots:
    void updateList();
    void updateTransactionToServer();
private:
    QList<Transaction*> m_transactionList;
    WebAPIRequest *apiRequester{nullptr};
    Transaction* temp{nullptr};
    int updateCounter = 0;
private slots:

    void onNetworkResonsed(QString data);
};

#endif // HISTORYCONTROLLER_H
