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
#include "D1BaseMessage.h"
#include "D1MsgPerformanceCheckNtf.h"
#include "D1MsgRemoteLogNtf.h"
#include "D1MSMsgKeepAliveRsp.h"

#include <D1Base/D1Consts.h>
#include <D1Base/D1RedisClientInterface.h>

using namespace BnD;

D1MessageSender::D1MessageSender()
{
}

D1MessageSender::~D1MessageSender()
{
}

bool D1MessageSender::rpushMessage(const B1String& key, const D1BaseMessage& message, D1RedisClientInterface* redisClientInterface) const
{
    B1String m;
    message.composeToJson(&m);
    return redisClientInterface->rpush(key, m);
}

bool D1MessageSender::publishMessage(const B1String& channel, const B1String& message, bool essential, D1RedisClientInterface* redisClientInterface) const
{
    return redisClientInterface->publish(channel, message, essential);
}

bool D1MessageSender::publishMessage(const B1String& channel, const D1BaseMessage& message, bool essential, D1RedisClientInterface* redisClientInterface) const
{
    B1String m;
    message.composeToJson(&m);
    return redisClientInterface->publish(channel, m, essential);
}

bool D1MessageSender::publishMessageWithTime(const B1String& channel, D1BaseMessage* message, bool essential, D1RedisClientInterface* redisClientInterface) const
{
    B1String m;
    message->composeToJsonWithBaseTime(&m);
    return redisClientInterface->publish(channel, m, essential);
}

bool D1MessageSender::sendResponseKeepAliveToMS(int32 serviceID, D1RedisClientInterface* redisClientInterface) const
{
    D1MSMsgKeepAliveRsp rsp(serviceID);
    return publishMessage(msSubscribingChannel(), rsp, false, redisClientInterface);
}

bool D1MessageSender::sendLogMessageDebug(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const
{
    D1MsgRemoteLogNtf msg;
    msg.setDebug(serviceID, taskID, zoneID, std::move(comment));
    return publishMessageWithTime(logMessageChannel(), &msg, false, redisClientInterface);
}

bool D1MessageSender::sendLogMessageInfo(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const
{
    D1MsgRemoteLogNtf msg;
    msg.setInfo(serviceID, taskID, zoneID, std::move(comment));
    return publishMessageWithTime(logMessageChannel(), &msg, false, redisClientInterface);
}

bool D1MessageSender::sendLogMessageError(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const
{
    D1MsgRemoteLogNtf msg;
    msg.setError(serviceID, taskID, zoneID, std::move(comment));
    return publishMessageWithTime(logMessageChannel(), &msg, false, redisClientInterface);
}

bool D1MessageSender::sendPerformanceCheckResult(int32 serviceID, uint32 pid,
                                                 int64 memAvailable, int64 memUsage, int64 memCurrentProcessUsage, int64 memTotal,
                                                 int64 vmemUsage, int64 vmemCurrentProcessUsage, int64 vmemTotal,
                                                 float64 cpuUsagePercent, float64 cpuTemperature,
                                                 D1RedisClientInterface* redisClientInterface) const
{
    D1MsgPerformanceCheckNtf msg;
    msg.setServiceID(serviceID);
    msg.setPid(pid);
    msg.setMemAvailable(memAvailable);
    msg.setMemUsage(memUsage);
    msg.setMemCurrentProcessUsage(memCurrentProcessUsage);
    msg.setMemTotal(memTotal);
    msg.setVMemUsage(vmemUsage);
    msg.setVMemCurrentProcessUsage(vmemCurrentProcessUsage);
    msg.setVMemTotal(vmemTotal);
    msg.setCpuUsagePercent(cpuUsagePercent);
    msg.setCpuTemperature(cpuTemperature);
    return publishMessage(logMessageChannel(), msg, false, redisClientInterface);
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
    return B1String::formatAs("PollingList:Controller:%d", dcsID);
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
    const static B1String s_ecsPollingListKey(B1String::formatAs("PollingList:%d", D1Consts::SERVICE_ID_ECS));
    return s_ecsPollingListKey;
}

const B1String& D1MessageSender::ccsPollingListKey()
{
    const static B1String s_ccsPollingListKey(B1String::formatAs("PollingList:%d", D1Consts::SERVICE_ID_CCS));
    return s_ccsPollingListKey;
}

const B1String& D1MessageSender::cusPollingListKey()
{
    const static B1String s_cusPollingListKey(B1String::formatAs("PollingList:%d", D1Consts::SERVICE_ID_CUS));
    return s_cusPollingListKey;
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
