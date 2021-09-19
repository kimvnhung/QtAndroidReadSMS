#include "appmain.h"
#include "log.h"

#include <QQmlContext>

AppMain::AppMain(QQmlApplicationEngine* engine, QObject *parent) : QObject(parent),
    m_engine(engine),
    m_isAccessibilityAvailble(false)
{
//    mastercontroller = new MasterController(this);
    m_aslbServiceCom = new ServiceCommunicator(this);
    LOGD("");
}

AppMain::~AppMain()
{
    LOGD("");
}

void AppMain::initAplication()
{
    LOGD("");
//    m_engine->rootContext()-
}

void AppMain::connectSignalSlots()
{

}


