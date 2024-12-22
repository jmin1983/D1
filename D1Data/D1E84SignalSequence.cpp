//
// D1E84SignalSequence.cpp
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1Data.h"
#include "D1E84SignalSequence.h"

using namespace BnD;

std::vector<uint32> D1E84SignalSequence::_timeouts;

D1E84SignalSequence::D1E84SignalSequence(int32 zoneID)
    : _zoneID(zoneID)
    , _sequence(SEQUENCE_0)
    , _signals(SIGNAL_COUNTS, false)
{
}

bool D1E84SignalSequence::isSignalOn(SIGNAL signal) const
{
    return _signals[signal];
}

bool D1E84SignalSequence::isSignalOff(SIGNAL signal) const
{
    return _signals[signal] != true;
}

bool D1E84SignalSequence::isValidSequenceSignal(SEQUENCE sequence, bool isLoading) const
{
    if (_signals[SIGNAL_HO_AVBL] != true || _signals[SIGNAL_ES] != true) {
        return false;
    }
    switch (sequence) {
        case SEQUENCE_0:
        case SEQUENCE_13:
            return isSignalOff(SIGNAL_VALID) &&
                   isSignalOff(SIGNAL_CS_0) &&
                   isSignalOff(SIGNAL_CS_1) &&
                   isSignalOff(SIGNAL_TR_REQ) &&
                   isSignalOff(SIGNAL_L_REQ) &&
                   isSignalOff(SIGNAL_U_REQ) &&
                   isSignalOff(SIGNAL_READY) &&
                   isSignalOff(SIGNAL_BUSY) &&
                   isSignalOff(SIGNAL_COMPT) &&
                   isSignalOff(SIGNAL_CONT) &&
                   isSignalOn(SIGNAL_HO_AVBL) &&
                   isSignalOn(SIGNAL_ES);
        case SEQUENCE_1:
            return isSignalOn(SIGNAL_CS_0);
        case SEQUENCE_2:
            return isSignalOn(SIGNAL_VALID);
        case SEQUENCE_3:
            return isSignalOn(SIGNAL_VALID) &&
                   (isLoading ? isSignalOn(SIGNAL_L_REQ) : isSignalOn(SIGNAL_U_REQ));
        case SEQUENCE_4:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_TR_REQ);
        case SEQUENCE_5:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   isSignalOn(SIGNAL_TR_REQ);
        case SEQUENCE_6:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   isSignalOn(SIGNAL_TR_REQ) &&
                   isSignalOn(SIGNAL_BUSY);
        case SEQUENCE_7:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   (isLoading ? isSignalOff(SIGNAL_L_REQ) : isSignalOff(SIGNAL_U_REQ));
        case SEQUENCE_8:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   isSignalOff(SIGNAL_BUSY);
        case SEQUENCE_9:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   isSignalOff(SIGNAL_TR_REQ) &&
                   isSignalOff(SIGNAL_BUSY);
        case SEQUENCE_10:
            return isSignalOn(SIGNAL_VALID) &&
                   isSignalOn(SIGNAL_READY) &&
                   isSignalOn(SIGNAL_COMPT);
        case SEQUENCE_11:
            return isSignalOff(SIGNAL_READY);
        case SEQUENCE_12:
            return isSignalOff(SIGNAL_CS_0) &&
                   isSignalOff(SIGNAL_VALID) &&
                   isSignalOff(SIGNAL_COMPT);
        default:
            break;
    }
    return false;
}

uint32 D1E84SignalSequence::timeoutValue(TIMEOUT timeout) const
{
    if (_timeouts.empty()) {    //  call initTimeoutValues().
        assert(false);
        return CONSTS_DEFAULT_TIMEOUT;
    }
    return timeout < TIMEOUT_COUNTS ? _timeouts[timeout] : CONSTS_DEFAULT_TIMEOUT;
}

