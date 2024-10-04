//
// D1E84Manager.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_E84_MANAGER_H
#define _D1DATA_E84_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <map>
#include <set>

#include <D1Data/D1E84SignalSequence.h>

namespace BnD {
    class D1E84Manager {
    public:
        D1E84Manager();
        virtual ~D1E84Manager() {}
    protected:
        struct Data {
            Data(int32 zoneID);
            bool _emergencyStop;
            bool _resetSequence;
            bool _halted;
            D1E84SignalSequence _sequence;
        };
    protected:
        std::map<int32, Data> _loadSequences;   //  map<zone_id, data>
        std::map<int32, Data> _unloadSequences; //  map<zone_id, data>
    protected:
        virtual bool implInitialize() { return true; }
        virtual void implFinalize() {}
        virtual void implProcess();
        virtual bool implGetSignalFromSensor(int32 zoneID, std::vector<bool>* signals) = 0;   //  vector<D1E84SignalSequence::SIGNAL>. return false if get signal from E84 sensor failed.
        virtual bool implSetSingalToSensor(int32 zoneID, D1E84SignalSequence::SIGNAL signal, bool value) = 0;
        virtual bool implIsZoneAvailableToE84(int32 zoneID) { return true; }
        virtual void implOnSequenceFinished(int32 zoneID) = 0;
        virtual void implOnSequenceTimedOut(int32 zoneID, D1E84SignalSequence::TIMEOUT type) = 0;
        virtual void implOnEmergencyStopped(int32 zoneID) = 0;
    protected:
        bool updateSignal(int32 zoneID, D1E84SignalSequence* sequence); //  return true if signal updated.
        void process(std::map<int32, Data>* data, bool isLoadSequence);
        void processLoadSequence(int32 zoneID, D1E84SignalSequence* sequence);
        void processUnloadSequence(int32 zoneID, D1E84SignalSequence* sequence);
    public:
        bool initialize(const std::set<int32>& loadZoneIDs, const std::set<int32>& unloadZoneIDs);
        void finalize();
        void process();
        void setEmergencyStop(int32 zoneID);
        void resetSequence(int32 zoneID);
    };
}   //  !BnD

#endif  // !_D1DATA_E84_MANAGER_H
