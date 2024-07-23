//
// D1MSMsgKeepAliveRsp.cpp
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MSMsgKeepAliveRsp.h"

#include <D1Base/D1Consts.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace BnD;

D1MSMsgKeepAliveRsp::D1MSMsgKeepAliveRsp(int32 serviceID)
    : D1BaseMessage()
    , _serviceID("ServiceID", serviceID)
{
    _messageID.second = messageString().copy();
}

D1MSMsgKeepAliveRsp::D1MSMsgKeepAliveRsp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _serviceID("ServiceID", D1Consts::SERVICE_ID_INVALID)
{
}

D1MSMsgKeepAliveRsp::~D1MSMsgKeepAliveRsp()
{
}

void D1MSMsgKeepAliveRsp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive(_serviceID, archive);
}

void D1MSMsgKeepAliveRsp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive(archive, &_serviceID);
}
