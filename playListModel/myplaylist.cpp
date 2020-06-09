#include "myplaylist.h"

#include <QUrl>

myPlaylist::myPlaylist(QObject* parent) :
    QMediaPlaylist(parent)
{

}

myPlaylist::~myPlaylist()
{

}

void myPlaylist::setPlaylistName(QString name)
{
    mName=name;
}

QString myPlaylist::getPlaylistName() const
{
    return mName;
}

void myPlaylist::setPlaylistImage(QImage image)
{
    mImage=image;
}

QImage myPlaylist::getPlaylistImage() const
{
    return mImage;
}
