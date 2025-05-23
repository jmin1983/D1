//
// D1MessageSender.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MESSAGE_SENDER_H
#define _D1MESSAGE_MESSAGE_SENDER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif
 
namespace BnD {
    class D1BaseMessage;
    class D1RedisClientInterface;
    class D1MessageSender {
    public:
        D1MessageSender();
        virtual ~D1MessageSender();
    protected:
        bool rpushMessage(const B1String& key, const D1BaseMessage& message, D1RedisClientInterface* redisClientInterface) const;
        bool publishMessage(const B1String& channel, const B1String& message, bool essential, D1RedisClientInterface* redisClientInterface) const;
        bool publishMessage(const B1String& channel, const D1BaseMessage& message, bool essential, D1RedisClientInterface* redisClientInterface) const;
        bool publishMessageWithTime(const B1String& channel, D1BaseMessage* message, bool essential, D1RedisClientInterface* redisClientInterface) const;
    public:
        bool sendResponseKeepAliveToMS(int32 serviceID, D1RedisClientInterface* redisClientInterface) const;
        bool sendLogMessageDebug(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const;
        bool sendLogMessageInfo(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const;
        bool sendLogMessageError(int32 serviceID, int64 taskID, int32 zoneID, B1String&& comment, D1RedisClientInterface* redisClientInterface) const;
        bool sendPerformanceCheckResult(int32 serviceID, uint32 pid,
                                        int64 memAvailable, int64 memUsage, int64 memCurrentProcessUsage, int64 memTotal,
                                        int64 vmemUsage, int64 vmemCurrentProcessUsage, int64 vmemTotal,
                                        float64 cpuUsagePercent, float64 cpuTemperature,
                                        D1RedisClientInterface* redisClientInterface) const;
    public:
        static const B1String& alarmEventChannel();
        static const B1String& systemChannel();
        static const B1String& dcsSubscribingChannel();             //  The channel all DCS are subscribed to.
        static       B1String  dcsSubscribingChannel(int32 dcsID);  //  The channel to which a particular DCS is subscribed.
        static       B1String  dcsPollingListKey(int32 dcsID);
        static       B1String  updateZoneAttributesChannel(int32 ownerID);  //  Channel to publish when zone attributes are being changed. Anyone who interested in the zone attributes must subscribe this channel. MS always subscribes(for redis_writing).
        static const B1String& updateTransferInfoChannel();         //  Channel to publish when TransferInfo changes. Anyone who interested in TransferInfo must subscribe this channel. MS always subscribes(for redis_writing).
        static const B1String& userCommandChannel();                //  Channel to publish when user want to notify something to system. ex) WAS(GUI) -> CUS/DWS/etc...
        static const B1String& userSubscribingChannel();            //  Channel to publish when system want to notify something to user. ex) CUS/DWS/etc... -> WAS(GUI)
        static const B1String& ecsPollingListKey();
        static const B1String& ccsPollingListKey();
        static const B1String& cusPollingListKey();
        static const B1String& msSubscribingChannel();  //  The channel the MS is subscribed to. All programs except MS must send alive_check_rsp through this channel.
        static const B1String& logMessageChannel();
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MESSAGE_SENDER_H
