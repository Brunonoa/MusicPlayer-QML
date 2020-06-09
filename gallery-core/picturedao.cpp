#include "picturedao.h"

#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QVariant>

#include "picture.h"

using namespace std;

PictureDao::PictureDao(QString databaseName) :
    mDatabaseName(databaseName)
{

}

void	PictureDao::init()	const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    if	(!database.tables().contains("pictures"))	{
        QSqlQuery	query(database);
        query.exec(QString("CREATE	TABLE	pictures")
        +	"	(id	INTEGER	PRIMARY	KEY	AUTOINCREMENT,	"
        +	"album_id	INTEGER,	"
        +	"url	TEXT)");
    }
}

void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare(QString("INSERT INTO pictures")
        + " (album_id, url)"
        + " VALUES ("
        + ":album_id, "
        + ":url"
        + ")");
    query.bindValue(":album_id", albumId);
    query.bindValue(":url", picture.fileUrl());
    query.exec();
    //DatabaseManager::debugQuery(query);
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare("DELETE FROM pictures WHERE id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    //DatabaseManager::debugQuery(query);
}

void PictureDao::removePicturesForAlbum(int albumId) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare("DELETE FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
    //DatabaseManager::debugQuery(query);
}

unique_ptr<vector<unique_ptr<Picture>>> PictureDao::picturesForAlbum(int albumId) const
{
    QSqlDatabase database = QSqlDatabase::database(mDatabaseName);
    QSqlQuery query(database);
    query.prepare("SELECT * FROM pictures WHERE album_id = (:album_id)");
    query.bindValue(":album_id", albumId);
    query.exec();
    //DatabaseManager::debugQuery(query);
    unique_ptr<vector<unique_ptr<Picture>>> list(new vector<unique_ptr<Picture>>());
    while(query.next()) {
        unique_ptr<Picture> picture(new Picture());
        picture->setId(query.value("id").toInt());
        picture->setAlbumId(query.value("album_id").toInt());
        picture->setFileUrl(query.value("url").toString());
        list->push_back(move(picture));
    }
    return list;
}


