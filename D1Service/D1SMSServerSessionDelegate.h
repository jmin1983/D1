//
// D1SMSServerSessionDelegate.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_SERVER_SESSION_DELEGATE_H
#define _D1SERVICE_SMS_SERVER_SESSION_DELEGATE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Service/D1SMSProtocol.h>

#include <list>

namespace BnD {
    class D1SMSServerSessionDelegate {
    public:
        virtual void implSMSServerOperationNtf(D1SMSProtocol::OPERATION operation) = 0;
        virtual std::list<B1String> implSMSServerHostAddressesReq() = 0;
        virtual B1String implSMSServerHostNameReq() = 0;
        virtual B1String implSMSServerSystemResourceUsagesReq() = 0;
        virtual bool implSMSServerStartSystemServiceReq(const B1String& name) = 0;                  //  return true if success.
        virtual bool implSMSServerStopSystemServiceReq(const B1String& name) = 0;                   //  return true if success.
        virtual bool implSMSServerStatusSystemServiceReq(const B1String& name, bool* isActive) = 0; //  return true if success.
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_SERVER_SESSION_DELEGATE_H
