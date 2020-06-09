#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "SystemData_global.h"

class SYSTEMDATA_EXPORT SysInfo
{
    public:
        static SysInfo& instance();
        virtual ~SysInfo();

        virtual void init() = 0;
        virtual double cpuLoadAverage() = 0;
        virtual double memoryUsage() = 0;

protected:
        explicit SysInfo();

private:
        SysInfo(const SysInfo& rhs);
        SysInfo& operator=(const SysInfo& rhs);
};

#endif // SYSTEMDATA_H
