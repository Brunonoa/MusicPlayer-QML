#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H

#include <QtMultimedia/QMediaPlaylist>
#include <QImage>
#include <QObject>

class myPlaylist : public QMediaPlaylist
{
    Q_OBJECT
public:

    explicit myPlaylist(QObject* parent = nullptr);
    ~myPlaylist();

    void setPlaylistName(QString name);
    QString getPlaylistName() const;

    void setPlaylistImage(QImage image);
    QImage getPlaylistImage() const;

private:
    QString mName;
    QImage mImage;
};

#endif // MYPLAYLIST_H
