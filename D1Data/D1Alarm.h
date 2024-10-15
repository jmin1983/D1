//
// D1Alarm.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_ALARM_H
#define _D1DATA_ALARM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Data/D1RedisHashmapObject.h>

namespace BnD {
    class D1Alarm : public D1RedisHashmapObject {
    public:
        D1Alarm(int64 serialNumber);
        D1Alarm(int64 serialNumber, int64 taskID, int32 zoneID, int32 serviceID, int32 code, int32 reason, B1String&& carrierID);
        virtual ~D1Alarm();
    private:
        static const B1String _alarmKey;
        DataInt64 _serialNumber;
    protected:
        DataInt64 _taskID;
        DataInt32 _zoneID;
        DataInt32 _serviceID;
        DataInt32 _code;
        DataInt32 _reason;
        DataString _carrierID;
    protected:
        B1String redisKey() const final;
        bool isValidToMakeRedisString() const final;
        void makeRedisStringArgs(std::vector<B1String>* args) const final;
        bool readRedisMap(const std::map<B1String, B1String>& map) final;
    public:
        int64 serialNumber() const { return _serialNumber.second; }
        int32 code() const { return _code.second; }
        int64 taskID() const { return _taskID.second; }
        int32 zoneID() const { return _zoneID.second; }
        int32 serviceID() const { return _serviceID.second; }
        int32 reason() const { return _reason.second; }
        const B1String& carrierID() const { return _carrierID.second; }

        void setCode(int32 value) { _code.second = value; }
        void setTaskID(int64 value) { _taskID.second = value; }
        void setZoneID(int32 value) { _zoneID.second = value; }
        void setServiceID(int32 value) { _serviceID.second = value; }
        void setReason(int32 value) { _reason.second = value; }
        void setCarrierID(B1String&& value) { _carrierID.second = std::move(value); }
    public:
        static const B1String& alarmKey() { return _alarmKey; }
        static B1String redisKey(int64 serialNumber);
    };
}   //  !BnD

#endif  // !_D1DATA_ALARM_H
