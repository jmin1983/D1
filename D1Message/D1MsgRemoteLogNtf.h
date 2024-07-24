//
// D1MsgRemoteLogNtf.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_REMOTE_LOG_NTF_H
#define _D1MESSAGE_MSG_REMOTE_LOG_NTF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgRemoteLogNtf : public D1BaseMessage {
    public:
        D1MsgRemoteLogNtf();
        D1MsgRemoteLogNtf(D1BaseMessage&& baseMessage);
        virtual ~D1MsgRemoteLogNtf();
    protected:
        enum LEVEL {
            LEVEL_UNKNOWN = -1,
            LEVEL_DEBUG = 0,
            LEVEL_INFO = 1,
            LEVEL_ERROR = 2,
        };
    protected:
        DataInt32 _level;
        DataInt32 _serviceID;
        DataInt32 _taskID;
        DataInt32 _zoneID;
        DataString _comment;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    protected:
        void set(LEVEL level, int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment);
    public:
        void setDebug(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment);
        void setInfo(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment);
        void setError(int32 serviceID, int32 taskID, int32 zoneID, B1String&& comment);

        bool isDebug() const { return LEVEL_DEBUG == _level.second; }
        bool isInfo() const { return LEVEL_INFO == _level.second; }
        bool isError() const { return LEVEL_ERROR == _level.second; }
        bool serviceID() const { return _serviceID.second; }
        bool taskID() const { return _taskID.second; }
        bool zoneID() const { return _zoneID.second; }
        const B1String& comment() const { return _comment.second; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgRemoteLogNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_REMOTE_LOG_NTF_H
