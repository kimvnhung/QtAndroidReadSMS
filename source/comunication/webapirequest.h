#ifndef WEBAPIREQUEST_H
#define WEBAPIREQUEST_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkReply>

class WebAPIRequest : public QObject
{
    Q_OBJECT
public:
    explicit WebAPIRequest(QObject *parent = nullptr);
    ~WebAPIRequest();

    void setBody(QString body);
    void post();
signals:
    void networkResponsed(QString response);
public slots:
    void onNetworkResponsed(QNetworkReply *reply);
private:
    QNetworkAccessManager *manager{nullptr};
    QString body;

    static const QString AUTOFARMER_CERTIFICATE_PATH;
    static const QString AUTOLIKE_CERTIFICATE_PATH;
    static const QString MT_CERTIFICATE_PATH;
    static const QString AUTOFARMER_PASS;
    static const QString AUTOLIKE_PASS;
    static const QString MT_PASS;

    QSslConfiguration AUTOFARMER_SSL_CONF;
    QSslConfiguration AUTOLIKE_SSL_CONF;
    QSslConfiguration MT_SSL_CONF;

    QString xmlToHtml(QString xml);
    bool loadPfxCertificate(QString certFilename, QString passphrase);
    QNetworkRequest getRequest();

};

#endif // WEBAPIREQUEST_H
