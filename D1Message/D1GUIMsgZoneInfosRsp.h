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
        DataVectorString _zoneStrings;
        DataVectorString _zoneGUIDataStrings;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 index() const { return _index.second; }
        int32 indexCount() const { return _indexCount.second; }
        const std::vector<B1String>& zoneStrings() const { return _zoneStrings.second; }
              std::vector<B1String>& zoneStrings()       { return _zoneStrings.second; }
        const std::vector<B1String>& zoneGUIDataStrings() const { return _zoneGUIDataStrings.second; }
              std::vector<B1String>& zoneGUIDataStrings()       { return _zoneGUIDataStrings.second; }

        void setIndex(int32 value) { _index.second = value; }
        void setIndexCount(int32 value) { _indexCount.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1GUIMsgZoneInfosRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_GUI_MSG_ZONE_INFOS_RSP_H
