#include "playlistmodel.h"

#include <QDirIterator>
#include <QMediaContent>
#include <QImage>

PlayListModel::PlayListModel(QString dirPath, QObject* parent) :
    PlayListModel(QDir(dirPath), parent)
{}

QStringList PlayListModel::playListNames() const
{
    QStringList lista;
    for(int i=0; i<rowCount(); i++)
    {
        myPlaylist& newPlaylist = *mPlayListsList.at(static_cast<unsigned int>(i));
        lista.append(newPlaylist.getPlaylistName());
    }
    return lista;
}

PlayListModel::PlayListModel(QDir dirPath, QObject* parent) :
    QAbstractListModel(parent)
{
    // Per passare l'oggetto QMediaPlaylist a QML devo registrarlo
    qRegisterMetaType<QMediaPlaylist*>("QMediaPlaylist");

    QDirIterator it(dirPath.path(), QDirIterator::Subdirectories);
    while (it.hasNext()) {
        if (QFileInfo(it.filePath()).isDir() & (it.fileName()!=".") & (it.fileName()!=".."))
        {
            bool songFound = false;
            QDir dir(it.filePath());
            //qDebug()<<"Analizying folder: "<<it.filePath();
            std::unique_ptr<myPlaylist> newPlaylist(new myPlaylist());
            newPlaylist->setPlaylistName(it.fileName());
            newPlaylist->setCurrentIndex(0);
            QDirIterator song(dir.path(), QDir::Files);
            while(song.hasNext())
            {
                song.next();
                //qDebug()<<"Analizying file: "<<song.filePath();
                if((QFileInfo(song.filePath()).suffix() == "mp3") |
                    (QFileInfo(song.filePath()).suffix() == "m4a"))
                {
                    QUrl url = QUrl::fromLocalFile(song.path());
                    newPlaylist->addMedia(QMediaContent(url));
                    songFound=true;
                }
            }

            if(songFound) {
                int rowIndex = rowCount();
                beginInsertRows(QModelIndex(), rowIndex, rowIndex);
                //qDebug()<<"Found "<<newPlaylist->mediaCount()<<" songs";
                mPlayListsList.push_back(move(newPlaylist));
                mPlaylistNames.append(it.filePath());
                endInsertRows();
            }

            /*int rowIndex = rowCount()-1;
            qDebug()<<"Numero di canzoni in "
                   <<mPlayListsList.at(static_cast<unsigned int>(rowIndex))->getPlaylistName()
                   <<": "
                   <<mPlayListsList.at(static_cast<unsigned int>(rowIndex))->mediaCount();*/
        }
        it.next();
    }
}

QMediaPlaylist* PlayListModel::getPlaylistFromIndex(int index)
{
    if((mPlayListsList.size() > 0) & (index < static_cast<int>(mPlayListsList.size())))
        return mPlayListsList.at(static_cast<unsigned int>(index)).get();
    return nullptr;
}

QString PlayListModel::getPlaylistPathFromIndex(int index)
{
    if((mPlayListsList.size() > 0) & (index < static_cast<int>(mPlayListsList.size())))
        return mPlaylistNames.at(index);
    return "No Playlist Found";
}

QString PlayListModel::getPlaylistInformation(int index) const
{
    if((mPlayListsList.size() > 0) & (index < static_cast<int>(mPlayListsList.size())))
    {
        const myPlaylist& album = *mPlayListsList.at(static_cast<unsigned int>(index));
        QString str1 = QString(QString("Playlist name: %1").arg(album.getPlaylistName()));
        str1 = str1.leftJustified(30, ' ', true);
        str1 = str1.append(QString("Number of songs: %1\n").arg(album.mediaCount()));

        QString str2 = QString(QString("Playback mode: %1").arg(album.playbackMode()));
        str2 = str2.leftJustified(30, ' ', true);
        str2 = str2.append(QString("Current index: %1").arg(album.currentIndex()));

        QString str;
        str.append(str1);
        str.append(str2);
        return str;
    }
    return "No Playlist Found";
}

int PlayListModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return static_cast<int>(mPlayListsList.size());
}

QVariant PlayListModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const myPlaylist& album = *mPlayListsList.at(static_cast<unsigned int>(index.row()));

    switch (role) {     
        case PlaylistRoles::IconRole:
            return album.getPlaylistImage();

        case PlaylistRoles::IndexRole:
            return album.currentIndex();

        case PlaylistRoles::PlaybackRole:
            return album.playbackMode();

        case PlaylistRoles::SizeRole:
            return album.mediaCount();

        case PlaylistRoles::NameRole:
        case Qt::DisplayRole:
            return album.getPlaylistName(); //album.objectName();

        case PlaylistRoles::NextRole:
        case PlaylistRoles::PreviousRole:
            return QVariant();

        default:
            return QVariant();
    }
}

bool PlayListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!isIndexValid(index)
            || role != PlaylistRoles::PlaybackRole
            || role != PlaylistRoles::NextRole
            || role != PlaylistRoles::PreviousRole
            || role != PlaylistRoles::NameRole
            || role != PlaylistRoles::IconRole
            || role != PlaylistRoles::IndexRole) {
        return false;
    }

    myPlaylist& album = *mPlayListsList.at(static_cast<unsigned int>(index.row()));

    switch(role)
    {
        case PlaylistRoles::NameRole:
            album.setPlaylistName(value.toString());
            break;

        case PlaylistRoles::IconRole:
            album.setPlaylistImage(value.value<QImage>());
            break;

        case PlaylistRoles::PlaybackRole:
            //CurrentItemOnce, CurrentItemInLoop, Sequential, Loop, Random
            album.setPlaybackMode(static_cast<QMediaPlaylist::PlaybackMode>(value.toInt()));
            break;

        case PlaylistRoles::NextRole:
            album.next();
            break;

        case PlaylistRoles::PreviousRole:
            album.previous();
            break;

        case PlaylistRoles::IndexRole:
            album.setCurrentIndex(value.toInt());
            break;

        default:
            break;
    }

    emit dataChanged(index, index);
    return true;
}

QHash<int, QByteArray> PlayListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PlaylistRoles::IconRole] = "icon";
    roles[PlaylistRoles::PlaybackRole] = "playback";
    roles[PlaylistRoles::SizeRole] = "size";
    roles[PlaylistRoles::IndexRole] = "currentIndex";
    roles[PlaylistRoles::NameRole] = "name";
    return roles;
}

bool PlayListModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid()) {
        return false;
    }
    return true;
}

