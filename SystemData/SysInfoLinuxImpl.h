#ifndef SYSINFOLINUXIMPL_H
#define SYSINFOLINUXIMPL_H

#include        "SysInfo.h"

#include        <QtCore/QtGlobal>
#include        <QtCore/QVector>

class SysInfoLinuxImpl : public SysInfo
{
public:
    SysInfoLinuxImpl();

    // SysInfo interface
    void init() override;
    double memoryUsage() override;
    double cpuLoadAverage() override;
private:
    QVector<qulonglong>	cpuRawData();

private:
    QVector<qulonglong>	mCpuLoadLastValues;
};

#endif // SYSINFOLINUXIMPL_H
