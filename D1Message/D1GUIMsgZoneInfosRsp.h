//
// D1GUIMsgZoneInfosRsp.h
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_GUI_MSG_ZONE_INFOS_RSP_H
#define _D1MESSAGE_GUI_MSG_ZONE_INFOS_RSP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1GUIMsgZoneInfosRsp : public D1BaseMessage {
    public:
        D1GUIMsgZoneInfosRsp();
        D1GUIMsgZoneInfosRsp(D1BaseMessage&& baseMessage);
        virtual ~D1GUIMsgZoneInfosRsp();
    protected:
        DataInt32 _index;
        DataInt32 _indexCount;
        DataString _zoneString;
        DataString _zoneGUIDataString;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 index() const { return _index.second; }
        int32 indexCount() const { return _indexCount.second; }
        const B1String& zoneString() const { return _zoneString.second; }
        const B1String& zoneGUIDataString() const { return _zoneGUIDataString.second; }

        void setIndex(int32 value) { _index.second = value; }
        void setIndexCount(int32 value) { _indexCount.second = value; }
        void setZoneString(B1String&& value) { _zoneString.second = std::move(value); }
        void setZoneGUIDataString(B1String&& value) { _zoneGUIDataString.second = std::move(value); }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1GUIMsgZoneInfosRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_GUI_MSG_ZONE_INFOS_RSP_H
