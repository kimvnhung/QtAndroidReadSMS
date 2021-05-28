#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "comunication/jnimessenger.h"
#include "revenuecontroller.h"


class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(JniMessenger* ui_jniMessenger READ jniMessenger CONSTANT)
    Q_PROPERTY(RevenueController* ui_revenueController READ revenueController CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);

    JniMessenger* jniMessenger();
    RevenueController* revenueController();
signals:
private:
    RevenueController* m_revenueController = nullptr;

};

#endif // MAINCONTROLLER_H
