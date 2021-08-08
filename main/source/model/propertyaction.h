#ifndef PROPERTYACTION_H
#define PROPERTYACTION_H

#include <QObject>

class PropertyAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_title READ getTitle NOTIFY propertyChanged)
    Q_PROPERTY(QString ui_content READ getContent NOTIFY propertyChanged)
    Q_PROPERTY(bool ui_isNotitle READ isNotitle NOTIFY propertyChanged)
    Q_PROPERTY(QString ui_icon READ getIcon NOTIFY propertyChanged)
    Q_PROPERTY(bool ui_isHightLight READ isHightLight NOTIFY propertyChanged)
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
    void propertyChanged();
    void clicked();
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
