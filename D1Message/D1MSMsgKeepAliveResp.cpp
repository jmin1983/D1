//
// D1MSMsgKeepAliveResp.cpp
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MSMsgKeepAliveResp.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace BnD;

D1MSMsgKeepAliveResp::D1MSMsgKeepAliveResp()
    : D1BaseMessage()
    , _respMessage()
{
    _messageID.second = messageString().copy();
}

D1MSMsgKeepAliveResp::D1MSMsgKeepAliveResp(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
    , _respMessage()
{
}

D1MSMsgKeepAliveResp::~D1MSMsgKeepAliveResp()
{
}

void D1MSMsgKeepAliveResp::archiveMessage(B1Archive* archive) const
{
    writeDataToArchive("RespMessage", _respMessage, archive);
}

void D1MSMsgKeepAliveResp::unarchiveMessage(const B1Archive& archive)
{
    readDataFromArchive("RespMessage", archive, &_respMessage);
}
