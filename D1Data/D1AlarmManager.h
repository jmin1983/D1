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
    class B1Lock;
    class D1Alarm;
    class D1Zone;
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
        std::shared_ptr<B1Lock> _alarmLock;
    protected:
        virtual int64 implMakeNewSerialNumber() = 0;
        virtual void onAlarmAdded(int64 serialNumber, int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone, const B1String& carrierID, const B1String& data);
        virtual void onAlarmCleared(int64 serialNumber, int32 serviceID, int32 zoneID);
    protected:
        int64 makeNewSerialNumber();
    public:
        bool addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason);
        bool addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone);
        bool addAlarm(int32 code, int32 serviceID, int64 taskID, int32 reason, const D1Zone* zone, const B1String& carrierID, B1String&& data = "");
        bool clearAlarm(int64 serialNumber, int32 serviceID);
        bool clearAlarm(int64 serialNumber, int32 serviceID, const D1Zone* zone);
    };
}   //  !BnD

#endif  // !_D1DATA_ALARM_MANAGER_H
