//
// D1MsgEventNtf.h
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_EVENT_NTF_H
#define _D1MESSAGE_MSG_EVENT_NTF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgEventNtf : public D1BaseMessage {
    public:
        D1MsgEventNtf(int64 serialNumber, int32 code);
        D1MsgEventNtf(D1BaseMessage&& baseMessage);
        virtual ~D1MsgEventNtf();
    protected:
        DataInt64 _serialNumber;
        DataInt64 _taskID;
        DataInt32 _zoneID;
        DataInt32 _serviceID;
        DataInt32 _code;
        DataInt32 _reason;
        DataString _carrierID;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int64 serialNumber() const { return _serialNumber.second; }
        int64 taskID() const { return _taskID.second; }
        int32 zoneID() const { return _zoneID.second; }
        int32 serviceID() const { return _serviceID.second; }
        int32 code() const { return _code.second; }
        int32 reason() const { return _reason.second; }
        const B1String& carrierID() const { return _carrierID.second; }

        void setTaskID(int64 value) { _taskID.second = value; }
        void setZoneID(int32 value) { _zoneID.second = value; }
        void setServiceID(int32 value) { _serviceID.second = value; }
        void setReason(int32 value) { _reason.second = value; }
        void setCarrierID(B1String&& value) { _carrierID.second = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgEventNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_EVENT_NTF_H
