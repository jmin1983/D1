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
    : B1Object()
    , _zoneID(zoneID)
    , _sequence(SEQUENCE_0)
    , _signals(SIGNAL_COUNTS, false)
{
}

bool D1E84SignalSequence::signalOn(SIGNAL signal) const
{
    return _signals[signal];
}

bool D1E84SignalSequence::signalOff(SIGNAL signal) const
{
    return _signals[signal] != true;
}

void D1E84SignalSequence::archiveTo(B1Archive* archive) const
{
    writeDataToArchive(toRedisFieldFromSequence(), _sequence, archive);
#define WRITE_SIGNAL(s) writeDataToArchive(toRedisField(s), _signals[s], archive);
    WRITE_SIGNAL(SIGNAL_VALID);
    WRITE_SIGNAL(SIGNAL_CS_0);
    WRITE_SIGNAL(SIGNAL_CS_1);
    WRITE_SIGNAL(SIGNAL_TR_REQ);
    WRITE_SIGNAL(SIGNAL_L_REQ);
    WRITE_SIGNAL(SIGNAL_U_REQ);
    WRITE_SIGNAL(SIGNAL_READY);
    WRITE_SIGNAL(SIGNAL_BUSY);
    WRITE_SIGNAL(SIGNAL_COMPT);
    WRITE_SIGNAL(SIGNAL_CONT);
    WRITE_SIGNAL(SIGNAL_HO_AVBL);
    WRITE_SIGNAL(SIGNAL_ES);
}

void D1E84SignalSequence::unarchiveFrom(const B1Archive& archive)
{
    readDataFromArchiveCastInt32<SEQUENCE>(toRedisFieldFromSequence(), archive, &_sequence);
#define READ_SIGNAL(s) { bool temp = false; readDataFromArchive(toRedisField(s), archive, &temp); _signals[s] = temp; }
    READ_SIGNAL(SIGNAL_VALID);
    READ_SIGNAL(SIGNAL_CS_0);
    READ_SIGNAL(SIGNAL_CS_1);
    READ_SIGNAL(SIGNAL_TR_REQ);
    READ_SIGNAL(SIGNAL_L_REQ);
    READ_SIGNAL(SIGNAL_U_REQ);
    READ_SIGNAL(SIGNAL_READY);
    READ_SIGNAL(SIGNAL_BUSY);
    READ_SIGNAL(SIGNAL_COMPT);
    READ_SIGNAL(SIGNAL_CONT);
    READ_SIGNAL(SIGNAL_HO_AVBL);
    READ_SIGNAL(SIGNAL_ES);
}

B1String D1E84SignalSequence::toString() const
{
    B1String tmp;
    tmp.format("E84_SEQUENCE[%d]", _sequence);
#define APPEND_SIGNAL_STRING(s) tmp.appendf(", %s:[%d]", toRedisField(s).cString(), signalOn(s) ? 1 : 0);
    APPEND_SIGNAL_STRING(SIGNAL_VALID);
    APPEND_SIGNAL_STRING(SIGNAL_CS_0);
    APPEND_SIGNAL_STRING(SIGNAL_CS_1);
    APPEND_SIGNAL_STRING(SIGNAL_TR_REQ);
    APPEND_SIGNAL_STRING(SIGNAL_L_REQ);
    APPEND_SIGNAL_STRING(SIGNAL_U_REQ);
    APPEND_SIGNAL_STRING(SIGNAL_READY);
    APPEND_SIGNAL_STRING(SIGNAL_BUSY);
    APPEND_SIGNAL_STRING(SIGNAL_COMPT);
    APPEND_SIGNAL_STRING(SIGNAL_CONT);
    APPEND_SIGNAL_STRING(SIGNAL_HO_AVBL);
    APPEND_SIGNAL_STRING(SIGNAL_ES);
    return tmp;
}

