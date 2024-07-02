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

bool D1MessageAnalyzer::implInitialize()
{
    if (_messageTable.empty() != true) {
        return false;
    }
#define INSERT_TABLE_VALUE(c) table->insert(std::make_pair(c::messageString().copy(), MAKE_MSG_ENUM(c)));
    auto table = &_messageTable;
    INSERT_TABLE_VALUE(D1MSMsgKeepAliveReq);
    INSERT_TABLE_VALUE(D1MSMsgKeepAliveRsp);

    if (_messageTable.size() != MSG_COUNTS) {
        assert(false);
        return false;
    }
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
        assert(false);
        return MESSAGE_IGNORED;
    }
    return implAnalyzeMessage(temporaryListener, index, indexCount, itr->second, baseMessage, archive, from);
}
