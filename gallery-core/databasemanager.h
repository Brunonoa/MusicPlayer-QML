#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>

#include "albumdao.h"
#include "picturedao.h"

const QString DATABASE_FILENAME = "gallery";
const QString DATABASE_FILEPATH = "gallery";

class DatabaseManager
{
    public:
        static DatabaseManager& instance();
        ~DatabaseManager();

    protected:
        DatabaseManager(const QString& name	= DATABASE_FILENAME, const QString& path = DATABASE_FILEPATH);
        DatabaseManager& operator=(const DatabaseManager& rhs);

    private:
        const QString mDbFilePath;

    public:
        const QString mDataBaseName;
        const AlbumDao albumDao;
        const PictureDao pictureDao;
};

#endif // DATABASEMANAGER_H
