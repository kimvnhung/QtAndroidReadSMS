#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>

class Account : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_name READ name NOTIFY nameChanged)
public:
    explicit Account(QObject *parent = nullptr,
                     QString username = "",
                     QString password = "",
                     QString name = "");
    QString name();
signals:
    void nameChanged();
private:
    QString mUsername;
    QString mPassword;
    QString mName;
};

#endif // ACCOUNT_H
