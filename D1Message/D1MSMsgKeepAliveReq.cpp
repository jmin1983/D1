//
// D1MSMsgKeepAliveReq.cpp
//
// Library: D1Message
// Package: MS
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MSMsgKeepAliveReq.h"

using namespace BnD;

D1MSMsgKeepAliveReq::D1MSMsgKeepAliveReq()
    : D1BaseMessage()
{
    _messageID.second = messageString().copy();
}

D1MSMsgKeepAliveReq::D1MSMsgKeepAliveReq(D1BaseMessage&& baseMessage)
    : D1BaseMessage(std::move(baseMessage))
{
}

D1MSMsgKeepAliveReq::~D1MSMsgKeepAliveReq()
{
}
