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

D1BasePacketAnalyzer::D1BasePacketAnalyzer(size_t defaultBufferSize)
    : B1BasePacketAnalyzer(defaultBufferSize)
{
}

auto D1BasePacketAnalyzer::implAnalyzeData(const D1BaseProtocol::Header& header, uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    switch (header._type) {
        case D1BaseProtocol::Header::TYPE_ALIVE_CHECK:
            implOnProtocolTypeAliveCheck();
            break;
        case D1BaseProtocol::Header::TYPE_NOTIFY_ID:
            return analyzeProtocolTypeNotifyID(data, size, pos);
        case D1BaseProtocol::Header::TYPE_TEXT_MESSAGE:
            return analyzeProtocolTypeTextMessage(data, size, pos);
        case D1BaseProtocol::Header::TYPE_TEXT_MESSAGE_BUNCH:
            return analyzeProtocolTypeTextMessageBunch(data, size, pos);
        case D1BaseProtocol::Header::TYPE_BINARY:
            return analyzeProtocolTypeBinary(data, size, pos);
        default:
            B1LOG("Unknown type: size[%d], recvdBuffer_size[%d]", size, _recvdBuffer.size());
            //assert(false);
            return ANALYZE_RESULT_FAIL;
    }
    return ANALYZE_RESULT_SUCCESS;
}

auto D1BasePacketAnalyzer::implAnalyzeData(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    D1BaseProtocol::Header header;
    {
        const size_t headerSize = sizeof(header);
        if (size < headerSize) {
            return ANALYZE_RESULT_NOT_ENOUTH_DATA;
        }
        memcpy(&header, data, headerSize);
        (*pos) += headerSize;
    }
    return implAnalyzeData(header, data + (*pos), size - (*pos), pos);
}

auto D1BasePacketAnalyzer::analyzeProtocolTypeNotifyID(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
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

auto D1BasePacketAnalyzer::analyzeProtocolTypeTextMessage(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    D1BaseProtocol::DataTextMessage dataTextMessage;
    const size_t lengthSize = sizeof(dataTextMessage._length);
    if (size < lengthSize) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    memcpy(&dataTextMessage._length, data, lengthSize);
    dataTextMessage._length = TO_UINT32_FOR_NETWORK(dataTextMessage._length);
    if (size < lengthSize + dataTextMessage._length) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    try {
        dataTextMessage._message.from((char*)data + lengthSize);
    }
    catch (...) {
        B1LOG("Invalid data_text_message string");
        assert(false);
        return ANALYZE_RESULT_FAIL;
    }
    implOnProtocolTypeTextMessage(std::move(dataTextMessage._message));
    (*pos) += (lengthSize + dataTextMessage._length);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1BasePacketAnalyzer::analyzeProtocolTypeTextMessageBunch(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    int32 index = -1;
    int32 indexCount = 0;
    D1BaseProtocol::DataTextMessage dataTextMessage;

    const size_t indexSize = sizeof(index);
    const size_t indexCountSize = sizeof(indexCount);
    const size_t dataTextLengthSize = sizeof(dataTextMessage._length);
    if (size < indexSize + indexCountSize + dataTextLengthSize) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }

    memcpy(&dataTextMessage._length, data + indexSize + indexCountSize, dataTextLengthSize);
    dataTextMessage._length = TO_UINT32_FOR_NETWORK(dataTextMessage._length);
    if (size < indexSize + indexCountSize + dataTextLengthSize + dataTextMessage._length) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    memcpy(&index, data, indexSize);
    memcpy(&indexCount, data + indexSize, indexCountSize);
    index = TO_INT32_FOR_NETWORK(index);
    indexCount = TO_INT32_FOR_NETWORK(indexCount);
    
    try {
        dataTextMessage._message.from((char*)data + indexSize + indexCountSize + dataTextLengthSize);
    }
    catch (...) {
        B1LOG("Invalid data_text_message string");
        assert(false);
        return ANALYZE_RESULT_FAIL;
    }
    implOnProtocolTypeTextMessageBunch(index, indexCount, std::move(dataTextMessage._message));
    (*pos) += (indexSize + indexCountSize + dataTextLengthSize + dataTextMessage._length);
    return ANALYZE_RESULT_SUCCESS;
}

auto D1BasePacketAnalyzer::analyzeProtocolTypeBinary(uint8* data, size_t size, size_t* pos) -> ANALYZE_RESULT
{
    int32 index = -1;
    int32 indexCount = 0;
    uint32 dataLength = 0;

    const size_t indexSize = sizeof(index);
    const size_t indexCountSize = sizeof(indexCount);
    const size_t dataLengthSize = sizeof(dataLength);
    if (size < indexSize + indexCountSize + dataLengthSize) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }

    memcpy(&dataLength, data + indexSize + indexCountSize, dataLengthSize);
    dataLength = TO_UINT32_FOR_NETWORK(dataLength);
    if (size < indexSize + indexCountSize + dataLengthSize + dataLength) {
        return ANALYZE_RESULT_NOT_ENOUTH_DATA;
    }
    memcpy(&index, data, indexSize);
    memcpy(&indexCount, data + indexSize, indexCountSize);
    index = TO_INT32_FOR_NETWORK(index);
    indexCount = TO_INT32_FOR_NETWORK(indexCount);

    implOnProtocolTypeBinary(index, indexCount, std::vector<uint8>(data + indexSize + indexCountSize + dataLengthSize, data + indexSize + indexCountSize + dataLengthSize + dataLength));
    (*pos) += (indexSize + indexCountSize + dataLengthSize + dataLength);
    return ANALYZE_RESULT_SUCCESS;
}
