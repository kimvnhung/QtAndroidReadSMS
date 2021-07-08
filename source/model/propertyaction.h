#ifndef PROPERTYACTION_H
#define PROPERTYACTION_H

#include <QObject>

class PropertyAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_title READ getTitle NOTIFY titleChanged)
    Q_PROPERTY(QString ui_content READ getContent NOTIFY contentChanged)
    Q_PROPERTY(bool ui_isNotitle READ isNotitle NOTIFY isNotitleChanged)
    Q_PROPERTY(QString ui_icon READ getIcon NOTIFY iconChanged)
    Q_PROPERTY(bool ui_isHightLight READ isHightLight NOTIFY isHightLightChanged)
public:
    explicit PropertyAction(QObject *parent = nullptr,
                            QString title = "",
                            QString content = "",
                            QString icon = "",
                            bool isHightLight = false);
    ~PropertyAction();

    QString getTitle();
    QString getContent();
    bool isNotitle();
    QString getIcon();
    bool isHightLight();
signals:
    void titleChanged();
    void contentChanged();
    void isNotitleChanged();
    void iconChanged();
    void isHightLightChanged();
public slots:
    void click();
private:
    QString mTitle;
    QString mContent;
    bool mIsNotitle;
    QString mIcon;
    bool mIsHightLight;

};

#endif // PROPERTYACTION_H
