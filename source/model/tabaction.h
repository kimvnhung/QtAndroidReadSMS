#ifndef TABACTION_H
#define TABACTION_H

#include <QObject>

class TabAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString ui_text READ text NOTIFY textChanged)
    Q_PROPERTY(bool ui_selected READ selected NOTIFY selectedChanged)
public:
    explicit TabAction(QObject *parent = nullptr,
                       QString tabIcon = "",
                       QString untabIcon = "",
                       QString text = "",
                       bool selected = false);
    ~TabAction();

    QString icon();
    QString text();
    bool selected();
    void setSelected(bool isSelected);

public slots:
    void click();
signals:
    void iconChanged();
    void textChanged();
    void selectedChanged();
    void clicked();
private:
    QString mTabIcon;
    QString mUntabIcon;
    QString mText;
    bool isSeleted;
};

#endif // TABACTION_H
