//
// D1E84SignalSequence.h
//
// Library: D1Data
// Package: D1Data
// Module:  D1Data
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1DATA_E84_SIGNAL_SEQUENCE_H
#define _D1DATA_E84_SIGNAL_SEQUENCE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1Util/B1TimeChecker.h>

#include <map>

namespace BnD {
    class D1E84SignalSequence {
    public:
        D1E84SignalSequence(int32 zoneID);
        virtual ~D1E84SignalSequence() {}
    public:
        enum CONSTS {
            CONSTS_DEFAULT_TIMEOUT = 60 * 1000, //  60sec
        };
    public:
        enum SIGNAL {
            SIGNAL_VALID = 0,   //  A->P. Indicates that the signal transition is active and selected. before this signal is on, the load port must be specified by CS_0, CS_1.
            SIGNAL_CS_0,        //  A->P. Carrier Stage 0. ON: use the load port for carrier handoff. OFF: NA(for device per 2 load ports. not used for single load port).
            SIGNAL_CS_1,        //  A->P. Carrier Stage 1. always OFF for single load port.
            SIGNAL_TR_REQ,      //  A->P. Requests the handoff to the EQ.
            SIGNAL_L_REQ,       //  P->A. load port is assigned. turns ON when VALID_on. turns OFF when the load port detects the carrier in the correct position.
            SIGNAL_U_REQ,       //  P->A. load port is assigned. turns ON when VALID_on. turns OFF when the carrier on the load port is removed.
            SIGNAL_READY,       //  P->A. EQ has accepted the transfer request from OHT. turns ON when EQ accepts the transfer request. turns OFF when the COMPT_on.
            SIGNAL_BUSY,        //  A->P. handoff is in progress. turns ON when the OHT starts handoff operation(must be READY_on). turns OFF when after confirming L_REQ/R_REQ off.
            SIGNAL_COMPT,       //  A->P. OHT completed the handoff operation. turns ON when OHT completed the handoff(BUSY_off). turns OFF when EQ completed the handoff(READY_off).
            SIGNAL_CONT,        //  A->P. Specifies the handoff is continuous_handoff.
            SIGNAL_HO_AVBL,     //  P->A. EQ is not available for the handoff operation. turns ON when EQ is normal. turns OFF and keeps OFF when EQ port has exception.
            SIGNAL_ES,          //  P->A. Request to stop OHT activity immediately. turns ON when EQ is normal. turns OFF when critical situation like ES buttons is pressed or alarmed.

            SIGNAL_COUNTS,
        };
        enum TIMEOUT {
            TIMEOUT_TA1 = 0,    //  VALID_on ~ L_REQ(U_REQ)_on
            //TIMEOUT_TA2,        //  TR_REQ_on ~ READY_on
            //TIMEOUT_TA3,        //  COMPT_on ~ READY_off
            TIMEOUT_TP1,        //  L_REQ(U_REQ)_on ~ TR_REQ_on
            TIMEOUT_TP2,        //  READY_on ~ BUSY_on
            TIMEOUT_TP3,        //  BUSY_on ~ L_REQ(U_REQ)_off
            TIMEOUT_TP4,        //  L_REQ(U_REQ)_off ~ BUSY_off
            TIMEOUT_TP5,        //  READY_off ~ VALID_off
            //TIMEOUT_TP6,        //  VALID_off ~ VALID_on(continuous handoff)

