//
// D1SMSPacketMaker.h
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SERVICE_SMS_PACKET_MAKER_H
#define _D1SERVICE_SMS_PACKET_MAKER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Network/D1BasePacketMaker.h>

namespace BnD {
    class D1SMSPacketMaker : public D1BasePacketMaker {
    protected:
        void appendDataString(const B1String& string, std::vector<uint8>* data) const;
    public:
        std::vector<uint8> makeDataOperationNtf(const B1String& operation) const;
        std::vector<uint8> makeDataHostAddressesReq() const;
        std::vector<uint8> makeDataHostAddressesRsp(const B1String& addressesString) const;
        std::vector<uint8> makeDataHostNameReq() const;
        std::vector<uint8> makeDataHostNameRsp(const B1String& name) const;
        std::vector<uint8> makeDataSystemResourceUsagesReq() const;
        std::vector<uint8> makeDataSystemResourceUsagesRsp(const B1String& usages) const;
        std::vector<uint8> makeDataStartSystemServiceReq(const B1String& name) const;
        std::vector<uint8> makeDataStartSystemServiceRsp(const B1String& name, bool result) const;
        std::vector<uint8> makeDataStopSystemServiceReq(const B1String& name) const;
        std::vector<uint8> makeDataStopSystemServiceRsp(const B1String& name, bool result) const;
        std::vector<uint8> makeDataStatusSystemServiceReq(const B1String& name) const;
        std::vector<uint8> makeDataStatusSystemServiceRsp(const B1String& name, bool result, bool isActive) const;
    };
}   //  !BnD

#endif  // !_D1SERVICE_SMS_PACKET_MAKER_H
