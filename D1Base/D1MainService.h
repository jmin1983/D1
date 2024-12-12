//
// D1MainService.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_MAIN_SERVICE_H
#define _D1BASE_MAIN_SERVICE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1MainService.h>
#include <B1Util/B1TimeChecker.h>

namespace BnD {
    class B1PerformanceProfiler;
    class B1RedisDirectClient;
    class D1RedisClientInterface;
    class D1ProductIdentifier;
    class D1MainService : public B1MainService {
    public:
        D1MainService(std::shared_ptr<D1ProductIdentifier> productIdentifier, int32 version, B1String&& buildDate, B1String&& systemName);
        virtual ~D1MainService();
    private:
        enum CONSTS {
            CONSTS_REDIS_TIME_CHECK_INTERVAL = 1 * 60 * 1000,
            CONSTS_DISABLE_PERFORMANCE_CHECK = 0,
            CONSTS_PERFORMANCE_CHECK_LOG_INTERVAL = 10 * 60 * 1000,
        };
    private:
        std::shared_ptr<D1ProductIdentifier> _productIdentifier;
        std::shared_ptr<B1PerformanceProfiler> _performanceProfiler;
        std::shared_ptr<B1RedisDirectClient> _redisDirectClient;
        std::shared_ptr<D1RedisClientInterface> _redisClientInterface;
        B1TimeChecker _performanceCheckTimer;
        B1TimeChecker _performanceCheckLogTimer;
        B1TimeChecker _redisTimeCheckTimer;
    private:
        void checkPerformance();
        void syncWithRedisTime();
    protected:
        virtual bool useSyncWithRedisTime() const { return false; }
        virtual uint32 performanceProfilerInterval() const { return CONSTS_DISABLE_PERFORMANCE_CHECK; } //  return 0 if disable performance_profiler
        virtual auto initializeRedisClient() -> B1RedisDirectClient* = 0;
        virtual void onCheckPerformance(uint32 pid, int64 memUsage, int64 memTotal, float64 memUsagePercent, float64 cpuUsagePercent) {}
        virtual B1String serviceInfoKey() const;
    protected:
        virtual bool implStart() override;
        virtual bool implWorking() override;
        virtual void implStop() override;
    public:
        bool isRedisCanReadWrite() const;
        B1String serviceName() const;
        D1ProductIdentifier* productIdentifier() const { return _productIdentifier.get(); }
        D1RedisClientInterface* redisClientInterface() const { return _redisClientInterface.get(); }
    };
}   //  !BnD

#endif  // !_D1BASE_MAIN_SERVICE_H
