//
// D1GUIMsgZoneInfosReq.h
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_GUI_MSG_ZONE_INFOS_REQ_H
#define _D1MESSAGE_GUI_MSG_ZONE_INFOS_REQ_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1GUIMsgZoneInfosReq : public D1BaseMessage {
    public:
        D1GUIMsgZoneInfosReq();
        D1GUIMsgZoneInfosReq(D1BaseMessage&& baseMessage);
        virtual ~D1GUIMsgZoneInfosReq();
    protected:
        DataVectorInt32 _ownerIDs;  //  empty for all zones.
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        const std::vector<int32>& ownerIDs() const { return _ownerIDs.second; }
              std::vector<int32>& ownerIDs()       { return _ownerIDs.second; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1GUIMsgZoneInfosReq");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_GUI_MSG_ZONE_INFOS_REQ_H