auto D1E84SignalSequence::sequenceTimeoutType(SEQUENCE sequence) const -> TIMEOUT
{
    switch (sequence) {
        case SEQUENCE_2:
            return TIMEOUT_TA1;
        case SEQUENCE_3:
            return TIMEOUT_TP1;
        //case SEQUENCE_4:
        //    return TIMEOUT_TA2;
        case SEQUENCE_5:
            return TIMEOUT_TP2;
        case SEQUENCE_6:
            return TIMEOUT_TP3;
        case SEQUENCE_7:
            return TIMEOUT_TP4;
        //case SEQUENCE_10:
        //    return TIMEOUT_TA3;
        case SEQUENCE_11:
            return TIMEOUT_TP5;
        default:
            break;
    }
    return TIMEOUT_NA;
}

D1E84SignalSequence& D1E84SignalSequence::operator=(const D1E84SignalSequence& r)
{
    _sequence = r._sequence;
    _signals = r._signals;
    return *this;
}

bool D1E84SignalSequence::operator==(const D1E84SignalSequence& r) const
{
    return _sequence == r._sequence &&
           _signals == r._signals;
}

bool D1E84SignalSequence::isOn(SIGNAL signal) const
{
    return signal < SIGNAL_COUNTS ? _signals[signal] : false;
}

bool D1E84SignalSequence::isOff(SIGNAL signal) const
{
    return signal < SIGNAL_COUNTS ? _signals[signal] != true : true;
}

void D1E84SignalSequence::resetSequence()
{
    _timer.stop();
    _sequence = SEQUENCE_0;
}

bool D1E84SignalSequence::proceedNextSequence(bool isLoadingSequence)
{
    SEQUENCE nextSequence = SEQUENCE_0;
    switch (_sequence) {
        case SEQUENCE_0: nextSequence = SEQUENCE_1; break;
        case SEQUENCE_1: nextSequence = SEQUENCE_2; break;
        case SEQUENCE_2: nextSequence = SEQUENCE_3; break;
        case SEQUENCE_3: nextSequence = SEQUENCE_4; break;
        case SEQUENCE_4: nextSequence = SEQUENCE_5; break;
        case SEQUENCE_5: nextSequence = SEQUENCE_6; break;
        case SEQUENCE_6: nextSequence = SEQUENCE_7; break;
        case SEQUENCE_7: nextSequence = SEQUENCE_8; break;
        case SEQUENCE_8: nextSequence = SEQUENCE_9; break;
        case SEQUENCE_9: nextSequence = SEQUENCE_10; break;
        case SEQUENCE_10: nextSequence = SEQUENCE_11; break;
        case SEQUENCE_11: nextSequence = SEQUENCE_12; break;
        case SEQUENCE_12: nextSequence = SEQUENCE_13; break;
        case SEQUENCE_13: nextSequence = SEQUENCE_0; break;
        default: return false;
    }
    if (isValidSequenceSignal(nextSequence, isLoadingSequence) != true) {
        return false;
    }
    _timer.stop();
    if (SEQUENCE_0 != nextSequence) {
        auto timeoutInterval = timeoutValue(sequenceTimeoutType(nextSequence));
        B1LOG("E84_SEQUENCE proceed to next_sequence: zoneID[%d], sequence[%d], timeoutInterval[%d]", _zoneID, nextSequence, timeoutInterval);
        _timer.start(timeoutInterval);
    }
    _sequence = nextSequence;
    return true;
}

