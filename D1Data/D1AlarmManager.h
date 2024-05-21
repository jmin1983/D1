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

#include <set>

namespace BnD {
    class D1Alarm;
    class D1RedisClientInterface;
    class D1AlarmReader : public B1Singleton<D1AlarmReader> {
    public:
        D1AlarmReader();
        virtual ~D1AlarmReader();
    protected:
        const B1String _prefixRecord;
        const B1String _keyActive;
        D1RedisClientInterface* _redisClientInterface;
    protected:
        virtual void implInitialize(D1RedisClientInterface* redisClientInterface);
        virtual void implFinalize();
    protected:
        bool getTaskTransferInfo(int32 taskID, B1String* commandID, B1String* carrierID);
    public:
        void initialize(D1RedisClientInterface* redisClientInterface);
        void finalize();
        std::shared_ptr<D1Alarm> getAlarmInfo(int64 serialNumber) const;
        bool getActiveAlarmSerialNumbers(std::set<int64>* serialNumbers) const;
        bool getActiveAlarmCodes(std::set<int32>* codes) const;
        bool isAlarmActivated() const;
        bool isAlarmActivated(int32 zoneID) const;
    };

    class AlarmWriter : public D1AlarmReader {
    protected:
        virtual int64 implMakeNewSerialNumber() = 0;
    protected:
        int64 makeNewSerialNumber();
    };
}   //  !BnD

#endif  // !_D1DATA_ALARM_MANAGER_H