bool D1E84SignalSequence::setNextSequence(bool isLoading)
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
    if (isValidSequenceSignal(nextSequence, isLoading) != true) {
        return false;
    }
    _timer.stop();
    if (SEQUENCE_0 != nextSequence) {
        _timer.start(timeoutValue(sequenceTimeoutType(nextSequence)));
    }
    B1LOG("set E84 next_sequence: zoneID[%d], sequence[%d]", _zoneID, nextSequence);
    _sequence = nextSequence;
    return true;
}

bool D1E84SignalSequence::isValidSequenceSignal(SEQUENCE sequence, bool isLoading) const
{
    if (_signals[SIGNAL_HO_AVBL] != true || _signals[SIGNAL_ES] != true) {
        return false;
    }
    switch (sequence) {
        case SEQUENCE_0:
        case SEQUENCE_13:
            return signalOff(SIGNAL_VALID) &&
                   signalOff(SIGNAL_CS_0) &&
                   signalOff(SIGNAL_CS_1) &&
                   signalOff(SIGNAL_TR_REQ) &&
                   signalOff(SIGNAL_L_REQ) &&
                   signalOff(SIGNAL_U_REQ) &&
                   signalOff(SIGNAL_READY) &&
                   signalOff(SIGNAL_BUSY) &&
                   signalOff(SIGNAL_COMPT) &&
                   signalOff(SIGNAL_CONT) &&
                   signalOn(SIGNAL_HO_AVBL) &&
                   signalOn(SIGNAL_ES);
        case SEQUENCE_1:
            return signalOn(SIGNAL_CS_0);
        case SEQUENCE_2:
            return signalOn(SIGNAL_VALID);
        case SEQUENCE_3:
            return signalOn(SIGNAL_VALID) &&
                   (isLoading ? signalOn(SIGNAL_L_REQ) : signalOn(SIGNAL_U_REQ));
        case SEQUENCE_4:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_TR_REQ);
        case SEQUENCE_5:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   signalOn(SIGNAL_TR_REQ);
        case SEQUENCE_6:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   signalOn(SIGNAL_TR_REQ) &&
                   signalOn(SIGNAL_BUSY);
        case SEQUENCE_7:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   (isLoading ? signalOff(SIGNAL_L_REQ) : signalOff(SIGNAL_U_REQ));
        case SEQUENCE_8:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   signalOff(SIGNAL_BUSY);
        case SEQUENCE_9:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   signalOff(SIGNAL_TR_REQ) &&
                   signalOff(SIGNAL_BUSY);
        case SEQUENCE_10:
            return signalOn(SIGNAL_VALID) &&
                   signalOn(SIGNAL_READY) &&
                   signalOn(SIGNAL_COMPT);
        case SEQUENCE_11:
            return signalOff(SIGNAL_READY);
        case SEQUENCE_12:
            return signalOff(SIGNAL_CS_0) &&
                   signalOff(SIGNAL_VALID) &&
                   signalOff(SIGNAL_COMPT);
        default:
            break;
    }
    return false;
}

uint32 D1E84SignalSequence::timeoutValue(TIMEOUT timeout) const
{
    return timeout < TIMEOUT_COUNTS ? _timeouts[timeout] : CONSTS_DEFAULT_TIMEOUT;
}

D1E84SignalSequence::TIMEOUT D1E84SignalSequence::sequenceTimeoutType(SEQUENCE sequence) const
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

B1String D1E84SignalSequence::toRedisFieldFromSequence() const
{
    return "E84_SEQUENCE";
}

