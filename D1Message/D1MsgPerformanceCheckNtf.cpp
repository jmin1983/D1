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
    , _pid("PID", 0)
    , _memUsage("MemUsage", 0)
    , _memTotal("MemTotal", 0)
    , _cpuUsagePercent("CpuUsagePercent", 0)
{
    _messageID.second = messageString().copy();
}

D1MsgPerformanceCheckNtf::D1MsgPerformanceCheckNtf(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _pid("PID", 0)
    , _memUsage("MemUsage", 0)
    , _memTotal("MemTotal", 0)
    , _cpuUsagePercent("CpuUsagePercent", 0)
{
}

D1MsgPerformanceCheckNtf::~D1MsgPerformanceCheckNtf()
{
}

void D1MsgPerformanceCheckNtf::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_pid, archive);
    writeDataToArchive(_memUsage, archive);
    writeDataToArchive(_memTotal, archive);
    writeDataToArchive(_cpuUsagePercent, archive);
}

void D1MsgPerformanceCheckNtf::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_pid);
    readDataFromArchive(archive, &_memUsage);
    readDataFromArchive(archive, &_memTotal);
    readDataFromArchive(archive, &_cpuUsagePercent);
}

B1String D1MsgPerformanceCheckNtf::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", pid[%u]", pid());
    str.appendf(", memUsage[%lld]", memUsage());
    str.appendf(", memTotal[%d]", memTotal());
    str.appendf(", cpuUsagePercent[%lf]", cpuUsagePercent());
    return str;
}
