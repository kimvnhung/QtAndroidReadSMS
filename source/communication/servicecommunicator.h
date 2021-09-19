#ifndef SERVICECOMMUNICATOR_H
#define SERVICECOMMUNICATOR_H

#include <QObject>

class ServiceCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit ServiceCommunicator(QObject *parent = nullptr);

signals:

};

#endif // SERVICECOMMUNICATOR_H
