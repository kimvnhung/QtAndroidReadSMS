#ifndef WEBAPIREQUEST_H
#define WEBAPIREQUEST_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

class WebAPIRequest : public QObject
{
    Q_OBJECT
public:
    explicit WebAPIRequest(QObject *parent = nullptr,QString certPath = "");

    void setBody(QString body);
    void post();
signals:
    void networkResponsed(QString response);
public slots:
    void onNetworkResponsed(QNetworkReply *reply);
private:
    QNetworkAccessManager *manager{nullptr};
    QString body;

    QString xmlToHtml(QString xml);
    bool loadPfxCertifcate(QString certFilename, QString passphrase);
};

#endif // WEBAPIREQUEST_H