bool D1E84SignalSequence::isSequenceSignalInvalid() const
{
    switch (_sequence) {
        case SEQUENCE_1: {
            if (isSignalOff(SIGNAL_CS_0)) {
                B1LOG("E84_SEQUENCE invalid signal. CS_0 off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            break;
        }
        case SEQUENCE_2:
        case SEQUENCE_3: {
            if (isSignalOff(SIGNAL_CS_0)) {
                B1LOG("E84_SEQUENCE invalid signal. CS_0 off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_VALID)) {
                B1LOG("E84_SEQUENCE invalid signal. VALID off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            break;
        }
        case SEQUENCE_4:
        case SEQUENCE_5: {
            if (isSignalOff(SIGNAL_CS_0)) {
                B1LOG("E84_SEQUENCE invalid signal. CS_0 off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_VALID)) {
                B1LOG("E84_SEQUENCE invalid signal. VALID off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_TR_REQ)) {
                B1LOG("E84_SEQUENCE invalid signal. TR_REQ off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            break;
        }
        case SEQUENCE_6:
        case SEQUENCE_7: {
            if (isSignalOff(SIGNAL_CS_0)) {
                B1LOG("E84_SEQUENCE invalid signal. CS_0 off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_VALID)) {
                B1LOG("E84_SEQUENCE invalid signal. VALID off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_TR_REQ)) {
                B1LOG("E84_SEQUENCE invalid signal. TR_REQ off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            if (isSignalOff(SIGNAL_BUSY)) {
                B1LOG("E84_SEQUENCE invalid signal. BUSY off: zoneID[%d], sequence[%d]", _zoneID, _sequence);
                return true;
            }
            break;
        }
        default:
            break;
    }
    return false;
}

auto D1E84SignalSequence::isSequenceTimedOut() -> TIMEOUT
{
    if (_timer.isTimeover(false)) {
        return sequenceTimeoutType(_sequence);
    }
    return TIMEOUT_NA;
}

B1String D1E84SignalSequence::toString() const
{
    B1String msg(B1String::formatAs("E84Signal: zoneID[%d]", _zoneID));
    for (size_t i = 0; i < _signals.size(); ++i) {
        switch (i) {
            case SIGNAL_VALID:
                msg.append(", VALID");
                break;
            case SIGNAL_CS_0:
                msg.append(", CS_0");
                break;
            case SIGNAL_CS_1:
                msg.append(", CS_1");
                break;
            case SIGNAL_TR_REQ:
                msg.append(", TR_REQ");
                break;
            case SIGNAL_L_REQ:
                msg.append(", L_REQ");
                break;
            case SIGNAL_U_REQ:
                msg.append(", U_REQ");
                break;
            case SIGNAL_READY:
                msg.append(", READY");
                break;
            case SIGNAL_BUSY:
                msg.append(", BUSY");
                break;
            case SIGNAL_COMPT:
                msg.append(", COMPT");
                break;
            case SIGNAL_CONT:
                msg.append(", CONT");
                break;
            case SIGNAL_HO_AVBL:
                msg.append(", HO_AVBL");
                break;
            case SIGNAL_ES:
                msg.append(", ES");
                break;
            default:
                msg.append(", SIGNAL_UNKNOWN_%d", i);
                break;
        }
        msg.appendf("[%d]", _signals[i]);
    }
    for (size_t i = 0; i < _timeouts.size(); ++i) {
        switch (i) {
            case TIMEOUT_TA1:
                msg.append(", TA1");
                break;
            case TIMEOUT_TP1:
                msg.append(", TP1");
                break;
            case TIMEOUT_TP2:
                msg.append(", TP2");
                break;
            case TIMEOUT_TP3:
                msg.append(", TP3");
                break;
            case TIMEOUT_TP4:
                msg.append(", TP4");
                break;
            case TIMEOUT_TP5:
                msg.append(", TP5");
                break;
            default:
                msg.append(", TIMEOUT_UNKNOWN_%d", i);
                break;
        }
        msg.appendf("[%d]", _timeouts[i]);
    }
    return msg;
}

void D1E84SignalSequence::initTimeoutValues(const std::vector<uint32>& timeouts)
{
    _timeouts.resize(std::min<uint32>(TIMEOUT_COUNTS, static_cast<uint32>(timeouts.size())));
    for (size_t i = 0; i < TIMEOUT_COUNTS; ++i) {
        if (i < timeouts.size()) {
            _timeouts[i] = timeouts[i];
        }
        else {
            _timeouts[i] = CONSTS_DEFAULT_TIMEOUT;
        }
    }
}
