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

std::vector<uint8> D1BasePacketMaker::makeDataNotifyID(int32 id)
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

std::vector<uint8> D1BasePacketMaker::makeDataTextMessage(const B1String& message)
{
    D1BaseProtocol::Header header(D1BaseProtocol::Header::TYPE_TEXT_MESSAGE);
    uint32 dataLength = TO_UINT32_FOR_NETWORK(message.length() + 1);
    const size_t headerSize = sizeof(header);
    const size_t dataLengthSize = sizeof(dataLength);
    const size_t dataSize = message.length();
    std::vector<uint8> buffer(headerSize + dataLengthSize + dataSize + 1, 0);   //  include end of string
    memcpy(&buffer[0], &header, headerSize);
    memcpy(&buffer[0] + headerSize, &dataLength, dataLengthSize);
    memcpy(&buffer[0] + headerSize + dataLengthSize, message.cString(), dataSize);
    return buffer;
}
