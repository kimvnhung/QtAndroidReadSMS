#include "mastercontroller.h"

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    this->m_revenueController = new RevenueController(this);
}


//publics
QtAndroidService* MasterController::qtAndroidService()
{
    return QtAndroidService::instance();
}

RevenueController* MasterController::revenueController()
{
    return this->m_revenueController;
}
