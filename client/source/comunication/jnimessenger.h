#ifndef JNIMESSENGER_H
#define JNIMESSENGER_H

#include <QObject>

class JniMessenger : public QObject
{
    Q_OBJECT

public:
    explicit JniMessenger(QObject *parent = nullptr);
    static JniMessenger *instance() { return m_instance; }
    Q_INVOKABLE void printFromJava(const QString &message);

signals:
    void messageFromJava(const QString &message);

public slots:

private:
    static JniMessenger *m_instance;

    void registerDatabaseHandler();
};

#endif // JNIMESSENGER_H
