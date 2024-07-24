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

#include <map>

namespace BnD {
    class D1Alarm {
    public:
        D1Alarm();
        D1Alarm(int64 serialNumber, int32 code, int32 taskID, int32 zoneID, int32 serviceID, int32 reason,
                B1String&& commandID, B1String&& carrierID, B1String&& activateTime, B1String&& data = "");
        virtual ~D1Alarm();
    protected:
        int64 _serialNumber;
        int32 _code;
        int32 _taskID;
        int32 _zoneID;
        int32 _serviceID;
        int32 _reason;
        B1String _commandID;
        B1String _carrierID;
        B1String _activateTime;
        B1String _clearTime;
        B1String _resolvedBy;
        B1String _data;
    protected:
        void appendRedisStringArgs(std::vector<B1String>* args, B1String&& key, int32 value) const;
        void appendRedisStringArgs(std::vector<B1String>* args, B1String&& key, const B1String& value) const;
    public:
        int64 serialNumber() const { return _serialNumber; }
        int32 code() const { return _code; }
        int32 taskID() const { return _taskID; }
        int32 zoneID() const { return _zoneID; }
        int32 serviceID() const { return _serviceID; }
        int32 reason() const { return _reason; }
        const B1String& commandID() const { return _commandID; }
        const B1String& carrierID() const { return _carrierID; }
        const B1String& activateTime() const { return _activateTime; }
        const B1String& clearTime() const { return _clearTime; }
        const B1String& resolvedBy() const { return _resolvedBy; }
        const B1String& data() const { return _data; }

        void setCode(int32 code) { _code = code; }
        void setTaskID(int32 taskID) { _taskID = taskID; }
        void setZoneID(int32 zoneID) { _zoneID = zoneID; }
        void setServiceID(int32 value) { _serviceID = value; }
        void setReason(int32 reason) { _reason = reason; }
        void setCommandID(B1String&& id) { _commandID = std::move(id); }
        void setCarrierID(B1String&& id) { _carrierID = std::move(id); }
        void setActivateTime(B1String&& t) { _activateTime = std::move(t); }
        void setClearTime(B1String&& t) { _clearTime = std::move(t); }
        void setResolvedBy(B1String&& value) { _resolvedBy = std::move(value); }
        void setData(B1String&& value) { _data = std::move(value); }

        void toRedisStringArgs(std::vector<B1String>* args) const;
        void fromRedisMap(const std::map<B1String, B1String>& map);
    };
}   //  !BnD

#endif  // !_D1DATA_ALARM_H
