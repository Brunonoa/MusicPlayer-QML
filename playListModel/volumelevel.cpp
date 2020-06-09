#include "volumelevel.h"
#include <QDebug>

VolumeLevel::VolumeLevel(QObject *parent, int interval) :
    QObject(parent)
{
    m_timer.setInterval(interval);
}

void VolumeLevel::initVolume(QObject* obj)
{
    m_player = qvariant_cast<QMediaPlayer *>(obj->property("mediaObject"));
    if( m_player != nullptr )
    {
        if(m_probe.setSource(m_player)) {
            connect(&m_probe, &QAudioProbe::audioBufferProbed, this, &VolumeLevel::processBuffer);
            connect(&m_timer, &QTimer::timeout, this, &VolumeLevel::timerExpired);
            m_timer.start();
        }
        else
            qDebug()<<"Connection not done";
    }
}

void VolumeLevel::processBuffer(QAudioBuffer buffer)
{
    // With a 16bit sample buffer:
    const quint16 *data = buffer.constData<quint16>();
    m_data = static_cast<unsigned int>(*data);
    m_probe.flush();
}

void VolumeLevel::timerExpired()
{
    emit currentVolumeChanged(m_data);
}

VolumeLevel::~VolumeLevel()
{}
