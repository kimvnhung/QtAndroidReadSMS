#include "mastercontroller.h"

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    JniMessenger *initialer = new JniMessenger(parent);
    Q_UNUSED(initialer)

    this->m_revenueController = new RevenueController(this);

}


//publics

JniMessenger* MasterController::jniMessenger()
{
    return JniMessenger::instance();
}

RevenueController* MasterController::revenueController()
{
    return this->m_revenueController;
}
