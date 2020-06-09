#include "systemcore.h"
#include "SysInfo.h"
#include <QDebug>

Systemcore::Systemcore() :
    QObject()
{
}

void Systemcore::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    QString currentTimeValue = QTime::currentTime().toString("hh:mm:ss");
    emit updateTime(currentTimeValue);
    emit updateCpuLoad(SysInfo::instance().cpuLoadAverage());
    emit updateMemoryUsed(SysInfo::instance().memoryUsage());
}

Systemcore &Systemcore::instance()
{
    static Systemcore singleton;
    return singleton;
}

void Systemcore::init(int timeMs)
{   
    SysInfo::instance().init();
    startTimer(timeMs);
}


