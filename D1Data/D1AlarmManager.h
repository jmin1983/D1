//
// D1AlarmManager.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_ALARM_MANAGER_H
#define _D1DATA_ALARM_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Base/B1Singleton.h>

#include <list>

namespace BnD {
    class D1Alarm;
    class D1RedisClientInterface;
    class D1AlarmReader : public B1Singleton<D1AlarmReader> {
    public:
        D1AlarmReader();
        virtual ~D1AlarmReader();
    protected:
        D1RedisClientInterface* _redisClientInterface;
    protected:
        virtual void implInitialize(D1RedisClientInterface* redisClientInterface);
        virtual void implFinalize();
    public:
        void initialize(D1RedisClientInterface* redisClientInterface);
        void finalize();
        std::shared_ptr<D1Alarm> getAlarmInfo(int64 serialNumber) const;
        std::list<std::shared_ptr<D1Alarm> > getAllAlarmInfos() const;      //  WARNING: do not use too often. it scans all data.
    };

    class D1AlarmWriter : public D1AlarmReader {
    public:
        D1AlarmWriter();
    protected:
        virtual int64 implMakeNewSerialNumber() = 0;
        virtual void implLogAlarm(int64 serialNumber, int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, B1String&& carrierID, B1String&& data) {}
    protected:
        int64 makeNewSerialNumber();
    public:
        bool clearAlarm(int64 serialNumber, int32 serviceID, const B1String& resolvedBy);
        bool addAlarm(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason);
        bool addAlarm(int32 code, int32 serviceID, int32 zoneID, int64 taskID, int32 reason, B1String&& carrierID, B1String&& data = "");
    };
}   //  !BnD

#endif  // !_D1DATA_ALARM_MANAGER_H
