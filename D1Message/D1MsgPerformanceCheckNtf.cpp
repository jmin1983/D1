//
// D1MsgPerformanceCheckNtf.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MsgPerformanceCheckNtf.h"

#include <D1Base/D1Consts.h>

using namespace BnD;

D1MsgPerformanceCheckNtf::D1MsgPerformanceCheckNtf()
    : D1BaseMessage()
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _pid("PID", 0)
    , _memAvailable("MemAvailable", 0)
    , _memUsage("MemUsage", 0)
    , _memCurrentProcessUsage("MemCurrentProcessUsage", 0)
    , _memTotal("MemTotal", 0)
    , _vmemUsage("VMemUsage", 0)
    , _vmemCurrentProcessUsage("VMemCurrentProcessUsage", 0)
    , _vmemTotal("VMemTotal", 0)
    , _cpuUsagePercent("CpuUsagePercent", 0)
    , _cpuTemperature("CpuTemperature", 0)
{
    _messageID.second = messageString().copy();
}

D1MsgPerformanceCheckNtf::D1MsgPerformanceCheckNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
    , _pid("PID", 0)
    , _memAvailable("MemAvailable", 0)
    , _memUsage("MemUsage", 0)
    , _memCurrentProcessUsage("MemCurrentProcessUsage", 0)
    , _memTotal("MemTotal", 0)
    , _vmemUsage("VMemUsage", 0)
    , _vmemCurrentProcessUsage("VMemCurrentProcessUsage", 0)
    , _vmemTotal("VMemTotal", 0)
    , _cpuUsagePercent("CpuUsagePercent", 0)
    , _cpuTemperature("CpuTemperature", 0)
{
}

D1MsgPerformanceCheckNtf::~D1MsgPerformanceCheckNtf()
{
}

void D1MsgPerformanceCheckNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serviceID, archive);
    writeDataToArchive(_pid, archive);
    writeDataToArchive(_memAvailable, archive);
    writeDataToArchive(_memUsage, archive);
    writeDataToArchive(_memCurrentProcessUsage, archive);
    writeDataToArchive(_memTotal, archive);
    writeDataToArchive(_vmemUsage, archive);
    writeDataToArchive(_vmemCurrentProcessUsage, archive);
    writeDataToArchive(_vmemTotal, archive);
    writeDataToArchive(_cpuUsagePercent, archive);
    writeDataToArchive(_cpuTemperature, archive);
}

void D1MsgPerformanceCheckNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serviceID);
    readDataFromArchive(archive, &_pid);
    readDataFromArchive(archive, &_memAvailable);
    readDataFromArchive(archive, &_memUsage);
    readDataFromArchive(archive, &_memCurrentProcessUsage);
    readDataFromArchive(archive, &_memTotal);
    readDataFromArchive(archive, &_vmemUsage);
    readDataFromArchive(archive, &_vmemCurrentProcessUsage);
    readDataFromArchive(archive, &_vmemTotal);
    readDataFromArchive(archive, &_cpuUsagePercent);
    readDataFromArchive(archive, &_cpuTemperature);
}

B1String D1MsgPerformanceCheckNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", serviceID[%d]", serviceID());
    str.appendf(", pid[%u]", pid());
    str.appendf(", memAvailable[%lld]", memAvailable());
    str.appendf(", memUsage[%lld]", memUsage());
    str.appendf(", memCurrentProcessUsage[%lld]", memCurrentProcessUsage());
    str.appendf(", memTotal[%d]", memTotal());
    str.appendf(", vmemUsage[%lld]", vmemUsage());
    str.appendf(", vmemCurrentProcessUsage[%lld]", vmemCurrentProcessUsage());
    str.appendf(", vmemTotal[%d]", vmemTotal());
    str.appendf(", cpuUsagePercent[%lf]", cpuUsagePercent());
    str.appendf(", cpuTemperature[%lf]", cpuTemperature());
    return str;
}
