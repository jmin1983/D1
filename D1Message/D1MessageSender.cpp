//
// D1MessageSender.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MessageSender.h"

using namespace BnD;

D1MessageSender::D1MessageSender()
{
}

D1MessageSender::~D1MessageSender()
{
}

const B1String& D1MessageSender::alarmEventChannel()
{
    const static B1String s_alarmEventChannel("AlarmEventChannel");
    return s_alarmEventChannel;
}

const B1String& D1MessageSender::systemChannel()
{
    const static B1String s_systemChannel("SystemChannel");
    return s_systemChannel;
}

const B1String& D1MessageSender::dcsSubscribingChannel()
{
    const static B1String s_dcsListeningChannel("DCSListeningChannel");
    return s_dcsListeningChannel;
}

B1String D1MessageSender::dcsSubscribingChannel(int32 dcsID)
{
    return B1String::formatAs("DCSListeningChannel:%d", dcsID);
}

B1String D1MessageSender::dcsPollingListKey(int32 dcsID)
{
    return B1String::formatAs("DCSPollingListKey:%d", dcsID);
}

B1String D1MessageSender::updateZoneAttributesChannel(int32 ownerID)
{
    return B1String::formatAs("UpdateZoneAttributesChannel:%d", ownerID);
}

const B1String& D1MessageSender::updateTransferInfoChannel()
{
    const static B1String s_updateTransferInfoChannel("UpdateTransferInfoChannel");
    return s_updateTransferInfoChannel;
}

const B1String& D1MessageSender::userCommandChannel()
{
    const static B1String s_userCommandChannel("UserCommandChannel");
    return s_userCommandChannel;
}

const B1String& D1MessageSender::userSubscribingChannel()
{
    const static B1String s_userSubscribingChannel("UserSubscribingChannel");
    return s_userSubscribingChannel;
}

const B1String& D1MessageSender::ecsPollingListKey()
{
    const static B1String s_ecsPollingListKey("ECSPollingListKey");
    return s_ecsPollingListKey;
}

const B1String& D1MessageSender::ccsPollingListKey()
{
    const static B1String s_ccsPollingListKey("CCSPollingListKey");
    return s_ccsPollingListKey;
}

const B1String& D1MessageSender::msSubscribingChannel()
{
    const static B1String s_msSubscribingChannel("MSSubscribingChannel");
    return s_msSubscribingChannel;
}

const B1String& D1MessageSender::logMessageChannel() {

    const static B1String s_logMessageChannel("LogMessageChannel");
    return s_logMessageChannel;
}

const B1String& D1MessageSender::selfTestChannel() {

    const static B1String s_selfTestChannel("SelfTestChannel");
    return s_selfTestChannel;
}
