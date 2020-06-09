#include "picturemodel.h"
#include "albummodel.h"

PictureModel::PictureModel(const AlbumModel &albumModel, QObject *parent) :
    QAbstractListModel(parent),
    mAlbumId(-1),
    mPictures(new std::vector<std::unique_ptr<Picture>>())
{
    connect(&albumModel, &AlbumModel::removeRows, this, &PictureModel::deletePicturesForAlbum);
}

QModelIndex PictureModel::addPicture(const Picture &picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    std::unique_ptr<Picture>newPicture(new Picture(picture));
    DatabaseManager::instance().pictureDao.addPictureInAlbum(mAlbumId, *newPicture);
    mPictures->push_back(move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

void PictureModel::addPictureFromUrl(const QUrl &pictureUrl)
{
    addPicture(Picture(pictureUrl));
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    (void)parent;
    return static_cast<int>(mPictures->size());
}

QVariant PictureModel::data(const QModelIndex &index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const Picture& picture = *mPictures->at(static_cast<unsigned int>(index.row()));

    switch (role) {
        case Qt::DisplayRole:
            return picture.fileUrl().fileName();

        case Roles::UrlRole:
            return picture.fileUrl();

        case Roles::FilePathRole:
            return picture.fileUrl().toLocalFile();

        default:
            return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if ((row < 0)
            || (row >= rowCount())
            || (count < 0)
            || ((row + count) > rowCount())) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while(countLeft--) {
        const Picture& picture = *mPictures->at(static_cast<unsigned int>(row + countLeft));
        DatabaseManager::instance().pictureDao.removePicture(picture.id());
    }
    mPictures->erase(mPictures->begin() + row,
                    mPictures->begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Roles::FilePathRole] = "filepath";
    roles[Roles::UrlRole] = "url";
    return roles;
}

void PictureModel::setAlbumId(int albumId)
{
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}

void PictureModel::clearAlbum()
{
    setAlbumId(-1);
}

void PictureModel::deletePicturesForAlbum()
{
    DatabaseManager::instance().pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId)
{
    if (albumId <= 0) {
        mPictures.reset(new std::vector<std::unique_ptr<Picture>>());
        return;
    }
    mPictures = DatabaseManager::instance().pictureDao.picturesForAlbum(albumId);
}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    if ((index.row() < 0)
            || (index.row() >= rowCount())
            || (!index.isValid())) {
        return false;
    }
    return true;
}
