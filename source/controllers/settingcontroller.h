#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QObject>

#include "model/propertyaction.h"

class SettingController : public QObject
{
    Q_OBJECT
public:
    explicit SettingController(QObject *parent = nullptr);

signals:

};

#endif // SETTINGCONTROLLER_H
