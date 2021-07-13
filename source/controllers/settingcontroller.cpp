#include "settingcontroller.h"

SettingController::SettingController(QObject *parent) :
    QObject(parent)
{
    this->mLanguageProperty = new PropertyAction(this,"Language","Tiếng Việt","qrc:/images/right_arrow.svg");
    this->mCurrencyProperty = new PropertyAction(this,"Currency","USD","qrc:/images/right_arrow.svg");
    this->mAboutUsProperty = new PropertyAction(this,"","About & contact us","qrc:/images/right_arrow.png");
    this->mLogOutProperty = new PropertyAction(this,"","Log out","qrc:/images/log_out.svg",true);

    connect(this->mLanguageProperty, &PropertyAction::clicked, this, &SettingController::languagePropertyClicked);
    connect(this->mCurrencyProperty, &PropertyAction::clicked, this, &SettingController::currencyPropertyClicked);
    connect(this->mAboutUsProperty, &PropertyAction::clicked, this, &SettingController::aboutUsPropertyClicked);
    connect(this->mLogOutProperty, &PropertyAction::clicked, this, &SettingController::logOutPropertyClicked);
}

SettingController::~SettingController()
{

}

PropertyAction* SettingController::getLanguageProperty()
{
    return  this->mLanguageProperty;
}

PropertyAction* SettingController::getCurrencyProperty()
{
    return this->mCurrencyProperty;
}

PropertyAction* SettingController::getAboutUsProperty()
{
    return this->mAboutUsProperty;
}

PropertyAction* SettingController::getLogOutProperty()
{
    return this->mLogOutProperty;
}

