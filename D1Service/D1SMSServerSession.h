//
// D1SMSServerSession.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_SERVER_SESSION_H
#define _D1SERVICE_SMS_SERVER_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BaseServerSession.h>
#include <D1Service/D1SMSProtocol.h>

namespace BnD {
    class D1SMSPacketMaker;
    class D1SMSServerSessionDelegate;
    class D1SMSServerSession : public D1BaseServerSession {
    public:
        D1SMSServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, D1BaseServer* owner, int32 maxAliveCount,
                           D1SMSServerSessionDelegate* smsServerDelegate);
    protected:
        D1SMSServerSessionDelegate* _smsServerDelegate;
    protected:
        virtual void implOnProtocolTypeOperationNtf(const B1String& operation);
        virtual void implOnProtocolTypeHostAddressesReq();
        virtual void implOnProtocolTypeHostNameReq();
        virtual void implOnProtocolTypeSystemResourceUsagesReq();
        virtual void implOnProtocolTypeStartSystemService(const B1String& name);
        virtual void implOnProtocolTypeStopSystemService(const B1String& name);
        virtual void implOnProtocolTypeStatusSystemService(const B1String& name);
    protected:
        ANALYZE_RESULT implAnalyzeData(const D1BaseProtocol::Header& header, uint8* data, size_t size, size_t* pos) final;
    protected:
        D1SMSPacketMaker* packetMaker() const;
        D1SMSServerSessionDelegate* smsServerDelegate() const { return _smsServerDelegate; }
        B1String getOperationEncString(D1SMSProtocol::OPERATION operation) const;
        D1SMSProtocol::OPERATION analyzeOperation(const B1String& operation) const;
        ANALYZE_RESULT analyzeDataTypeString(uint8* data, size_t size, size_t* pos, B1String* string) const;
        ANALYZE_RESULT analyzeProtocolTypeOperationNtf(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeHostAddressesReq(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeHostNameReq(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeSystemResourceUsagesReq(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStartSystemServiceReq(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStopSystemServiceReq(uint8* data, size_t size, size_t* pos);
        ANALYZE_RESULT analyzeProtocolTypeStatusSystemServiceReq(uint8* data, size_t size, size_t* pos);
        bool sendHostAddressesRsp(const B1String& addressesString);
        bool sendHostNameRsp(const B1String& name);
        bool sendSystemResourceUsagesRsp(const B1String& usages);
        bool sendStartSystemServiceRsp(const B1String& name, bool result);
        bool sendStopSystemServiceRsp(const B1String& name, bool result);
        bool sendStatusSystemServiceRsp(const B1String& name, bool result, bool isActive);
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_SERVER_SESSION_H
