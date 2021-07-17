#ifndef HISTORYCONTROLLER_H
#define HISTORYCONTROLLER_H

#include <QObject>

class HistoryController : public QObject
{
    Q_OBJECT

public:
    explicit HistoryController(QObject *parent = nullptr);

signals:

};

#endif // HISTORYCONTROLLER_H
