//
// D1MsgAlarmRemoteNtf.h
//
// Library: D1Message
// Package: AlarmEvent
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_ALARM_REMOTE_NTF_H
#define _D1MESSAGE_MSG_ALARM_REMOTE_NTF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgAlarmRemoteNtf : public D1BaseMessage {
    public:
        D1MsgAlarmRemoteNtf(int64 taskID, int32 zoneID, int32 serviceID, int32 code, int32 reason);
        D1MsgAlarmRemoteNtf(D1BaseMessage&& baseMessage);
        virtual ~D1MsgAlarmRemoteNtf();
    protected:
        DataInt64 _taskID;
        DataInt32 _zoneID;
        DataInt32 _serviceID;
        DataInt32 _code;
        DataInt32 _reason;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int64 taskID() const { return _taskID.second; }
        int32 zoneID() const { return _zoneID.second; }
        int32 serviceID() const { return _serviceID.second; }
        int32 code() const { return _code.second; }
        int32 reason() const { return _reason.second; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgAlarmRemoteNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_ALARM_REMOTE_NTF_H
