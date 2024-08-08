//
// D1MsgAlarmClearRsp.h
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_ALARM_CLEAR_RSP_H
#define _D1MESSAGE_MSG_ALARM_CLEAR_RSP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgAlarmClearRsp : public D1BaseMessage {
    public:
        D1MsgAlarmClearRsp(int64 serialNumber, int32 serviceID, int32 zoneID, bool alarmCleared);
        D1MsgAlarmClearRsp(D1BaseMessage&& baseMessage);
        virtual ~D1MsgAlarmClearRsp();
    protected:
        DataInt64 _serialNumber;
        DataInt32 _zoneID;
        DataInt32 _serviceID;   //  which service handled the alarm.
        DataBool _alarmCleared;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int64 serialNumber() const { return _serialNumber.second; }
        int32 zoneID() const { return _zoneID.second; }
        int32 serviceID() const { return _serviceID.second; }
        bool isAlarmCleared() const { return _alarmCleared.second; }
        
        void setSerialNumbererialNo(int64 value) { _serialNumber.second = value; }
        void setZoneID(int32 value) { _zoneID.second = value; }
        void setServiceID(int32 value) { _serviceID.second = value; }
        void setAlarmCleared(bool value) { _alarmCleared.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgAlarmClearRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_ALARM_CLEAR_RSP_H
