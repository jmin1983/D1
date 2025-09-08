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
    public:
        struct DiskUsage : B1Object {
            DiskUsage() : _path("Path", ""), _capacity("Capacity", 0), _usedPercent("UsedPercent", 0.) {}
            DiskUsage(B1String&& path, int64 capacity, float64 usedPercent)
                : _path("Path", std::move(path)), _capacity("Capacity", capacity), _usedPercent("UsedPercent", usedPercent) {}
            DiskUsage(DiskUsage&& r)
                : _path("Path", std::move(r._path.second)), _capacity("Capacity", r._capacity.second), _usedPercent("UsedPercent", r._usedPercent.second) {}
            DataString _path;
            DataInt64 _capacity;
            DataFloat64 _usedPercent;
            void archiveTo(B1Archive* archive) const final
            {
                writeDataToArchive(_path, archive);
                writeDataToArchive(_capacity, archive);
                writeDataToArchive(_usedPercent, archive);
            }
            void unarchiveFrom(const B1Archive& archive) final
            {
                readDataFromArchive(archive, &_path);
                readDataFromArchive(archive, &_capacity);
                readDataFromArchive(archive, &_usedPercent);
            }
        };
    protected:
        DataInt32 _serviceID;
        DataUint32 _pid;
        DataInt64 _memAvailable;
        DataInt64 _memUsage;
        DataInt64 _memCurrentProcessUsage;
        DataInt64 _memTotal;
        DataInt64 _vmemUsage;
        DataInt64 _vmemCurrentProcessUsage;
        DataInt64 _vmemTotal;
        DataFloat64 _cpuUsagePercent;
        DataFloat64 _cpuTemperature;
        std::pair<const B1String, std::vector<DiskUsage> > _diskUsage;
    protected:
        void archiveMessage(B1Archive* archive) const final;
        void unarchiveMessage(const B1Archive& archive) final;
    public:
        B1String toString() const final;
    public:
        int32 serviceID() const { return _serviceID.second; }
        uint32 pid() const { return _pid.second; }
        int64 memAvailable() const { return _memAvailable.second; }
        int64 memUsage() const { return _memUsage.second; }
        int64 memCurrentProcessUsage() const { return _memCurrentProcessUsage.second; }
        int64 memTotal() const { return _memTotal.second; }
        int64 vmemUsage() const { return _vmemUsage.second; }
        int64 vmemCurrentProcessUsage() const { return _vmemCurrentProcessUsage.second; }
        int64 vmemTotal() const { return _vmemTotal.second; }
        float64 cpuUsagePercent() const { return _cpuUsagePercent.second; }
        float64 cpuTemperature() const { return _cpuTemperature.second; }
        const std::vector<DiskUsage>& diskUsage() const { return _diskUsage.second; }
              std::vector<DiskUsage>& diskUsage()       { return _diskUsage.second; }

        void setServiceID(int32 value) { _serviceID.second = value; }
        void setPid(uint32 value) { _pid.second = value; }
        void setMemAvailable(int64 value) { _memAvailable.second = value; }
        void setMemUsage(int64 value) { _memUsage.second = value; }
        void setMemCurrentProcessUsage(int64 value) { _memCurrentProcessUsage.second = value; }
        void setMemTotal(int64 value) { _memTotal.second = value; }
        void setVMemUsage(int64 value) { _vmemUsage.second = value; }
        void setVMemCurrentProcessUsage(int64 value) { _vmemCurrentProcessUsage.second = value; }
        void setVMemTotal(int64 value) { _vmemTotal.second = value; }
        void setCpuUsagePercent(float64 value) { _cpuUsagePercent.second = value; }
        void setCpuTemperature(float64 value) { _cpuTemperature.second = value; }
    public:
        static const B1String& messageString()
        {
            static B1String s_messageString("D1MsgPerformanceCheckNtf");
            return s_messageString;
        }
    };
}   //  !BnD

#endif  // !_D1MESSAGE_MSG_PERFORMANCE_CHECK_NTF_H
