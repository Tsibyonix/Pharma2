#include "loaddatabase.h"

LoadDatabase::LoadDatabase(QStringList databaseLocation, QObject *parent) :
    QObject(parent)
{
    DBLocation = databaseLocation.at(0);
}

void LoadDatabase::loadDatabase()
{
    pharmaMain = QSqlDatabase::addDatabase("QSQLITE");
    pharmaMain.setDatabaseName(DBLocation+"/pharmamain.db3");
    qDebug() << "Database loacation "+DBLocation;
    pharmaMain.open();

    if(pharmaMain.isOpen())
    {
        DatabaseState = 1;
        qDebug() << "Database loaded";
        emit finished();
    }
    else
    {
        DatabaseState = 0;
        emit broadcastMessage("Unable to load Database!");
    }
}

void LoadDatabase::closeDatabase()
{
    pharmaMain.close();
}

bool LoadDatabase::returnDatabaseState()
{
    return DatabaseState;
}
