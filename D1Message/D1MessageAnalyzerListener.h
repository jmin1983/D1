//
// D1MessageAnalyzerListener.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MESSAGE_ANALYZER_LISTENER_H
#define _D1MESSAGE_MESSAGE_ANALYZER_LISTENER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

namespace BnD {
    class D1MessageAnalyzerListener {
    public:
        //  return true if message processing is complete.
        //  If message processing has not been completed(processed in another worker thread, etc.), return false and then process task completion according to @from.
        //  (ex: In case of polling, @from is set to 0, so if @from is 0, pop() is called from poller after the task is completed).
#define DEFINE_MESSAGE_LISTENER_FUNC(c) virtual bool onMessage##c(const class c& data, int32 from)  //  from: MESSAGE_FROM
#define DEFINE_MESSAGE_ANALYZER_LISTENER_FUNC(post_fix) \
    DEFINE_MESSAGE_LISTENER_FUNC(D1MSMsgKeepAliveReq) post_fix\
    DEFINE_MESSAGE_LISTENER_FUNC(D1MSMsgKeepAliveRsp) post_fix\

    DEFINE_MESSAGE_ANALYZER_LISTENER_FUNC({ return true; });
#undef DEFINE_MESSAGE_ANALYZER_LISTENER_FUNC
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MESSAGE_ANALYZER_LISTENER_H
