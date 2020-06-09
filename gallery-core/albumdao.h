#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include <vector>
#include <memory>

class QSqlDatabase;

#include <QList>
#include "album.h"

class AlbumDao
{
    public:
        explicit AlbumDao(QString database);
        void init()	const;

        void addAlbum(Album& album) const;
        void updateAlbum(const	Album&	album)	const;
        void removeAlbum(int id)	const;
        std::unique_ptr<std::vector<std::unique_ptr<Album>>> albums() const;

    private:
        QString mDatabaseName;
};

#endif // ALBUMDAO_H
