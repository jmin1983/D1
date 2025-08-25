//
// D1SMSPacketMaker.cpp
//
// Library: D1Service
// Package: SMS
// Module:  D1Service
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Service.h"
#include "D1SMSPacketMaker.h"
#include "D1SMSProtocol.h"

#include <B1Base/B1Endian.h>

using namespace BnD;

void D1SMSPacketMaker::appendDataString(const B1String& string, std::vector<uint8>* data) const
{
    uint32 stringLength = TO_UINT32_FOR_NETWORK(string.length() + 1);   //  include end of string.
    data->insert(data->end(), (uint8*)&stringLength, (uint8*)&stringLength + sizeof(stringLength));
    data->insert(data->end(), string.cString(), string.cString() + string.length());
    data->push_back(0); //  include end of string;
}

auto D1SMSPacketMaker::makeDataOperationNtf(const B1String& operation) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_OPERATION_NTF);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(operation, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataHostAddressesReq() const -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_HOST_ADDRESSES_REQ);
    return std::vector<uint8>((uint8*)&header, (uint8*)&header + sizeof(header));
}

auto D1SMSPacketMaker::makeDataHostAddressesRsp(const B1String& addressesString) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_HOST_ADDRESSES_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(addressesString, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataHostNameReq() const -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_HOST_NAME_REQ);
    return std::vector<uint8>((uint8*)&header, (uint8*)&header + sizeof(header));
}

auto D1SMSPacketMaker::makeDataHostNameRsp(const B1String& name) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_HOST_NAME_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataSystemResourceUsagesReq() const -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_SYSTEM_RESOURCE_USAGES_REQ);
    return std::vector<uint8>((uint8*)&header, (uint8*)&header + sizeof(header));
}

auto D1SMSPacketMaker::makeDataSystemResourceUsagesRsp(const B1String& usages) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_SYSTEM_RESOURCE_USAGES_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(usages, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStartSystemServiceReq(const B1String& name) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_START_SYSTEM_SERVICE_REQ);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStartSystemServiceRsp(const B1String& name, bool result) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_START_SYSTEM_SERVICE_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    buffer.push_back(result ? 1 : 0);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStopSystemServiceReq(const B1String& name) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_STOP_SYSTEM_SERVICE_REQ);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStopSystemServiceRsp(const B1String& name, bool result) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_STOP_SYSTEM_SERVICE_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    buffer.push_back(result ? 1 : 0);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStatusSystemServiceReq(const B1String& name) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_STATUS_SYSTEM_SERVICE_REQ);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    return buffer;
}

auto D1SMSPacketMaker::makeDataStatusSystemServiceRsp(const B1String& name, bool result, bool isActive) const -> std::vector<uint8>
{
    std::vector<uint8> buffer;
    buffer.reserve(1024);
    D1BaseProtocol::Header header(D1SMSProtocol::TYPE_STATUS_SYSTEM_SERVICE_RSP);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    appendDataString(name, &buffer);
    buffer.push_back(result ? 1 : 0);
    buffer.push_back(isActive ? 1 : 0);
    return buffer;
}
