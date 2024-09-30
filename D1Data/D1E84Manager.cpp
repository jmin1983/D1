//
// D1E84Manager.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1E84Manager.h"

using namespace BnD;

D1E84Manager::D1E84Manager()
{
}

D1E84Manager::Data::Data(int32 zoneID)
    : _emergencyStop(false)
    , _resetSequence(false)
    , _halted(false)
    , _sequence(zoneID)
{
}

void D1E84Manager::implProcess()
{
    process(&_loadSequences, true);
    process(&_unloadSequences, false);
}

bool D1E84Manager::updateSignal(int32 zoneID, D1E84SignalSequence* sequence)
{
    std::vector<bool> signals;
    if (implGetSignalFromSensor(zoneID , &signals) != true) {
        return false;
    }
    if (sequence->signals() == signals) {
        return false;
    }
    sequence->signals().swap(signals);
    return true;
}

void D1E84Manager::process(std::map<int32, Data>* data, bool isLoadSequence)
{
    for (auto& dataPair : *data) {
        if (implIsZoneAvailableToE84(dataPair.first) != true) {
            continue;
        }
        if (dataPair.second._emergencyStop) {
            dataPair.second._emergencyStop = false;
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_ES, false);
            implOnEmergencyStopped(dataPair.first);
        }
        else if (dataPair.second._resetSequence) {
            dataPair.second._resetSequence = false;
            dataPair.second._halted = false;
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_HO_AVBL, true);
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_L_REQ, false);
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_U_REQ, false);
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_READY, false);
            implSetSingalToSensor(dataPair.first, D1E84SignalSequence::SIGNAL_ES, true);
            dataPair.second._sequence.resetSequence();
        }
        else {
            if (dataPair.second._halted) {
                continue;
            }
            auto timedOut = dataPair.second._sequence.isSequenceTimedOut();
            if (timedOut != D1E84SignalSequence::TIMEOUT_NA) {
                implOnSequenceTimedOut(dataPair.first, timedOut);
                dataPair.second._halted = true;
            }
            else {
                if (updateSignal(dataPair.first, &dataPair.second._sequence)) {
                    if (isLoadSequence) {
                        processLoadSequence(dataPair.first, &dataPair.second._sequence);
                    }
                    else {
                        processUnloadSequence(dataPair.first, &dataPair.second._sequence);
                    }
                }
            }
        }
    }
}

void D1E84Manager::processLoadSequence(int32 zoneID, D1E84SignalSequence* sequence)
{
    if (sequence->setNextLoadSequence()) {
        if (sequence->needToTurnOnLREQ()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_L_REQ, true);
        }
        else if (sequence->needToTurnOnREADY()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, true);
        }
        else if (sequence->needToTurnOffLREQ()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_L_REQ, false);
        }
        else if (sequence->needToTurnOffREADY()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, false);
        }
    }
}

void D1E84Manager::processUnloadSequence(int32 zoneID, D1E84SignalSequence* sequence)
{
    if (sequence->setNextUnloadSequence()) {
        if (sequence->needToTurnOnUREQ()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_U_REQ, true);
        }
        else if (sequence->needToTurnOnREADY()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, true);
        }
        else if (sequence->needToTurnOffUREQ()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_U_REQ, false);
        }
        else if (sequence->needToTurnOffREADY()) {
            implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, false);
        }
    }
}

bool D1E84Manager::initialize(const std::set<int32>& loadZoneIDs, const std::set<int32>& unloadZoneIDs)
{
    for (int32 zoneID : loadZoneIDs) {
        _loadSequences.insert(std::make_pair(zoneID, zoneID));
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_HO_AVBL, true);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_L_REQ, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_U_REQ, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_ES, true);
    }
    for (int32 zoneID : unloadZoneIDs) {
        _unloadSequences.insert(std::make_pair(zoneID, zoneID));
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_HO_AVBL, true);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_L_REQ, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_U_REQ, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_READY, false);
        implSetSingalToSensor(zoneID, D1E84SignalSequence::SIGNAL_ES, true);
    }
    return implInitialize();
}

void D1E84Manager::finalize()
{
    implFinalize();
    _loadSequences.clear();
    _unloadSequences.clear();
}

void D1E84Manager::process()
{
    implProcess();
}

void D1E84Manager::setEmergencyStop(int32 zoneID)
{
    {
        auto itr = _loadSequences.find(zoneID);
        if (itr != _loadSequences.end()) {
            itr->second._emergencyStop = true;
            return;
        }
    }
    auto itr = _unloadSequences.find(zoneID);
    if (itr != _unloadSequences.end()) {
        itr->second._emergencyStop = true;
    }
}

void D1E84Manager::resetSequence(int32 zoneID)
{
    {
        auto itr = _loadSequences.find(zoneID);
        if (itr != _loadSequences.end()) {
            itr->second._resetSequence = true;
            return;
        }
    }
    auto itr = _unloadSequences.find(zoneID);
    if (itr != _unloadSequences.end()) {
        itr->second._resetSequence = true;
    }
}
