//
// D1DCSMsgZoneInfosReq.h
//
// Library: D1Message
// Package: DCS
// Module:  D1Message
//
// Copyright (c) 2023-2024, Semi-TS.
// All rights reserved.
//

#ifndef _D1MESSAGE_DCS_MSG_ZONE_INFOS_REQ_H
#define _D1MESSAGE_DCS_MSG_ZONE_INFOS_REQ_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1DCSMsgZoneInfosReq : public D1BaseMessage {
    public:
        D1DCSMsgZoneInfosReq();
        D1DCSMsgZoneInfosReq(D1BaseMessage&& baseMessage);
        virtual ~D1DCSMsgZoneInfosReq();
    protected:
        DataInt32 _ownerID;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 ownerID() const { return _ownerID.second; }

        void setOwnerID(int32 value) { _ownerID.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1DCSMsgZoneInfosReq");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_DCS_MSG_ZONE_INFOS_REQ_H
