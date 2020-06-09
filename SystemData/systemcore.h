#ifndef SYSTEMCORE_H
#define SYSTEMCORE_H

#include <QTimer>
#include <QDateTime>

#include "SystemData_global.h"

//https://doc.qt.io/archives/qt-4.8/qtbinding.html#receiving-signals

class SYSTEMDATA_EXPORT Systemcore : public QObject
{
    Q_OBJECT
public:
    static Systemcore& instance();
    void init(int timeMs = 1000);

signals:
    void updateTime(QString currentTimeValue);
    void updateMemoryUsed(double currentMemoryUsed);
    void updateCpuLoad(double currentCpuLoad);

protected:
    explicit Systemcore();

private:
    Systemcore(const Systemcore& rhs);
    Systemcore& operator=(const Systemcore& rhs);
    void timerEvent(QTimerEvent *event) override;
};

#endif // SYSTEMCORE_H
