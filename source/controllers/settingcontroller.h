#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QObject>

#include "model/propertyaction.h"

class SettingController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PropertyAction* ui_languageProperty READ getLanguageProperty NOTIFY languagePropertyChanged)
    Q_PROPERTY(PropertyAction* ui_currencyProperty READ getCurrencyProperty NOTIFY currencyPropertyChanged)
    Q_PROPERTY(PropertyAction* ui_aboutUsProperty READ getAboutUsProperty NOTIFY aboutUsPropertyChanged)
    Q_PROPERTY(PropertyAction* ui_logOutProperty READ getLogOutProperty NOTIFY logOutPropertyChanged)
public:
    explicit SettingController(QObject *parent = nullptr);
    ~SettingController();

    PropertyAction* getLanguageProperty();
    PropertyAction* getCurrencyProperty();
    PropertyAction* getAboutUsProperty();
    PropertyAction* getLogOutProperty();
signals:
    void languagePropertyChanged();
    void currencyPropertyChanged();
    void aboutUsPropertyChanged();
    void logOutPropertyChanged();

    void languagePropertyClicked();
    void currencyPropertyClicked();
    void aboutUsPropertyClicked();
    void logOutPropertyClicked();
private:
    PropertyAction* mLanguageProperty{nullptr};
    PropertyAction* mCurrencyProperty{nullptr};
    PropertyAction* mAboutUsProperty{nullptr};
    PropertyAction* mLogOutProperty{nullptr};

};

#endif // SETTINGCONTROLLER_H
