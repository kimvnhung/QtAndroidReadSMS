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
    void loadCertificatePath(QString path);
signals:
    void transactionListChanged();
public slots:
    void updateList();

private:
    QList<Transaction*> m_transactionList;
    WebAPIRequest *apiRequester{nullptr};
    void traverse(const QString &pattern, const QString &dirname, int level);
private slots:
    void updateTransactionToServer();
    void onNetworkResonsed(QString data);
};

#endif // HISTORYCONTROLLER_H
