#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <vector>
#include <memory>

class QSqlDatabase;

#include <QList>
#include "picture.h"

class PictureDao
{
    public:
        explicit PictureDao(QString databaseName);
        void init()	const;

        void addPictureInAlbum(int albumId,	Picture& picture) const;
        void removePicture(int id)	const;
        void removePicturesForAlbum(int	albumId) const;
        std::unique_ptr<std::vector<std::unique_ptr<Picture>>> picturesForAlbum(int albumId) const;

    private:
        QString mDatabaseName;
};

#endif // PICTUREDAO_H
