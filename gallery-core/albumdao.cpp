#include "albumdao.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QVariant>
#include <QDebug>

#include "databasemanager.h"

#include "album.h"

using namespace std;

AlbumDao::AlbumDao(QString database) :
    mDatabaseName(database)
{

}

void AlbumDao::init() const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    if (!database.tables().contains("albums"))	{
        QSqlQuery query(database);
        query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    }
}

void AlbumDao::addAlbum(Album &album) const
{
    bool tempBool;
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    tempBool = query.prepare("INSERT INTO albums (name) VALUES (:name)");
    //qDebug() << "prepare: " << tempBool << endl;
    query.bindValue(":name", album.name());
    tempBool = query.exec();
    //qDebug() << "exec: " << tempBool << endl;
    album.setId(query.lastInsertId().toInt());
}

void AlbumDao::updateAlbum(const Album &album) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare("UPDATE albums SET name = (:name) WHERE id = (:id)");
    query.bindValue(":name", album.name());
    query.bindValue(":id", album.id());
    query.exec();
    //DatabaseManager::debugQuery(query);
}

void AlbumDao::removeAlbum(int id) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare("DELETE FROM albums WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
}

unique_ptr<vector<unique_ptr<Album>>> AlbumDao::albums() const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query("SELECT * FROM albums", database);
    query.exec();
    unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>());
    while(query.next())
    {
        unique_ptr<Album> album(new Album());
        album->setId(query.value("id").toInt());
        album->setName(query.value("name").toString());
        list->push_back(move(album));
    }
    return list;
}
