//
// D1BasePacketMaker.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BasePacketMaker.h"
#include "D1BaseProtocol.h"

#include <B1Base/B1Endian.h>

using namespace BnD;

D1BasePacketMaker::D1BasePacketMaker()
{
}

D1BasePacketMaker::~D1BasePacketMaker()
{
}

auto D1BasePacketMaker::makeDataNotifyID(int32 id) -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_NOTIFY_ID);
    int32 data = TO_INT32_FOR_NETWORK(id);
    const size_t headerSize = sizeof(header);
    const size_t dataSize = sizeof(data);
    std::vector<uint8> buffer(headerSize + dataSize, 0);
    memcpy(&buffer[0], &header, headerSize);
    memcpy(&buffer[0] + headerSize, &data, dataSize);
    return buffer;
}

auto D1BasePacketMaker::makeDataTextMessage(const B1String& message) -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_TEXT_MESSAGE);
    uint32 dataLength = TO_UINT32_FOR_NETWORK(message.length() + 1);    //  include end of string.
    std::vector<uint8> buffer;
    buffer.reserve(sizeof(header) + sizeof(dataLength) + message.length() + 1);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    buffer.insert(buffer.end(), (uint8*)&dataLength, (uint8*)&dataLength + sizeof(dataLength));
    buffer.insert(buffer.end(), message.cString(), message.cString() + message.length());
    buffer.push_back(0);    //  include end of string;
    return buffer;
}

auto D1BasePacketMaker::makeDataTextMessageBunch(int32 index, int32 indexCount, const B1String& message) -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_TEXT_MESSAGE_BUNCH);
    int32 dataIndex = TO_INT32_FOR_NETWORK(index);
    int32 dataIndexCount = TO_INT32_FOR_NETWORK(indexCount);
    uint32 dataTextLength = TO_UINT32_FOR_NETWORK(message.length() + 1);    //  include end of string.
    std::vector<uint8> buffer;
    buffer.reserve(sizeof(header) + sizeof(dataIndex) + sizeof(dataIndexCount) + sizeof(dataTextLength) + message.length() + 1);
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    buffer.insert(buffer.end(), (uint8*)&dataIndex, (uint8*)&dataIndex + sizeof(dataIndex));
    buffer.insert(buffer.end(), (uint8*)&dataIndexCount, (uint8*)&dataIndexCount + sizeof(dataIndexCount));
    buffer.insert(buffer.end(), (uint8*)&dataTextLength, (uint8*)&dataTextLength + sizeof(dataTextLength));
    buffer.insert(buffer.end(), message.cString(), message.cString() + message.length());
    buffer.push_back(0);    //  include end of string;
    return buffer;
}

auto D1BasePacketMaker::makeDataBinary(int32 index, int32 indexCount, const std::vector<uint8>& data) -> std::vector<uint8>
{
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_BINARY);
    int32 dataIndex = TO_INT32_FOR_NETWORK(index);
    int32 dataIndexCount = TO_INT32_FOR_NETWORK(indexCount);
    uint32 dataLength = TO_UINT32_FOR_NETWORK(static_cast<uint32>(data.size()));
    std::vector<uint8> buffer;
    buffer.reserve(sizeof(header) + sizeof(dataIndex) + sizeof(dataIndexCount) + sizeof(dataLength) + data.size());
    buffer.insert(buffer.end(), (uint8*)&header, (uint8*)&header + sizeof(header));
    buffer.insert(buffer.end(), (uint8*)&dataIndex, (uint8*)&dataIndex + sizeof(dataIndex));
    buffer.insert(buffer.end(), (uint8*)&dataIndexCount, (uint8*)&dataIndexCount + sizeof(dataIndexCount));
    buffer.insert(buffer.end(), (uint8*)&dataLength, (uint8*)&dataLength + sizeof(dataLength));
    buffer.insert(buffer.end(), data.begin(), data.end());
    return buffer;
}
