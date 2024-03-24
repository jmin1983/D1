//
// D1BasePacketAnalyzer.cpp
//
// Library: D1Network
// Package: D1Network
// Module:  D1Network
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Network.h"
#include "D1BasePacketAnalyzer.h"
#include "D1BaseProtocol.h"

#include <B1Base/B1Endian.h>

using namespace BnD;

B1BasePacketAnalyzer::ANALYZE_RESULT D1BasePacketAnalyzer::implAnalyzeData(uint8* data, size_t size, size_t* pos)
{
    D1BaseProtocol::Header::TYPE type = D1BaseProtocol::Header::TYPE_UNKNOWN;
    {
        D1BaseProtocol::Header header;
        const size_t headerSize = sizeof(header);
        if (size < headerSize) {
            return ANALYZE_RESULT_NOT_ENOUTH_DATA;
        }
        memcpy(&header, data, headerSize);
        (*pos) += headerSize;
        type = static_cast<D1BaseProtocol::Header::TYPE>(header._type);
    }
    switch (type) {
        case D1BaseProtocol::Header::TYPE_ALIVE_CHECK:
            implOnProtocolTypeAliveCheck();
            break;
        case D1BaseProtocol::Header::TYPE_NOTIFY_ID:
            return analyzeProtocolTypeNotifyID(data + (*pos), size - (*pos), pos);
        case D1BaseProtocol::Header::TYPE_TEXT_MESSAGE:
            return analyzeProtocolTypeTextMessage(data + (*pos), size - (*pos), pos);
        default:
            B1LOG("Unknown type: size[%d], recvdBuffer_size[%d]", size, _recvdBuffer.size());
            //assert(false);
            return ANALYZE_RESULT_FAIL;
    }
    return ANALYZE_RESULT_SUCCESS;
}

D1BasePacketAnalyzer::ANALYZE_RESULT D1BasePacketAnalyzer::analyzeProtocolTypeNotifyID(uint8* data, size_t size, size_t* pos)
{
    int32 id = -1;
    const size_t idLength = sizeof(id);
    if (size < idLength) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    memcpy(&id, data, idLength);
    id = TO_INT32_FOR_NETWORK(id);
    implOnProtocolTypeNotifyID(id);
    (*pos) += idLength;
    return ANALYZE_RESULT_SUCCESS;
}

D1BasePacketAnalyzer::ANALYZE_RESULT D1BasePacketAnalyzer::analyzeProtocolTypeTextMessage(uint8* data, size_t size, size_t* pos)
{
    D1BaseProtocol::DataTextMessage dataD1Message;
    const size_t lengthSize = sizeof(dataD1Message._length);
    if (size < lengthSize) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    memcpy(&dataD1Message._length, data, lengthSize);
    dataD1Message._length = TO_UINT32_FOR_NETWORK(dataD1Message._length);
    if (size < lengthSize + dataD1Message._length) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    try {
        dataD1Message._message.from((char*)data + lengthSize);
    }
    catch (...) {
        B1LOG("Invalid jize_message string");
        assert(false);
        return ANALYZE_RESULT_FAIL;
    }
    implOnProtocolTypeTextMessage(dataD1Message._message);
    (*pos) += (lengthSize + dataD1Message._length);
    return ANALYZE_RESULT_SUCCESS;
}
