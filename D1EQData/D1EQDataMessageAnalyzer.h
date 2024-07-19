//
// D1EQDataMessageAnalyzer.h
//
// Library: D1EQData
// Package: D1EQData
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_EQ_DATA_MESSAGE_ANALYZER_H
#define _D1EQDATA_EQ_DATA_MESSAGE_ANALYZER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1MessageAnalyzer.h>

namespace BnD {
    class D1EQDataMessageAnalyzer : public D1MessageAnalyzer {
    protected:
        //  When adding a new message, need to work on D1EQDataMessageAnalyzerListener::new_function(), enum MSG, initializeTable(), implAnalyzeMessage(). (any better method?)
#define MAKE_EQ_MSG_ENUM(c) EQ_MSG_##c
        enum EQ_MSG {
            EQ_MSG_BEGIN = MSG_MAX,

            MAKE_EQ_MSG_ENUM(D1TaskLocationInfoMsg),
            MAKE_EQ_MSG_ENUM(D1ZoneOccupiedAttributesMsg),
            MAKE_EQ_MSG_ENUM(D1ZoneStateAttributesMsg),

            EQ_MSG_COUNTS,

            EQ_MSG_MAX = EQ_MSG_BEGIN + 1000,

            //  When adding a new message, check the comment at the top of enum MSG.
        };
    protected:  //  D1MessageAnalyzer
        virtual int32 messageCount() const override;
        virtual bool implInitialize() override;
        virtual MESSAGE_RESULT implAnalyzeMessage(D1MessageAnalyzerListener* listener, int32 index, int32 indexCount,
                                                  int32 message, const D1BaseMessage& baseMessage, const B1Archive& archive, int32 from) const override;
    };
}   //  !BnD

#endif  // !_D1EQDATA_EQ_DATA_MESSAGE_ANALYZER_H
