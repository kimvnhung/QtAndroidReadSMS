#include "propertyaction.h"

#include <QDebug>

PropertyAction::PropertyAction(QObject *parent, QString title, QString content, QString icon, bool isHightLight):
    QObject(parent)
{
    this->mTitle = title;
    this->mContent = content;
    this->mIsNotitle = title.size()==0;
    this->mIcon = icon;
    this->mIsHightLight = isHightLight;
    emit propertyChanged();
}

PropertyAction::~PropertyAction()
{

}

QString PropertyAction::getTitle()
{
    return this->mTitle;
}

QString PropertyAction::getContent()
{
    return this->mContent;
}

QString PropertyAction::getIcon()
{
    return this->mIcon;
}

bool PropertyAction::isHightLight()
{
    return this->mIsHightLight;
}

bool PropertyAction::isNotitle()
{
    return this->mIsNotitle;
}


//slots
void PropertyAction::click()
{
    qDebug()<<"PropertyClicked";
    emit clicked();
}
