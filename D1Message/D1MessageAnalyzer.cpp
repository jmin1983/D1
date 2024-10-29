//
// D1MessageAnalyzer.cpp
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Message.h"
#include "D1MessageAnalyzer.h"
#include "D1MessageAnalyzerListener.h"

#include "D1MsgAlarmClearReq.h"
#include "D1MsgAlarmClearRsp.h"
#include "D1MsgAlarmNtf.h"
#include "D1MsgAlarmRemoteNtf.h"
#include "D1MsgEventNtf.h"
#include "D1DCSMsgZoneInfosReq.h"
#include "D1DCSMsgZoneInfosRsp.h"
#include "D1GUIMsgServiceInfosReq.h"
#include "D1GUIMsgZoneInfosReq.h"
#include "D1MsgPerformanceCheckNtf.h"
#include "D1MsgRemoteLogNtf.h"
#include "D1MSMsgKeepAliveReq.h"
#include "D1MSMsgKeepAliveRsp.h"
 
using namespace BnD;

D1MessageAnalyzer::D1MessageAnalyzer()
    : _messageTable()
    , _listener(NULL)
{
}

D1MessageAnalyzer::~D1MessageAnalyzer()
{
}

int32 D1MessageAnalyzer::messageCount() const
{
    return MSG_COUNTS;
}

bool D1MessageAnalyzer::implInitialize()
{
    assert(MSG_COUNTS < MSG_MAX);

    if (_messageTable.empty() != true) {
        return false;
    }
#define INSERT_TABLE_VALUE(c) table->insert(std::make_pair(c::messageString().copy(), MAKE_MSG_ENUM(c)));
    auto table = &_messageTable;
    INSERT_TABLE_VALUE(D1MsgAlarmClearReq);
    INSERT_TABLE_VALUE(D1MsgAlarmClearRsp);
    INSERT_TABLE_VALUE(D1MsgAlarmNtf);
    INSERT_TABLE_VALUE(D1MsgAlarmRemoteNtf);
    INSERT_TABLE_VALUE(D1MsgEventNtf);
    INSERT_TABLE_VALUE(D1DCSMsgZoneInfosReq);
    INSERT_TABLE_VALUE(D1DCSMsgZoneInfosRsp);
    INSERT_TABLE_VALUE(D1GUIMsgServiceInfosReq);
    INSERT_TABLE_VALUE(D1GUIMsgZoneInfosReq);
    INSERT_TABLE_VALUE(D1MsgPerformanceCheckNtf);
    INSERT_TABLE_VALUE(D1MsgRemoteLogNtf);
    INSERT_TABLE_VALUE(D1MSMsgKeepAliveReq);
    INSERT_TABLE_VALUE(D1MSMsgKeepAliveRsp);
    return true;
}

void D1MessageAnalyzer::implFinalize()
{
    _messageTable.clear();
}

auto D1MessageAnalyzer::implAnalyzeMessage(D1MessageAnalyzerListener* listener, int32 index, int32 indexCount,
                                           int32 message, const D1BaseMessage& baseMessage, const B1Archive& archive, int32 from) const -> MESSAGE_RESULT
{
#define NOTIFY_LISTENER(c)\
    case MAKE_MSG_ENUM(c): {\
        c m(std::move(const_cast<D1BaseMessage&>(baseMessage)));\
        archive.toObject(&m);\
        return listener->onMessage##c(index, indexCount, m, from) ? MESSAGE_COMPLETE : MESSAGE_INCOMPLETE;\
    }
    switch (message) {
        NOTIFY_LISTENER(D1MsgAlarmClearReq);
        NOTIFY_LISTENER(D1MsgAlarmClearRsp);
        NOTIFY_LISTENER(D1MsgAlarmNtf);
        NOTIFY_LISTENER(D1MsgAlarmRemoteNtf);
        NOTIFY_LISTENER(D1MsgEventNtf);
        NOTIFY_LISTENER(D1DCSMsgZoneInfosReq);
        NOTIFY_LISTENER(D1DCSMsgZoneInfosRsp);
        NOTIFY_LISTENER(D1GUIMsgServiceInfosReq);
        NOTIFY_LISTENER(D1GUIMsgZoneInfosReq);
        NOTIFY_LISTENER(D1MsgPerformanceCheckNtf);
        NOTIFY_LISTENER(D1MsgRemoteLogNtf);
        NOTIFY_LISTENER(D1MSMsgKeepAliveReq);
        NOTIFY_LISTENER(D1MSMsgKeepAliveRsp);
    default:
        break;
    }
    return MESSAGE_IGNORED;
}

bool D1MessageAnalyzer::initialize(D1MessageAnalyzerListener* listener)
{
    _listener = listener;
    if (implInitialize() != true) {
        _listener = NULL;
        return false;
    }
    if (_messageTable.size() != messageCount()) {
        assert(false);
        return false;
    }
    return true;
}

void D1MessageAnalyzer::finalize()
{
    _listener = NULL;
    implFinalize();
}

auto D1MessageAnalyzer::analyzeMessage(const B1String& message, int32 from) const -> MESSAGE_RESULT
{
    assert(_listener != NULL);
    return analyzeMessage(_listener, 0, 1, message, from);
}

auto D1MessageAnalyzer::analyzeMessage(D1MessageAnalyzerListener* temporaryListener, int32 index, int32 indexCount, const B1String& message, int32 from) const -> MESSAGE_RESULT
{
    B1Archive archive;
    archive.fromString(message);
    D1BaseMessage baseMessage;
    archive.toObject(&baseMessage);
    auto itr = _messageTable.find(baseMessage.messageID());
    if (itr == _messageTable.end()) {
        B1LOG("unknown message received: message[%s]", message.cString());
        //assert(false);
        return MESSAGE_IGNORED;
    }
    return implAnalyzeMessage(temporaryListener, index, indexCount, itr->second, baseMessage, archive, from);
}
