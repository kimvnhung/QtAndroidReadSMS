#include "tabaction.h"

TabAction::TabAction(QObject *parent, QString tabicon, QString untabicon, QString text,bool selected) :
    QObject(parent)
{
    this->mTabIcon = tabicon;
    this->mUntabIcon = untabicon;
    this->mText = text;
    this->isSeleted = selected;
}

TabAction::~TabAction()
{

}

QString TabAction::icon()
{
    return this->isSeleted?mTabIcon:mUntabIcon;
}

QString TabAction::text()
{
    return this->mText;
}

bool TabAction::selected()
{
    return this->isSeleted;
}

void TabAction::setSelected(bool isSelected)
{
    this->isSeleted = isSelected;
    emit iconChanged();
    emit selectedChanged();
}

//slots
void TabAction::click()
{
    this->isSeleted = !this->isSeleted;
    emit clicked();
    emit iconChanged();
    emit selectedChanged();
}
