//
// D1MsgAlarmClearReq.h
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_ALARM_CLEAR_REQ_H
#define _D1MESSAGE_MSG_ALARM_CLEAR_REQ_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgAlarmClearReq : public D1BaseMessage {
    public:
        D1MsgAlarmClearReq();
        D1MsgAlarmClearReq(D1BaseMessage&& baseMessage);
        virtual ~D1MsgAlarmClearReq();
    protected:
        DataInt64 _serialNumber;
        DataInt32 _zoneID;
        DataString _resolvedBy;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int64 serialNumber() const { return _serialNumber.second; }
        int32 zoneID() const { return _zoneID.second; }
        const B1String& resolvedBy() const { return _resolvedBy.second; }
        
        void setSerialNumbererialNo(int64 value) { _serialNumber.second = value; }
        void setZoneID(int32 value) { _zoneID.second = value; }
        void setResolvedBy(B1String&& value) { _resolvedBy.second = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgAlarmClearReq");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_ALARM_CLEAR_REQ_H