B1String D1E84SignalSequence::toRedisField(SIGNAL signal) const
{
    switch (signal) {
        case SIGNAL_VALID: return "E84_VALID";
        case SIGNAL_CS_0: return "E84_CS_0";
        case SIGNAL_CS_1: return "E84_CS_1";
        case SIGNAL_TR_REQ: return "E84_TR_REQ";
        case SIGNAL_L_REQ: return "E84_L_REQ";
        case SIGNAL_U_REQ: return "E84_U_REQ";
        case SIGNAL_READY: return "E84_READY";
        case SIGNAL_BUSY: return "E84_BUSY";
        case SIGNAL_COMPT: return "E84_COMPT";
        case SIGNAL_CONT: return "E84_CONT";
        case SIGNAL_HO_AVBL: return "E84_HO_AVBL";
        case SIGNAL_ES: return "E84_ES";
        default:
            break;
    }
    return "E84_UNKNOWN";
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

void D1E84SignalSequence::makeRedisStringArgs(std::vector<B1String>* args) const
{
    args->push_back(toRedisFieldFromSequence());
    args->push_back(B1String::formatAs("%d", _sequence));

#define PUSH_BACK_SIGNAL(s) args->push_back(toRedisField(s)); args->push_back(B1String::formatAs("%d", signalOn(s) ? 1 : 0));
    PUSH_BACK_SIGNAL(SIGNAL_VALID);
    PUSH_BACK_SIGNAL(SIGNAL_CS_0);
    PUSH_BACK_SIGNAL(SIGNAL_CS_1);
    PUSH_BACK_SIGNAL(SIGNAL_TR_REQ);
    PUSH_BACK_SIGNAL(SIGNAL_L_REQ);
    PUSH_BACK_SIGNAL(SIGNAL_U_REQ);
    PUSH_BACK_SIGNAL(SIGNAL_READY);
    PUSH_BACK_SIGNAL(SIGNAL_BUSY);
    PUSH_BACK_SIGNAL(SIGNAL_COMPT);
    PUSH_BACK_SIGNAL(SIGNAL_CONT);
    PUSH_BACK_SIGNAL(SIGNAL_HO_AVBL);
    PUSH_BACK_SIGNAL(SIGNAL_ES);
}

bool D1E84SignalSequence::readRedisMap(const std::map<B1String, B1String>& map)
{
    auto itr = map.find(toRedisFieldFromSequence());
    if (itr != map.end() && itr->second.isEmpty() != true) {
        try { _sequence = static_cast<SEQUENCE>(itr->second.toInt32()); } catch (...) {}
    }

#define FIND_SIGNAL_DATA_AND_SET(s)\
    itr = map.find(toRedisField(s));\
    if (itr != map.end() && itr->second.isEmpty() != true) { try { _signals[s] = itr->second.toInt32() == 1 ? true : false; } catch (...) {} }
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_VALID);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_CS_0);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_CS_1);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_TR_REQ);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_L_REQ);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_U_REQ);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_READY);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_BUSY);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_COMPT);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_CONT);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_HO_AVBL);
    FIND_SIGNAL_DATA_AND_SET(SIGNAL_ES);
    return true;
}

bool D1E84SignalSequence::isOn(SIGNAL signal) const
{
    return signal < SIGNAL_COUNTS ? _signals[signal] : false;
}

bool D1E84SignalSequence::isOff(SIGNAL signal) const
{
    return signal < SIGNAL_COUNTS ? _signals[signal] != true : true;
}

void D1E84SignalSequence::setSignal(SIGNAL signal, bool value)
{
    if (signal < SIGNAL_COUNTS) {
        B1LOG("set E84 signal: zoneID[%d], signal:[%s], value[%d]", _zoneID, toRedisField(signal).cString(), value ? 1 : 0);
        _signals[signal] = value;
    }
}

void D1E84SignalSequence::resetSequence()
{
    _sequence = SEQUENCE_0;
}

bool D1E84SignalSequence::setNextLoadSequence()
{
    return setNextSequence(true);
}

bool D1E84SignalSequence::setNextUnloadSequence()
{
    return setNextSequence(false);
}

D1E84SignalSequence::TIMEOUT D1E84SignalSequence::isSequenceTimedOut()
{
    if (_timer.isTimeover(false)) {
        return sequenceTimeoutType(_sequence);
    }
    return TIMEOUT_NA;
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
