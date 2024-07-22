//
// D1DCSMsgZoneInfosRsp.h
//
// Library: D1Message
// Package: DCS
// Module:  D1Message
//
// Copyright (c) 2023-2024, Semi-TS.
// All rights reserved.
//

#ifndef _D1MESSAGE_DCS_MSG_ZONE_INFOS_RSP_H
#define _D1MESSAGE_DCS_MSG_ZONE_INFOS_RSP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1DCSMsgZoneInfosRsp : public D1BaseMessage {
    public:
        D1DCSMsgZoneInfosRsp();
        D1DCSMsgZoneInfosRsp(D1BaseMessage&& baseMessage);
        virtual ~D1DCSMsgZoneInfosRsp();
    protected:
        DataString _zoneString;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        const B1String& zoneString() const { return _zoneString.second; }

        void setZoneString(B1String&& value) { _zoneString.second = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1DCSMsgZoneInfosRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_DCS_MSG_ZONE_INFOS_RSP_H
