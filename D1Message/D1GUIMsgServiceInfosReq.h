//
// D1GUIMsgServiceInfosReq.h
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_GUI_MSG_SERVICE_INFOS_REQ_H
#define _D1MESSAGE_GUI_MSG_SERVICE_INFOS_REQ_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1GUIMsgServiceInfosReq : public D1BaseMessage {
    public:
        D1GUIMsgServiceInfosReq();
        D1GUIMsgServiceInfosReq(D1BaseMessage&& baseMessage);
        virtual ~D1GUIMsgServiceInfosReq();
    protected:
        DataVectorInt32 _serviceIDs;    //  empty for all zones.
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        const std::vector<int32>& serviceIDs() const { return _serviceIDs.second; }
              std::vector<int32>& serviceIDs()       { return _serviceIDs.second; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1GUIMsgServiceInfosReq");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_GUI_MSG_SERVICE_INFOS_REQ_H
