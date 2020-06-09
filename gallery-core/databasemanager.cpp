#include "databasemanager.h"

#include <QSqlDatabase>
#include <QStandardPaths>
#include <QDir>

#include <QDebug>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::~DatabaseManager()
{
    QSqlDatabase::database(mDataBaseName).close();
}

DatabaseManager::DatabaseManager(const QString &connectionName, const QString &dbFilePath) :
    mDbFilePath(dbFilePath),
    mDataBaseName(connectionName),
    albumDao(connectionName),
    pictureDao(connectionName)
{
    /*QString destinationDbFile = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation)
            .append("/" + DATABASE_FILENAME);*/

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    // Database file path
    database.setDatabaseName(mDbFilePath + ".dB");
    if(database.open())
    {
        // Called after opening database
        albumDao.init();
        pictureDao.init();
    }
    else
        qDebug()<<"Non ho aperto il database: "<<connectionName<<"salvato in: "<<dbFilePath<<".dB"<<endl;
}
