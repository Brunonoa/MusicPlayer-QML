#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QDir>
#include <vector>
#include <memory>
#include <QtMultimedia/QMediaPlaylist>
#include <QObject>

#include "myplaylist.h"

#include "playListModel_global.h"

class PLAYLISTMODEL_EXPORT PlayListModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum PlaylistRoles {
        IndexRole = Qt::UserRole + 1,
        IconRole,
        PlaybackRole,
        NextRole,
        PreviousRole,
        SizeRole,
        NameRole
    };

    PlayListModel(QDir dirPath, QObject* parent = nullptr);
    PlayListModel(QString dirPath, QObject* parent = nullptr);

    QStringList playListNames() const;
    Q_INVOKABLE QMediaPlaylist* getPlaylistFromIndex(int index);
    Q_INVOKABLE QString getPlaylistInformation(int index) const;

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::DisplayRole) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QString getPlaylistPathFromIndex(int index);

private:
    bool isIndexValid(const QModelIndex& index) const;

    std::vector<std::unique_ptr<myPlaylist>> mPlayListsList;
    QStringList mPlaylistNames;
};

#endif // PLAYLISTMODEL_H