            TIMEOUT_COUNTS,
            TIMEOUT_NA = 252,
        };
        enum SEQUENCE {
            SEQUENCE_0 = 0, //  EQ is waiting for OHT.
            SEQUENCE_1,     //  OHT reaches the load port, the OHT specifies the load port number to the EQ using CS_0 and CS_1.
            SEQUENCE_2,     //  OHT turns VALID_on. It shows that the signal transition of CS_0 and CS1 is valid.
            SEQUENCE_3,     //  EQ turns L_REQ_on for LOAD, U_REQ_on for UNLOAD.
            SEQUENCE_4,     //  OHT turns TR_REQ_on to begin EQ handoff operation.
            SEQUENCE_5,     //  EQ turns READY_on to begin OHT handoff operation.
            SEQUENCE_6,     //  OHT checks READY_on, and then OHT turns BUSY_on and start handoff operation.
            SEQUENCE_7,     //  EQ turns L_REQ(or U_REQ)_off when carrier is placed correctly on the load port(or the carrier on the load port is removed).
            SEQUENCE_8,     //  OHT turns BUSY_off. OHT MUST CONFIRM L_REQ(OR U_REQ) IS TURNED OFF BEFORE THE BUSY SIGNAL TURN OFF.
            SEQUENCE_9,     //  OHT turns TR_REQ_off.
            SEQUENCE_10,    //  OHT turns COMPT_on to inform the EQ about the completion of the handoff operation.
            SEQUENCE_11,    //  EQ checks COMPT_on, and then EQ turns READY_off.
            SEQUENCE_12,    //  OHT checks READY_off, and then OHT turns off COMPT, VALID, CS_0, CS_1.
            SEQUENCE_13,    //  checks VALID_off, this means the handshake with the EQ is closed.
        };
        /*
        Load Sequence:
                            L_REQ   U_REQ   READY   CS_0    CS_1    VALID | TR_REQ  BUSY    COMPT   CONT    HO_AVBL     ES
        0.                  0       0       0       0       0       0     | 0       0       0       0       1(P)        1(P)
        1.                                          1(A)                  |
        2. CS Spcified                                              1(A)  |
        3.                  1(P)                                          |
        4.                                                                | 1(A)
        5.                                  1(P)                          |
        6. Transfer Begin                                                 |         1(A)
        ----------------------------------------------------------------------------------------------------------------------------------
        7. Carrier Detected 0(P)                                          |
        8.                                                                |         0(A)
        9.                                                                | 0(A)
        10. Transfer End                                                  |                 1(A)
        11.                                 0(P)                          |
        12. Release CS                              0(A)            0(A)  |                 0(A)
        13. closed                                                  cks(P)|
        */
        /*
        Unload Sequence:
                            L_REQ   U_REQ   READY   CS_0    CS_1    VALID | TR_REQ  BUSY    COMPT   CONT    HO_AVBL     ES
        0.                  0       0       0       0       0       0     | 0       0       0       0       1(P)        1(P)
        1.                                          1(A)                  |
        2. CS Spcified                                              1(A)  |
        3.                          1(P)                                  |
        4.                                                                | 1(A)
        5.                                  1(P)                          |
        6. Transfer Begin                                                 |         1(A)
        ----------------------------------------------------------------------------------------------------------------------------------
        7. Carrier Removed          0(P)                                  |
        8.                                                                |         0(A)
        9.                                                                | 0(A)
        10. Transfer End                                                  |                 1(A)
        11.                                 0(P)                          |
        12. Release CS                              0(A)            0(A)  |                 0(A)
        13. closed                                                  cks(P)|
        */
    protected:
        const int32 _zoneID;
        SEQUENCE _sequence;
        std::vector<bool> _signals;             //  vector<SIGNAL>
        B1TimeChecker _timer;
        static std::vector<uint32> _timeouts;   //  vector<TIMEOUT>
    private:
        bool isSignalOn(SIGNAL signal) const;   //  use private only.
        bool isSignalOff(SIGNAL signal) const;  //  use private only.
    protected:
        bool isSequenceSignalReadyToProceed(SEQUENCE sequence, bool isLoading) const;   //  return true if signal is ready to procceed to next _sequence.
        uint32 timeoutValue(TIMEOUT timeout) const;
        TIMEOUT sequenceTimeoutType(SEQUENCE sequence) const;
    public:
        D1E84SignalSequence& operator=(const D1E84SignalSequence& r);
        bool operator==(const D1E84SignalSequence& r) const;
        bool operator!=(const D1E84SignalSequence& r) const { return operator==(r) != true; }
    public:
        SEQUENCE sequence() const { return _sequence; }
        bool isInSequence() const { return sequence() != SEQUENCE_0; }
        bool needToTurnOnLREQ(bool isLoadingSequence) const { return isLoadingSequence && sequence() == SEQUENCE_2; }
        bool needToTurnOnUREQ(bool isLoadingSequence) const { return isLoadingSequence != true && sequence() == SEQUENCE_2; }
        bool needToTurnOnREADY() const { return sequence() == SEQUENCE_4; }
        bool needToTurnOffLREQ(bool isLoadingSequence) const { return isLoadingSequence && sequence() == SEQUENCE_6; }
        bool needToTurnOffUREQ(bool isLoadingSequence) const { return isLoadingSequence != true && sequence() == SEQUENCE_6; }
        bool needToTurnOffREADY() const { return sequence() == SEQUENCE_10; }
        bool isOn(SIGNAL signal) const;
        bool isOff(SIGNAL signal) const;
        bool isCarrierDetectedSequence() const { return sequence() == SEQUENCE_7; }
        bool isCarrierRemovedSequence() const { return sequence() == SEQUENCE_7; }
        void resetSequence();                               //  WARNING. CRITICAL IF E84 SEQUENCE IN PROGRESS.
        bool proceedNextSequence(bool isLoadingSequence);   //  return true if proceeded to next sequence.
        bool isSequenceSignalInvalid() const;
        TIMEOUT isSequenceTimedOut();
        std::vector<bool>& signals() { return _signals; }
        B1String toString() const;
    public:
        static void initTimeoutValues(const std::vector<uint32>& timeouts); //  size: TIMEOUT_COUNTS
    };
}   //  !BnD

#endif  // !_D1DATA_E84_SIGNAL_SEQUENCE_H
