//
// D1MainServiceWrapper.h
//
// Library: D1Base
// Package: D1Base
// Module:  D1Base
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1BASE_MAIN_SERVICE_WRAPPER_H
#define _D1BASE_MAIN_SERVICE_WRAPPER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1FileLog.h>
#include <B1Base/B1Singleton.h>
#include <B1Base/B1SystemUtil.h>
#include <B1Base/B1Time.h>
#include <B1Redic/B1RedisDirectClient.h>

#include <D1Base/D1Consts.h>
#include <D1Base/D1ProductIdentifier.h>
#include <D1Base/D1RedisClientInterface.h>

namespace BnD {
    template <typename T, typename U>
    class D1MainServiceWrapper : public B1Singleton<U> {
    public:
        D1MainServiceWrapper() {}
        virtual ~D1MainServiceWrapper() { deinitFileLog(); }
    protected:
        std::shared_ptr<T> _service;
        std::shared_ptr<B1FileLog> _fileLog;
    protected:
        bool initFileLog(B1String&& logFilePath, B1String&& fileName, int32 logCounts)
        {
            if (_fileLog != NULL) {
                return false;
            }
            _fileLog.reset(new B1FileLog());
            if (_fileLog->start(std::move(logFilePath), std::move(fileName), logCounts) != true) {
                _fileLog.reset();
                return false;
            }
            setLogger(_fileLog.get());
            return true;
        }
        void deinitFileLog()
        {
            if (_fileLog) {
                setLogger(NULL);
                _fileLog->stop();
                _fileLog.reset();
            }
        }
        void syncWithRedisTime(D1RedisClientInterface* redisClient) const
        {
            uint64 redisSeconds = 0;
            uint32 redisMicroSeconds = 0;
            if (redisClient->time(&redisSeconds, &redisMicroSeconds)) {
                B1Time t(static_cast<time_t64>(redisSeconds));
                B1LOG("Sync server time:[%04d-%02d-%02d %02d:%02d:%02d.%03d]", t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second(), static_cast<int32>(redisMicroSeconds / 1000));
                B1Time::setAdjustCurrentTime(redisSeconds, redisMicroSeconds);
                B1LOG("Sync server time finished");
            }
            else {
                B1LOG("sync redis time failed");
            }
        }
    protected:
        virtual T* createMainService(std::shared_ptr<D1ProductIdentifier> productIdentifier) = 0;
        virtual int32 getServiceID(D1RedisClientInterface* redisReader) = 0;
        virtual D1ProductIdentifier* createProductIdentifier(int32 serviceID) = 0;
        virtual void onMainServiceStartBefore() {}
    public:
        bool start(const B1String& address, uint16 port, int32 db, const B1String& logPath, int32 logCounts,
                   bool useServiceIDForLog = false, bool ignoreFileLogFailure = false)
        {
            if (_service) {
                printf("already started");
                assert(false);
                return false;
            }
            {
                B1RedisDirectClient client(NULL);
                if (client.initializeReadOnly(address, port, db) != true) {
                    B1String errorMessage(B1String::formatAs("unable to connect Administration Service: address[%s], port[%d], db[%d]", address.cString(), port, db));
                    printf("%s\n", errorMessage.cString());
                    if (FILE* fp = fopen((B1SystemUtil::getCurrentDirectory() + "/can_not_connect_to_server.err").cString(), "w")) {
                        fwrite(errorMessage.cString(), sizeof(char), errorMessage.length(), fp);
                        fclose(fp);
                    }
                    assert(false);
                    return false;
                }
                D1RedisClientInterface clientInterface(&client);
                syncWithRedisTime(&clientInterface);
                int32 serviceID = getServiceID(&clientInterface);
                std::shared_ptr<D1ProductIdentifier> productIdentifier(createProductIdentifier(serviceID));
                productIdentifier->getProductInfo(&clientInterface);
                const B1String logFilePath = logPath + "/" + productIdentifier->serviceName();
                B1String serviceNameLower(productIdentifier->serviceName());
                serviceNameLower.makeLower();
                const B1String logFileName = useServiceIDForLog ? B1String::formatAs("%s_%d", serviceNameLower.cString(), serviceID) : serviceNameLower;
                if (initFileLog(logFilePath.copy(), logFileName.copy(), logCounts) != true) {
                    if (ignoreFileLogFailure != true) {
                        B1String errorMessage(B1String::formatAs("unable to start log file[%s/%s]\n", logFilePath.cString(), logFileName.cString()));
                        printf("%s\n", errorMessage.cString());
                        if (FILE* fp = fopen((B1SystemUtil::getCurrentDirectory() + "/can_not_create_log.err").cString(), "w")) {
                            fwrite(errorMessage.cString(), sizeof(char), errorMessage.length(), fp);
                            fclose(fp);
                        }
                        client.finalize();
                        assert(false);
                        return false;
                    }
                }
                B1LOG("initializing service: name[%s]", productIdentifier->serviceName().cString());
                B1LOG("cleanup product initializer -> disconnect sessions: site[%d], type[%d]", productIdentifier->site(), productIdentifier->type());
                client.finalize();
                _service.reset(createMainService(productIdentifier));
            }
            if (_service == NULL) {
                printf("create control service failed");
                assert(false);
                return false;
            }

            B1LOG("starting %s", _service->toString().cString());
            onMainServiceStartBefore();
            if (_service->start() != true) {
                b1log("start failed %s", _service->toString().cString());
                _service->stop();
                return false;
            }
            //onMainServiceStartAfter();
            B1LOG("%s started", _service->toString().cString());
            return true;
        }
        void wait()
        {
            if (_service) {
                _service->wait();
                B1LOG("%s stopped", _service->toString().cString());
            }
        }
        void stop()
        {
            if (_service) {
                B1LOG("stopping %s", _service->toString().cString());
                _service->stop();
            }
        }
        bool isStopped() const
        {
            return _service ? _service->isStopped() : false;
        }
        B1String serviceName()
        {
            return _service ? _service->mainServiceName().copy() : "unknown";
        }
    };
}   //  !BnD

#endif  // !_D1BASE_MAIN_SERVICE_WRAPPER_H
