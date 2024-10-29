//
// D1GUIMsgServiceInfosRsp.cpp
//
// Library: D1Message
// Package: GUI
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1GUIMsgServiceInfosRsp.h"

#include <B1Base/B1Archive.hpp>

#include <D1Base/D1Consts.h>

using namespace BnD;

D1GUIMsgServiceInfosRsp::D1GUIMsgServiceInfosRsp()
    : D1BaseMessage()
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _serviceInfos("ServiceInfos", std::vector<D1ServiceInfo>())
{
    _messageID.second = messageString().copy();
}

D1GUIMsgServiceInfosRsp::D1GUIMsgServiceInfosRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _index("Index", 0)
    , _indexCount("IndexCount", 0)
    , _serviceInfos("ServiceInfos", std::vector<D1ServiceInfo>())
{
}

D1GUIMsgServiceInfosRsp::~D1GUIMsgServiceInfosRsp()
{
}

void D1GUIMsgServiceInfosRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_index, archive);
    writeDataToArchive(_indexCount, archive);
    writeObjectArrayToArchive(_serviceInfos, archive);
}

void D1GUIMsgServiceInfosRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_index);
    readDataFromArchive(archive, &_indexCount);
    readObjectArrayFromArchive(archive, &_serviceInfos);
}

B1String D1GUIMsgServiceInfosRsp::toString() const
{
    B1String str = D1BaseMessage::toString();
    str.appendf(", index[%d]", index());
    str.appendf(", indexCount[%d]", indexCount());
    str.append(", serviceInfos:");
    if (serviceInfos().empty()) {
        str.append("[empty]");
    }
    else {
        for (const auto& serviceInfo : _serviceInfos.second) {
            str.appendf("[%s]", serviceInfo.toString().cString());
        }
    }
    return str;
}
