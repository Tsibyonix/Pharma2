#ifndef LOADDATABASE_H
#define LOADDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>

class LoadDatabase : public QObject
{
    Q_OBJECT
public:
    explicit LoadDatabase(QStringList databaseLocation, QObject *parent = 0);
    void closeDatabase();
    bool returnDatabaseState();

private:
    QSqlDatabase pharmaMain;
    bool DatabaseState;
    QString DBLocation;

signals:
    void broadcastMessage(QString message);
    void finished();

public slots:
    void loadDatabase();
};

#endif // LOADDATABASE_H
