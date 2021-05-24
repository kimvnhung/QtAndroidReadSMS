#ifndef DATABASEREADER_H
#define DATABASEREADER_H

#include <QObject>

class DatabaseReader : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseReader(QObject *parent = nullptr);

signals:

};

#endif // DATABASEREADER_H
