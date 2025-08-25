//
// D1SMSServerSession.cpp
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1SMSServerSession.h"
#include "D1SMSPacketMaker.h"
#include "D1SMSProtocol.h"
#include "D1SMSServerSessionDelegate.h"

#include <B1Base/B1Endian.h>
#include <B1Crypto/B1Encryptor.h>

#include <D1Data/D1StringArrayObject.h>

using namespace BnD;

D1SMSServerSession::D1SMSServerSession(B1ServerSocket* serverSocket, B1BaseServerSessionListener* listener, D1BaseServer* owner, int32 maxAliveCount,
                                               D1SMSServerSessionDelegate* smsServerDelegate)
    : D1BaseServerSession(serverSocket, listener, owner, maxAliveCount)
    , _smsServerDelegate(smsServerDelegate)
{
}

void D1SMSServerSession::implOnProtocolTypeOperationNtf(const B1String& operation)
{
    smsServerDelegate()->implSMSServerOperationNtf(analyzeOperation(operation));
}

void D1SMSServerSession::implOnProtocolTypeHostAddressesReq()
{
    auto addresses = smsServerDelegate()->implSMSServerHostAddressesReq();
    D1StringArrayObject arrayObject;
    arrayObject.values().reserve(addresses.size());
    for (auto& address : addresses) {
        arrayObject.values().push_back(std::move(address));
    }
    B1String addressesString;
    arrayObject.archiveToString(&addressesString);
    sendHostAddressesRsp(addressesString);
}

void D1SMSServerSession::implOnProtocolTypeHostNameReq()
{
    auto name = smsServerDelegate()->implSMSServerHostNameReq();
    sendHostNameRsp(name);
}

void D1SMSServerSession::implOnProtocolTypeSystemResourceUsagesReq()
{
    auto usages = smsServerDelegate()->implSMSServerSystemResourceUsagesReq();
    sendSystemResourceUsagesRsp(usages);
}

void D1SMSServerSession::implOnProtocolTypeStartSystemService(const B1String& name)
{
    bool result = smsServerDelegate()->implSMSServerStartSystemServiceReq(name);
    sendStartSystemServiceRsp(name, result);
}

void D1SMSServerSession::implOnProtocolTypeStopSystemService(const B1String& name)
{
    bool result = smsServerDelegate()->implSMSServerStopSystemServiceReq(name);
    sendStopSystemServiceRsp(name, result);
}

void D1SMSServerSession::implOnProtocolTypeStatusSystemService(const B1String& name)
{
    bool isActive = false;
    bool result = smsServerDelegate()->implSMSServerStatusSystemServiceReq(name, &isActive);
    sendStatusSystemServiceRsp(name, result, isActive);
}

auto D1SMSServerSession::implAnalyzeData(const D1BaseProtocol::Header& header, uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    switch (header._type) {
        case D1SMSProtocol::TYPE_OPERATION_NTF:
            return analyzeProtocolTypeOperationNtf(data, size, pos);
        case D1SMSProtocol::TYPE_HOST_ADDRESSES_REQ:
            return analyzeProtocolTypeHostAddressesReq(data, size, pos);
        case D1SMSProtocol::TYPE_HOST_NAME_REQ:
            return analyzeProtocolTypeHostNameReq(data, size, pos);
        case D1SMSProtocol::TYPE_SYSTEM_RESOURCE_USAGES_REQ:
            return analyzeProtocolTypeSystemResourceUsagesReq(data, size, pos);
        case D1SMSProtocol::TYPE_START_SYSTEM_SERVICE_REQ:
            return analyzeProtocolTypeStartSystemServiceReq(data, size, pos);
        case D1SMSProtocol::TYPE_STOP_SYSTEM_SERVICE_REQ:
            return analyzeProtocolTypeStopSystemServiceReq(data, size, pos);
        case D1SMSProtocol::TYPE_STATUS_SYSTEM_SERVICE_REQ:
            return analyzeProtocolTypeStatusSystemServiceReq(data, size, pos);
        default:
            break;
    }
    return D1BaseServerSession::implAnalyzeData(header, data, size, pos);
}

auto D1SMSServerSession::packetMaker() const -> D1SMSPacketMaker*
{
    return static_cast<D1SMSPacketMaker*>(D1BaseServerSession::packetMaker());
}

B1String D1SMSServerSession::getOperationEncString(D1SMSProtocol::OPERATION operation) const
{
    B1String result;
    return B1Encryptor::encryptSha256(B1String::formatAs("%d", operation), &result) ? result : "";
}

auto D1SMSServerSession::analyzeOperation(const B1String& operation) const -> D1SMSProtocol::OPERATION
{
    {
        const auto dropCacheString = getOperationEncString(D1SMSProtocol::OPERATION_DROP_CACHE_MEMORY);
        if (dropCacheString == operation) {
            return D1SMSProtocol::OPERATION_DROP_CACHE_MEMORY;
        }
    }
    {
        const auto rebootSystemString = getOperationEncString(D1SMSProtocol::OPERATION_REBOOT_SYSTEM);
        if (rebootSystemString == operation) {
            return D1SMSProtocol::OPERATION_REBOOT_SYSTEM;
        }
    }
    return D1SMSProtocol::OPERATION_UNKNOWN;
}

auto D1SMSServerSession::analyzeDataTypeString(uint8* data, size_t size, size_t* pos, B1String* string) const -> ANALYZE_RESULT
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

auto D1SMSServerSession::analyzeProtocolTypeOperationNtf(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String operation;
    auto result = analyzeDataTypeString(data, size, pos, &operation);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeOperationNtf(operation);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeHostAddressesReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    implOnProtocolTypeHostAddressesReq();
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeHostNameReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    implOnProtocolTypeHostNameReq();
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeSystemResourceUsagesReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    implOnProtocolTypeSystemResourceUsagesReq();
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeStartSystemServiceReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String name;
    auto result = analyzeDataTypeString(data, size, pos, &name);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeStartSystemService(name);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeStopSystemServiceReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String name;
    auto result = analyzeDataTypeString(data, size, pos, &name);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeStopSystemService(name);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1SMSServerSession::analyzeProtocolTypeStatusSystemServiceReq(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    B1String name;
    auto result = analyzeDataTypeString(data, size, pos, &name);
    if (result != ANALYZE_RESULT_SUCCESS) {
        return result;
    }
    implOnProtocolTypeStatusSystemService(name);
    return ANALYZE_RESULT_SUCCESS;
}

bool D1SMSServerSession::sendHostAddressesRsp(const B1String& addressesString)
{
    return sendData(packetMaker()->makeDataHostAddressesRsp(addressesString));
}

bool D1SMSServerSession::sendHostNameRsp(const B1String& name)
{
    return sendData(packetMaker()->makeDataHostNameRsp(name));
}

bool D1SMSServerSession::sendSystemResourceUsagesRsp(const B1String& usages)
{
    return sendData(packetMaker()->makeDataSystemResourceUsagesRsp(usages));
}

bool D1SMSServerSession::sendStartSystemServiceRsp(const B1String& name, bool result)
{
    return sendData(packetMaker()->makeDataStartSystemServiceRsp(name, result));
}

bool D1SMSServerSession::sendStopSystemServiceRsp(const B1String& name, bool result)
{
    return sendData(packetMaker()->makeDataStopSystemServiceRsp(name, result));
}

bool D1SMSServerSession::sendStatusSystemServiceRsp(const B1String& name, bool result, bool isActive)
{
    return sendData(packetMaker()->makeDataStatusSystemServiceRsp(name, result, isActive));
}
