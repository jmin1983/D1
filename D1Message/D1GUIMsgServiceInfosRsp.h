//
// D1GUIMsgServiceInfosRsp.h
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_GUI_MSG_SERVICE_INFOS_RSP_H
#define _D1MESSAGE_GUI_MSG_SERVICE_INFOS_RSP_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>
#include <D1Data/D1ServiceInfo.h>

namespace BnD {

    class D1GUIMsgServiceInfosRsp : public D1BaseMessage {
    public:
        D1GUIMsgServiceInfosRsp();
        D1GUIMsgServiceInfosRsp(D1BaseMessage&& baseMessage);
        virtual ~D1GUIMsgServiceInfosRsp();
    protected:
        DataInt32 _index;
        DataInt32 _indexCount;
        std::pair<const B1String, std::vector<D1ServiceInfo> > _serviceInfos;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 index() const { return _index.second; }
        int32 indexCount() const { return _indexCount.second; }
        const std::vector<D1ServiceInfo>& serviceInfos() const { return _serviceInfos.second; }
              std::vector<D1ServiceInfo>& serviceInfos()       { return _serviceInfos.second; }

        void setIndex(int32 value) { _index.second = value; }
        void setIndexCount(int32 value) { _indexCount.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1GUIMsgServiceInfosRsp");
            return s_messageString;
        }
    };
}   //  !BnD

#endif // _D1MESSAGE_GUI_MSG_SERVICE_INFOS_RSP_H
