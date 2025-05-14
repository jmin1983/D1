//
// D1MsgPerformanceCheckNtf.h
//
// Library: D1Message
// Package: D1Message
// Module:  D1Message
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1MESSAGE_MSG_PERFORMANCE_CHECK_NTF_H
#define _D1MESSAGE_MSG_PERFORMANCE_CHECK_NTF_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1Message/D1BaseMessage.h>

namespace BnD {
    class D1MsgPerformanceCheckNtf : public D1BaseMessage {
    public:
        D1MsgPerformanceCheckNtf();
        D1MsgPerformanceCheckNtf(D1BaseMessage&& baseMessage);
        virtual ~D1MsgPerformanceCheckNtf();
    protected:
        DataInt32 _serviceID;
        DataUint32 _pid;
        DataInt64 _memUsage;
        DataInt64 _memCurrentProcessUsage;
        DataInt64 _memTotal;
        DataInt64 _vmemUsage;
        DataInt64 _vmemCurrentProcessUsage;
        DataInt64 _vmemTotal;
        DataFloat64 _cpuUsagePercent;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 serviceID() const { return _serviceID.second; }
        uint32 pid() const { return _pid.second; }
        int64 memUsage() const { return _memUsage.second; }
        int64 memCurrentProcessUsage() const { return _memCurrentProcessUsage.second; }
        int64 memTotal() const { return _memTotal.second; }
        int64 vmemUsage() const { return _vmemUsage.second; }
        int64 vmemCurrentProcessUsage() const { return _vmemCurrentProcessUsage.second; }
        int64 vmemTotal() const { return _vmemTotal.second; }
        float64 cpuUsagePercent() const { return _cpuUsagePercent.second; }

        void setServiceID(int32 value) { _serviceID.second = value; }
        void setPid(uint32 value) { _pid.second = value; }
        void setMemUsage(int64 value) { _memUsage.second = value; }
        void setMemCurrentProcessUsage(int64 value) { _memCurrentProcessUsage.second = value; }
        void setMemTotal(int64 value) { _memTotal.second = value; }
        void setVMemUsage(int64 value) { _vmemUsage.second = value; }
        void setVMemCurrentProcessUsage(int64 value) { _vmemCurrentProcessUsage.second = value; }
        void setVMemTotal(int64 value) { _vmemTotal.second = value; }
        void setCpuUsagePercent(float64 value) { _cpuUsagePercent.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgPerformanceCheckNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_PERFORMANCE_CHECK_NTF_H
