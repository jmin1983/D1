//
// D1SMSClientSession.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_CLIENT_SESSION_H
#define _D1SERVICE_SMS_CLIENT_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseClientSession.h>
#include <D1Service/D1SMSProtocol.h>

namespace BnD {
    class D1SMSPacketMaker;
    class D1SMSClientSessionListener;
    class D1SMSClientSession : public D1BaseClientSession {
    public:
        D1SMSClientSession(int32 clientID, B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener, D1SMSPacketMaker* packetMaker, int32 maxAliveCount,
                           D1SMSClientSessionListener* smslistener);
    protected:
        virtual void implOnProtocolTypeHostAddressesRsp(const B1String& addressesString);
        virtual void implOnProtocolTypeHostNameRsp(const B1String& name);
        virtual void implOnProtocolTypeSystemResourceUsagesRsp(const B1String& usages);
        virtual void implOnProtocolTypeStartSystemServiceRsp(const B1String& name, bool result);
        virtual void implOnProtocolTypeStopSystemServiceRsp(const B1String& name, bool result);
        virtual void implOnProtocolTypeStatusSystemServiceRsp(const B1String& name, bool result, bool isActive);
    protected:
        ANALYZE_RESULT implAnalyzeData(const D1BaseProtocol::Header& header, uint8* data, size_t size, size_t* pos) final;
        void implOnDisconnected(int32 reason) final;
    protected:
        D1SMSPacketMaker* packetMaker() const;
        D1SMSClientSessionListener* smsClientlistener() const;
        B1String getOperationEncString(D1SMSProtocol::OPERATION operation) const;
        ANALYZE_RESULT analyzeDataTypeString(uint8* data, size_t size, size_t* pos, B1String* string) const;
        ANALYZE_RESULT analyzeProtocolTypeHostAddressesRsp(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeHostNameRsp(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeSystemResourceUsagesRsp(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStartSystemServiceRsp(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStopSystemServiceRsp(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStatusSystemServiceRsp(uint8* data, size_t size, size_t* pos);
    public:
        bool sendDropCacheMemoryNtf();
        bool sendRebootSystemNtf();
        bool sendHostAddressesReq();
        bool sendHostNameReq();
        bool sendSystemResourceUsagesReq();
        bool sendStartSystemServiceReq(const B1String& name);
        bool sendStopSystemServiceReq(const B1String& name);
        bool sendStatusSystemServiceReq(const B1String& name);
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_CLIENT_SESSION_H
