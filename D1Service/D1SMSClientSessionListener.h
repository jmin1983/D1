//
// D1SMSClientSessionListener.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_CLIENT_SESSION_LISTENER_H
#define _D1SERVICE_SMS_CLIENT_SESSION_LISTENER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseClientSessionMessageListener.h>

namespace BnD {
    class D1SMSClientSessionListener : public D1BaseClientSessionMessageListener {
    public:
        virtual void onSMSClientDisconnnected(int32 reason) {}
        virtual void onRecvSMSClientDataHostAddressesRsp(std::vector<B1String>&& addresses) {}
        virtual void onRecvSMSClientDataHostNameRsp(const B1String& name) {}
        virtual void onRecvSMSClientDataSystemResourceUsagesRsp(const B1String& usages) {}
        virtual void onRecvSMSClientDataStartSystemServiceRsp(const B1String& name, bool result) {}
        virtual void onRecvSMSClientDataStopSystemServiceRsp(const B1String& name, bool result) {}
        virtual void onRecvSMSClientDataStatusSystemServiceRsp(const B1String& name, bool result, bool isActive) {}
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_CLIENT_SESSION_LISTENER_H
