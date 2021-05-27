#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

#include "comunication/qtandroidservice.h"
#include "revenuecontroller.h"


class MasterController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtAndroidService* ui_qtAndroidService READ qtAndroidService CONSTANT)
    Q_PROPERTY(RevenueController* ui_revenueController READ revenueController CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);

    QtAndroidService* qtAndroidService();
    RevenueController* revenueController();
signals:
private:
    RevenueController* m_revenueController = nullptr;

};

#endif // MAINCONTROLLER_H
