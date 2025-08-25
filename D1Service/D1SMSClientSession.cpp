//
// D1SMSClientSession.cpp
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1SMSClientSession.h"
#include "D1SMSClientSessionListener.h"
#include "D1SMSPacketMaker.h"
#include "D1SMSProtocol.h"

#include <B1Base/B1Endian.h>
#include <B1Crypto/B1Encryptor.h>

#include <D1Data/D1StringArrayObject.h>

using namespace BnD;

D1SMSClientSession::D1SMSClientSession(int32 clientID, B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener, D1SMSPacketMaker* packetMaker, int32 maxAliveCount,
                                               D1SMSClientSessionListener* smslistener)
    : D1BaseClientSession(clientID, clientSocket, listener, packetMaker, maxAliveCount, smslistener)
{
}

void D1SMSClientSession::implOnProtocolTypeHostAddressesRsp(const B1String& addressesString)
{
    if (smsClientlistener()) {
        D1StringArrayObject arrayObject;
        arrayObject.unarchiveFromString(addressesString);
        smsClientlistener()->onRecvSMSClientDataHostAddressesRsp(std::move(arrayObject.values()));
    }
}

void D1SMSClientSession::implOnProtocolTypeHostNameRsp(const B1String& name)
{
    if (smsClientlistener()) {
        smsClientlistener()->onRecvSMSClientDataHostNameRsp(name);
    }
}

void D1SMSClientSession::implOnProtocolTypeSystemResourceUsagesRsp(const B1String& usages)
{
    if (smsClientlistener()) {
        smsClientlistener()->onRecvSMSClientDataSystemResourceUsagesRsp(usages);
    }
}

auto D1SMSClientSession::implAnalyzeData(const D1BaseProtocol::Header& header, uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    switch (header._type) {
        case D1SMSProtocol::TYPE_HOST_ADDRESSES_RSP:
            return analyzeProtocolTypeHostAddressesRsp(data, size, pos);
        case D1SMSProtocol::TYPE_HOST_NAME_RSP:
            return analyzeProtocolTypeHostNameRsp(data, size, pos);
        case D1SMSProtocol::TYPE_SYSTEM_RESOURCE_USAGES_RSP:
            return analyzeProtocolTypeSystemResourceUsagesRsp(data, size, pos);
        default:
            break;
    }
    return D1BaseClientSession::implAnalyzeData(header, data, size, pos);
}

void D1SMSClientSession::implOnDisconnected(int32 reason)
{
    if (smsClientlistener()) {
        smsClientlistener()->onSMSClientDisconnnected(reason);
    }
}

auto D1SMSClientSession::packetMaker() const -> D1SMSPacketMaker*
{
    return static_cast<D1SMSPacketMaker*>(D1BaseClientSession::packetMaker());
}

auto D1SMSClientSession::smsClientlistener() const -> D1SMSClientSessionListener*
{
    return static_cast<D1SMSClientSessionListener*>(_messageListener);
}

B1String D1SMSClientSession::getOperationEncString(D1SMSProtocol::OPERATION operation) const
{
    B1String result;
    return B1Encryptor::encryptSha256(B1String::formatAs("%d", operation), &result) ? result : "";
}

auto D1SMSClientSession::analyzeDataTypeString(uint8* data, size_t size, size_t* pos, B1String* string) const -> ANALYZE_RESULT
{
    uint32 stringLength = 0;
    const size_t stringLengthSize = sizeof(stringLength);
    if (size < stringLengthSize) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }

    memcpy(&stringLength, data, stringLengthSize);
    stringLength = TO_UINT32_FOR_NETWORK(stringLength);
    if (size < stringLengthSize + stringLength) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }

    try {
        string->from((char*)data + stringLengthSize);
    }
    catch (...) {
        B1LOG("invalid string");
        assert(false);
        return ANALYZE_RESULT_FAIL;
    }
    (*pos) += (stringLengthSize + stringLength);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSClientSession::analyzeProtocolTypeHostAddressesRsp(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String addressesString;
    auto result = analyzeDataTypeString(data, size, pos, &addressesString);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeHostAddressesRsp(addressesString);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSClientSession::analyzeProtocolTypeHostNameRsp(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String name;
    auto result = analyzeDataTypeString(data, size, pos, &name);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeHostNameRsp(name);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSClientSession::analyzeProtocolTypeSystemResourceUsagesRsp(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String usages;
    auto result = analyzeDataTypeString(data, size, pos, &usages);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeSystemResourceUsagesRsp(usages);
    return ANALYZE_RESULT_SUCCESS;
}

bool D1SMSClientSession::sendDropCacheMemoryNtf()
{
    return sendData(packetMaker()->makeDataOperationNtf(getOperationEncString(D1SMSProtocol::OPERATION_DROP_CACHE_MEMORY)));
}

bool D1SMSClientSession::sendRebootSystemNtf()
{
    return sendData(packetMaker()->makeDataOperationNtf(getOperationEncString(D1SMSProtocol::OPERATION_REBOOT_SYSTEM)));
}

bool D1SMSClientSession::sendHostAddressesReq()
{
    return sendData(packetMaker()->makeDataHostAddressesReq());
}

bool D1SMSClientSession::sendHostNameReq()
{
    return sendData(packetMaker()->makeDataHostNameReq());
}

bool D1SMSClientSession::sendSystemResourceUsagesReq()
{
    return sendData(packetMaker()->makeDataSystemResourceUsagesReq());
}

bool D1SMSClientSession::sendStartSystemServiceReq(const B1String& name)
{
    return sendData(packetMaker()->makeDataStartSystemServiceReq(name));
}

bool D1SMSClientSession::sendStopSystemServiceReq(const B1String& name)
{
    return sendData(packetMaker()->makeDataStopSystemServiceReq(name));
}

bool D1SMSClientSession::sendStatusSystemServiceReq(const B1String& name)
{
    return sendData(packetMaker()->makeDataStatusSystemServiceReq(name));
}
