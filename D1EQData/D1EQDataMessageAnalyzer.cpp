//
// D1EQDataMessageAnalyzer.cpp
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1EQDataMessageAnalyzer.h"
#include "D1EQDataMessageAnalyzerListener.h"

#include "D1TaskLocationInfoMsg.h"
#include "D1ZoneOccupiedAttributesMsg.h"
#include "D1ZoneStateAttributesMsg.h"
 
using namespace BnD;

#undef MAKE_MSG_ENUM

int32 D1EQDataMessageAnalyzer::messageCount() const
{
    return D1MessageAnalyzer::messageCount() + EQ_MSG_COUNTS - EQ_MSG_BEGIN - 1;
}

bool D1EQDataMessageAnalyzer::implInitialize()
{
    if (_listener && dynamic_cast<D1EQDataMessageAnalyzerListener*>(_listener) == NULL) {
        assert(false);
        return false;
    }
    if (D1MessageAnalyzer::implInitialize() != true) {
        return false;
    }
    assert(EQ_MSG_COUNTS < EQ_MSG_MAX);

#define INSERT_TABLE_VALUE(c) table->insert(std::make_pair(c::messageString().copy(), MAKE_EQ_MSG_ENUM(c)));
    auto table = &_messageTable;
    INSERT_TABLE_VALUE(D1TaskLocationInfoMsg);
    INSERT_TABLE_VALUE(D1ZoneOccupiedAttributesMsg);
    INSERT_TABLE_VALUE(D1ZoneStateAttributesMsg);
    return true;
}

auto D1EQDataMessageAnalyzer::implAnalyzeMessage(D1MessageAnalyzerListener* listener, int32 index, int32 indexCount,
                                                 int32 message, const D1BaseMessage& baseMessage, const B1Archive& archive, int32 from) const -> MESSAGE_RESULT
{
    const auto result = D1MessageAnalyzer::implAnalyzeMessage(listener, index, indexCount, message, baseMessage, archive, from);
    if (MESSAGE_IGNORED != result) {
        return result;
    }

    D1EQDataMessageAnalyzerListener* eqdataListener =
#if defined(_DEBUG)
        dynamic_cast<D1EQDataMessageAnalyzerListener*>(listener);
    if (NULL == eqdataListener) {
        assert(false);
        return result;
    }
#else
        static_cast<D1EQDataMessageAnalyzerListener*>(listener);
#endif
#define NOTIFY_LISTENER(c)\
    case MAKE_EQ_MSG_ENUM(c): {\
        c m(std::move(const_cast<D1BaseMessage&>(baseMessage)));\
        archive.toObject(&m);\
        return eqdataListener->onMessage##c(index, indexCount, m, from) ? MESSAGE_COMPLETE : MESSAGE_INCOMPLETE;\
    }

    switch (message) {
        NOTIFY_LISTENER(D1TaskLocationInfoMsg);
        NOTIFY_LISTENER(D1ZoneOccupiedAttributesMsg);
        NOTIFY_LISTENER(D1ZoneStateAttributesMsg);
        default:
            break;
    }
    return MESSAGE_IGNORED;
}
