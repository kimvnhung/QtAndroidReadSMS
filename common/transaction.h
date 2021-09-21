#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include <QDateTime>
#include "utility.h"

class Transaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString ui_phone READ getPhone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString ui_code READ getCode WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(QString ui_value READ getDisplayValue NOTIFY valueChanged)
    Q_PROPERTY(QString ui_time READ getTime WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString ui_updateTime READ getUpdateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(int ui_status READ getStatus WRITE setStatus NOTIFY statusChanged)
public:
    explicit Transaction(QObject *parent = nullptr, QString phone = "",
                         QString code = "", int value = 0, QString time = "");
    Transaction(QObject *parent, int id, QString phone,
                QString code, int value, QString time, QString updateTime, int status);
    ~Transaction();

    enum UpdateStatus{
        UNKNOWN = -1,
        PENDING = 0,
        ACCEPTED = 1,
        REJECT = 2
    };

    static QString format;
    static Transaction* fromJson(QString json);


    void setId(int id);
    void setPhone(QString phone);
    void setCode(QString code);
    void setValue(int value);
    void setTime(QString time);
    void set_Time(QDateTime time);
    void setUpdateTime(QString updateTime);
    void set_UpdateTime(QDateTime updateTime);
    void setStatus(int isUpdated);

    int getId(){return this->m_id;}
    QString getPhone(){return this->m_phone;}
    QString getCode(){return this->m_code;}
    int getValue(){return this->m_value;}
    QString getDisplayValue();
    QString getTime(){return this->m_time.toString(format);}
    QDateTime get_Time(){return this->m_time;}
    QString getUpdateTime(){return this->m_updateTime.toString(format);}
    QDateTime get_UpdateTime(){return this->m_updateTime;}
    int getStatus(){return this->m_status;}


    QString toJson();
signals:
    void idChanged();
    void phoneChanged();
    void codeChanged();
    void valueChanged();
    void timeChanged();
    void updateTimeChanged();
    void statusChanged();
private:
    int m_id;
    QString m_phone;
    QString m_code;
    int m_value;
    QDateTime m_time;
    QDateTime m_updateTime;
    int m_status;
};

#endif // TRANSACTION_H
