//
// D1MessageAnalyzer.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MESSAGE_ANALYZER_H
#define _D1MESSAGE_MESSAGE_ANALYZER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(_USE_MESSAGE_ANALYZER_STD_MAP)
#include <map>
#else
#include <unordered_map>
#endif

namespace BnD {
    class D1BaseMessage;
    class D1MessageAnalyzerListener;
    class B1Archive;
    class D1MessageAnalyzer {
    public:
        D1MessageAnalyzer();
        virtual ~D1MessageAnalyzer();
    protected:
        //  When adding a new message, need to work on D1MessageAnalyzerListener::new_function(), enum MSG, initializeTable(), implAnalyzeMessage(). (any better method?)
#define MAKE_MSG_ENUM(c) MSG_##c
        enum MSG {
            MSG_UNKNOWN = -1,

            MAKE_MSG_ENUM(D1MSMsgKeepAliveReq),
            MAKE_MSG_ENUM(D1MSMsgKeepAliveRsp),

            MSG_COUNTS,

            MSG_MAX = 1000,

            //  When adding a new message, check the comment at the top of enum MSG.
        };
    public:
        enum MESSAGE_RESULT {
            MESSAGE_COMPLETE = 0,   //  message process completed.
            MESSAGE_INCOMPLETE,     //  message can not be processed for this time.
            MESSAGE_IGNORED,        //  message can not be handled in this analyzer.
        };
        enum MESSAGE_FROM {
            MESSAGE_FROM_CHECK_RESULT = 0,
            MESSAGE_FROM_IGNORE_RESULT,
        };
    protected:
#if defined(_USE_MESSAGE_ANALYZER_STD_MAP)
        std::map<B1String, int32> _messageTable;
#else
        std::unordered_map<B1String, int32> _messageTable;
#endif
        D1MessageAnalyzerListener* _listener;
    protected:
        virtual int32 messageCount() const;
        virtual bool implInitialize();
        virtual void implFinalize();
        virtual MESSAGE_RESULT implAnalyzeMessage(D1MessageAnalyzerListener* listener, int32 index, int32 indexCount,
                                                  int32 message, const D1BaseMessage& baseMessage, const B1Archive& archive, int32 from) const;
    public:
        bool initialize(D1MessageAnalyzerListener* listener);
        void finalize();
        MESSAGE_RESULT analyzeMessage(const B1String& message, int32 from) const;
        MESSAGE_RESULT analyzeMessage(D1MessageAnalyzerListener* temporaryListener, int32 index, int32 indexCount, const B1String& message, int32 from = 1) const;
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MESSAGE_ANALYZER_H
