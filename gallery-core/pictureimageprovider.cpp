#include "pictureimageprovider.h"

#include <QStringList>
#include <QUrl>

#include "picturemodel.h"

const QString PICTURE_SIZE_FULL                     = "full";
const QString PICTURE_SIZE_THUMBNAIL                = "thumbnail";
const QSize PictureImageProvider::THUMBNAIL_SIZE    = QSize(350, 350);

PictureImageProvider::PictureImageProvider(PictureModel *pictureModel) :
    QQuickImageProvider(QQuickImageProvider::Pixmap),
    mPictureModel(pictureModel)
{}

QPixmap PictureImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize)
    Q_UNUSED(size)

    QStringList	query = id.split('/');
    if((!mPictureModel) || (query.size() < 2)) {
        return QPixmap();
    }

    int	row	= query[0].toInt();
    QString	pictureSize	= query[1];

    QUrl fileUrl = mPictureModel->data(mPictureModel->index(row, 0), PictureModel::Roles::UrlRole).toUrl();
    return *pictureFromCache(fileUrl.toLocalFile(), pictureSize);
}

QPixmap* PictureImageProvider::pictureFromCache(const QString& filepath, const QString& pictureSize)
{
    QString	key	= QStringList{pictureSize, filepath}.join("-");
    QPixmap* cachePicture =	nullptr;
    if(!mPicturesCache.contains(pictureSize)){
        QPixmap	originalPicture(filepath);
        if	(pictureSize == PICTURE_SIZE_THUMBNAIL){
            cachePicture = new QPixmap(originalPicture.scaled(THUMBNAIL_SIZE, Qt::KeepAspectRatio,
                                                              Qt::SmoothTransformation));
        }
        else if(pictureSize == PICTURE_SIZE_FULL){
            cachePicture = new QPixmap(originalPicture);
        }

        mPicturesCache.insert(key,	cachePicture);
    }
    else{
        cachePicture = mPicturesCache[pictureSize];
    }

    return	cachePicture;
}
