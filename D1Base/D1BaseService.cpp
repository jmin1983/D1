//
// D1BaseService.cpp
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Base.h"
#include "D1BaseService.h"
#include "D1ProductIdentifier.h"
#include "D1RedisClientInterface.h"

#include <B1Base/B1SystemUtil.h>
#include <B1Base/B1Time.h>
#include <B1Redic/B1RedisDirectClient.h>
#include <B1Util/B1PerformanceProfiler.h>

using namespace BnD;

D1BaseService::D1BaseService(std::shared_ptr<D1ProductIdentifier> productIdentifier, int32 version, B1String&& buildDate, B1String&& systemName)
    : B1MainService(productIdentifier->serviceID(), version, std::move(buildDate), productIdentifier->serviceName(), std::move(systemName))
    , _productIdentifier(productIdentifier)
{
}

D1BaseService::~D1BaseService()
{
}

void D1BaseService::checkPerformance()
{
    _performanceProfiler->process();
    std::map<B1String, std::pair<int64, float64> > diskUsage;   //  map<path, pair<capacity, used_percent> >
    const auto diskPath = performanceProfilerDiskPath();
    for (const auto& path : diskPath) {
        diskUsage.emplace(path.copy(), _performanceProfiler->getDiskUsage(path));
    }
    uint32 pid = B1SystemUtil::getCurrentProcessID();
    int64 memAvailable = _performanceProfiler->memAvailable();
    int64 memUsage = _performanceProfiler->memUsage();
    int64 memCurrentProcessUsage = _performanceProfiler->memCurrentProcessUsage();
    int64 memTotal = _performanceProfiler->memTotal();
    int64 vmemUsage = _performanceProfiler->vmemUsage();
    int64 vmemCurrentProcessUsage = _performanceProfiler->vmemCurrentProcessUsage();
    int64 vmemTotal = _performanceProfiler->vmemTotal();
    float64 memUsagePercent = static_cast<float64>(memUsage) * 100 / memTotal;
    float64 vmemUsagePercent = static_cast<float64>(vmemUsage) * 100 / vmemTotal;
    float64 cpuUsagePercent = _performanceProfiler->cpuUsage();
    float64 cpuTemperature = _performanceProfiler->cpuTemperature();
    if (_performanceCheckLogTimer.isTimeover()) {
        B1String msg("performance check: ");
        msg.appendf("version[%d], build_date[%s], pid[%u], cpu_temp[%f], cpu_used[%.02f%%], "
                    "mem_used[%lld/%lld][%f%%], mem_avail[%lld], "
                    "vmem[%lld/%lld][%f%%], self_mem[%lld], self_vmem[%lld]",
            version(), buildDate().cString(), pid, cpuTemperature, cpuUsagePercent,
            memUsage, memTotal, memUsagePercent, memAvailable,
            vmemUsage, vmemTotal, vmemUsagePercent,
            memCurrentProcessUsage, vmemCurrentProcessUsage);
        if (diskUsage.empty() != true) {
            msg.append(", disk_usage");
            for (const auto& diskUsagePair : diskUsage) {
                msg.appendf("[path:%s, capacity:%lldGB, used:%.02f%%]", diskUsagePair.first.cString(), diskUsagePair.second.first / (1024 * 1024 * 1024), diskUsagePair.second.second);
            }
        }
        B1LOG("%s", msg.cString());
    }
    onCheckPerformance(pid, memAvailable, memUsage, memCurrentProcessUsage, memTotal, vmemUsage, vmemCurrentProcessUsage, vmemTotal, cpuUsagePercent, cpuTemperature, diskUsage);
}

void D1BaseService::syncWithRedisTime()
{
    uint64 redisSeconds = 0;
    uint32 redisMicroSeconds = 0;
    if (redisClientInterface()->time(&redisSeconds, &redisMicroSeconds)) {
        B1Time t(static_cast<time_t64>(redisSeconds));
        B1Time::setAdjustCurrentTime(redisSeconds, redisMicroSeconds);
    }
    else {
        B1LOG("sync redis time failed");
    }
}

B1String D1BaseService::serviceInfoKey() const
{
    return "ServiceInfo:" + mainServiceName();
}

bool D1BaseService::implStart()
{
    {
        auto redisDirectClient = initializeRedisClient();
        if (NULL == redisDirectClient) {
            return false;
        }
        _redisDirectClient.reset(redisDirectClient);
    }
    _redisClientInterface.reset(new D1RedisClientInterface(_redisDirectClient.get()));
    uint32 perfInterval = performanceProfilerInterval();
    if (CONSTS_DISABLE_PERFORMANCE_CHECK != perfInterval) {
        _performanceProfiler.reset(new B1PerformanceProfiler());
        if (_performanceProfiler->initialize()) {
            checkPerformance();
            _performanceCheckTimer.start(perfInterval);
            _performanceCheckLogTimer.start(CONSTS_PERFORMANCE_CHECK_LOG_INTERVAL);
        }
        else {
            B1LOG("initialize profiler failed");
            _performanceProfiler->finalize();
            _performanceProfiler.reset();
        }
    }
    if (useSyncWithRedisTime()) {
        syncWithRedisTime();
        _redisTimeCheckTimer.start(CONSTS_REDIS_TIME_CHECK_INTERVAL);
    }
    return true;
}

bool D1BaseService::implWorking()
{
    if (_redisTimeCheckTimer.isTimeover()) {
        syncWithRedisTime();
    }
    if (_performanceCheckTimer.isTimeover()) {
        checkPerformance();
    }
    return true;
}

void D1BaseService::implStop()
{
    if (_performanceProfiler) {
        _performanceProfiler->finalize();
        _performanceProfiler.reset();
    }
    _redisClientInterface.reset();
    if (_redisDirectClient) {
        _redisDirectClient->finalize();
        _redisDirectClient.reset();
    }
}

bool D1BaseService::isRedisCanReadWrite() const
{
    return _redisDirectClient ? _redisDirectClient->isReadSessionConnected() && _redisDirectClient->isWriteSessionConnected() : false;
}

B1String D1BaseService::serviceName() const
{
    return productIdentifier() ? productIdentifier()->serviceName() : "UNKNOWN";
}
