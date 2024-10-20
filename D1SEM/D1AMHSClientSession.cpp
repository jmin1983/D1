//
// D1AMHSClientSession.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSClientSession.h"
#include "D1AMHSClientListener.h"
#include "D1AMHSDataManager.h"

#include <B1SECS2/B1SECS2DataManager.h>
#include <B1SECS2/B1SECS2DataTypes.h>

using namespace BnD;

D1AMHSClientSession::D1AMHSClientSession(B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener,
                                     uint16 secs2SessionID, const D1AMHSDataManager* secs2DataManager, D1AMHSClientListener* ownerListener)
    : B1SECS2ClientSession(clientSocket, listener, secs2SessionID, secs2DataManager)
    , _ownerListener(ownerListener)
{
}

void D1AMHSClientSession::onRecvMessageS1F4(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const std::vector<B1SECS2DataSV>& svs)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
    bool isProcessStatePaused = false;
    for (const auto& sv : svs) {
        if (amhsDataManager()->isSVIDProcessStatePaused(sv)) {
            isProcessStatePaused = true;
            break;
        }
    }
    //  TODO: continue implementation.
    if (isProcessStatePaused) {
        B1LOG("process state paused: sessionID[%d]", sessionID);
    }
    else {
        B1LOG("process state not paused: sessionID[%d]", sessionID);
    }


    //  for test.
    _ownerListener->onRequestOnlineCompleted(_secs2SessionID);



}

void D1AMHSClientSession::onRecvMessageS1F14(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                           const B1SECS2DataCOMMACK& commAck, const B1SECS2DataMDLN& mdln, const B1SECS2DataSOFTREV& softRev)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
    if (auto dataCommAck = amhsDataManager()->getDataCOMMACK(commAck)) {
        if (dataCommAck->data().empty() != true) {
            if (D1AMHSDataCOMMACK::VALUE_ACCEPTED == dataCommAck->data().front()) {
                if (sendMessageS1F17() != true) {
                    _ownerListener->onRequestOnlineFailed(_secs2SessionID);
                }
                return;
            }
        }
    }
    _ownerListener->onRequestOnlineFailed(_secs2SessionID);
}

void D1AMHSClientSession::onRecvMessageS1F16(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataOFLACK& oflAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS1F18(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataONLACK& onlAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
    if (auto dataOnlAck = amhsDataManager()->getDataONLACK(onlAck)) {
        if (dataOnlAck->data().empty() != true) {
            if (D1AMHSDataONLACK::VALUE_ON_LINE_ACCEPTED == dataOnlAck->data().front() ||
                D1AMHSDataONLACK::VALUE_EQ_ALREADY_ON_LINE == dataOnlAck->data().front()) {
                std::list<B1SECS2DataSVID> svIDs(1, amhsDataManager()->makeSVIDProcessState());
                if (sendMessageS1F3(svIDs) != true) {
                    _ownerListener->onRequestOnlineFailed(_secs2SessionID);
                }
            }
            else {
                _ownerListener->onRequestOnlineRejected(_secs2SessionID);
            }
            return;
        }
    }
    _ownerListener->onRequestOnlineFailed(_secs2SessionID);
}

void D1AMHSClientSession::onRecvMessageS2F32(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataTIACK& tiAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS2F34(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataDRACK& drAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS2F36(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataLRACK& lrAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS2F38(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataERACK& erAck)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS2F42(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                           const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS2F50(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                           const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCEPACK>& cps)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS5F1(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                          const B1SECS2DataALCD& alcd, const B1SECS2DataALID& alid, const B1SECS2DataALTX& altx)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS5F4(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataACKC5& ackc5)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS6F11(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                           const B1SECS2DataDATAID dataID, const B1SECS2DataCEID& ceID, const std::map<B1SECS2DataRPTID, std::vector<B1SECS2DataV> >& reportData)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onRecvMessageS64F2(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                           const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps)
{
    if (_secs2SessionID != sessionID) {
        sendMessageS1F0(sessionID, systemBytes);
        return;
    }
}

void D1AMHSClientSession::onSelectCompleted()
{
    _ownerListener->onSelectCompleted(_secs2SessionID);
}

void D1AMHSClientSession::implOnConnect()
{
    _ownerListener->onConnect(_secs2SessionID);
}

void D1AMHSClientSession::implOnDisconnected(int32 reason)
{
    _ownerListener->onDisconnected(_secs2SessionID, reason);
}

const D1AMHSDataManager* D1AMHSClientSession::amhsDataManager() const
{
    return static_cast<const D1AMHSDataManager*>(secs2DataManager());
}
