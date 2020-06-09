#ifndef VOLUMELEVEL_H
#define VOLUMELEVEL_H

#include <QObject>
#include <QAudioProbe>
#include <QMediaPlayer>
#include <QTimer>
#include <vector>
#include <memory>

#include "playListModel_global.h"

class PLAYLISTMODEL_EXPORT VolumeLevel : public QObject
{
    Q_OBJECT
public:
    explicit VolumeLevel(QObject *parent = nullptr, int interval = 1000);
    ~VolumeLevel();

    // Must call Q_INVOKABLE so that this function can be used in QML
    Q_INVOKABLE void initVolume(QObject* obj);

signals:
    void currentVolumeChanged(const unsigned int data);

public slots:
    void processBuffer(QAudioBuffer buffer);
    void timerExpired();

private:
    QAudioProbe m_probe;
    QMediaPlayer *m_player;
    QTimer m_timer;
    unsigned int m_data;
};

#endif // VOLUMELEVEL_H
