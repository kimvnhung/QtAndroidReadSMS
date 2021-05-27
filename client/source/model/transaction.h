#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

class Transaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ui_id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString ui_phone READ getPhone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString ui_code READ getCode WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(int ui_value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString ui_time READ getTime WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString ui_updateTime READ getUpdateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(bool ui_status READ getStatus WRITE setStatus NOTIFY statusChanged)
public:
    explicit Transaction(QObject *parent = nullptr, QString phone = "",
                         QString code = "", int value = 0, QString time = "");
    Transaction(QObject *parent, int id, QString phone,
                QString code, int value, QString time, QString updateTime, bool status);
    ~Transaction();


    void setId(int id);
    void setPhone(QString phone);
    void setCode(QString code);
    void setValue(int value);
    void setTime(QString time);
    void setUpdateTime(QString updateTime);
    void setStatus(bool isUpdated);

    int getId(){return this->m_id;}
    QString getPhone(){return this->m_phone;}
    QString getCode(){return this->m_code;}
    int getValue(){return this->m_value;}
    QString getTime(){return this->m_time;}
    QString getUpdateTime(){return this->m_updateTime;}
    bool getStatus(){return this->m_status;}


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
    QString m_time;
    QString m_updateTime;
    bool m_status;
};

#endif // TRANSACTION_H
