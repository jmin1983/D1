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
#include "D1AMHSDataManager.h"

#include <B1SECS2/B1SECS2DataManager.h>
#include <B1SECS2/B1SECS2DataTypes.h>

using namespace BnD;

D1AMHSClientSession::D1AMHSClientSession(B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener)
    : B1GEMClientSession(clientSocket, listener)
{
}

void D1AMHSClientSession::onRecvMessageS1F4(const std::vector<uint8>& systemBytes, const std::vector<B1SECS2DataSV>& svs)
{
    //bool isProcessStatePaused = false;
    //for (const auto& sv : svs) {
    //    if (amhsDataManager()->isSVIDProcessStatePaused(sv)) {
    //        isProcessStatePaused = true;
    //        break;
    //    }
    //}
    ////  TODO: continue implementation.
    //if (isProcessStatePaused) {
    //    B1LOG("process state paused: deviceID[%d]", deviceID());
    //}
    //else {
    //    B1LOG("process state not paused: deviceID[%d]", deviceID());
    //}
    //onAMHSRequestOnlineCompleted();
}

void D1AMHSClientSession::onRecvMessageS1F14(const std::vector<uint8>& systemBytes,
                                             const B1SECS2DataCOMMACK& commAck, const B1SECS2DataMDLN& mdln, const B1SECS2DataSOFTREV& softRev)
{
    //if (auto dataCommAck = amhsDataManager()->getDataCOMMACK(commAck)) {
    //    if (dataCommAck->data().empty() != true) {
    //        if (D1AMHSDataCOMMACK::VALUE_ACCEPTED == dataCommAck->data().front()) {
    //            if (sendMessageS1F17() != true) {
    //                onAMHSRequestOnlineFailed();
    //            }
    //            return;
    //        }
    //    }
    //}
    //onAMHSRequestOnlineFailed();
}

void D1AMHSClientSession::onRecvMessageS1F16(const std::vector<uint8>& systemBytes, const B1SECS2DataOFLACK& oflAck)
{
}

void D1AMHSClientSession::onRecvMessageS1F18(const std::vector<uint8>& systemBytes, const B1SECS2DataONLACK& onlAck)
{
    //if (auto dataOnlAck = amhsDataManager()->getDataONLACK(onlAck)) {
    //    if (dataOnlAck->data().empty() != true) {
    //        if (D1AMHSDataONLACK::VALUE_ON_LINE_ACCEPTED == dataOnlAck->data().front() ||
    //            D1AMHSDataONLACK::VALUE_EQ_ALREADY_ON_LINE == dataOnlAck->data().front()) {
    //            std::list<B1SECS2DataSVID> svIDs(1, amhsDataManager()->makeSVIDProcessState());
    //            if (sendMessageS1F3(svIDs) != true) {
    //                onAMHSRequestOnlineFailed();
    //            }
    //        }
    //        else {
    //            onAMHSRequestOnlineRejected();
    //        }
    //        return;
    //    }
    //}
    //onAMHSRequestOnlineFailed();
}

void D1AMHSClientSession::onRecvMessageS2F32(const std::vector<uint8>& systemBytes, const B1SECS2DataTIACK& tiAck)
{
}

void D1AMHSClientSession::onRecvMessageS2F34(const std::vector<uint8>& systemBytes, const B1SECS2DataDRACK& drAck)
{
}

void D1AMHSClientSession::onRecvMessageS2F36(const std::vector<uint8>& systemBytes, const B1SECS2DataLRACK& lrAck)
{
}

void D1AMHSClientSession::onRecvMessageS2F38(const std::vector<uint8>& systemBytes, const B1SECS2DataERACK& erAck)
{
}

void D1AMHSClientSession::onRecvMessageS2F42(const std::vector<uint8>& systemBytes,
                                             const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps)
{
}

void D1AMHSClientSession::onRecvMessageS2F50(const std::vector<uint8>& systemBytes,
                                             const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCEPACK>& cps)
{
}

void D1AMHSClientSession::onRecvMessageS5F1(bool wait, const std::vector<uint8>& systemBytes,
                                            const B1SECS2DataALCD& alcd, const B1SECS2DataALID& alid, const B1SECS2DataALTX& altx)
{
}

void D1AMHSClientSession::onRecvMessageS5F4(const std::vector<uint8>& systemBytes, const B1SECS2DataACKC5& ackc5)
{
}

void D1AMHSClientSession::onRecvMessageS6F11(bool wait, const std::vector<uint8>& systemBytes,
                                             const B1SECS2DataDATAID dataID, const B1SECS2DataCEID& ceID, const std::map<B1SECS2DataRPTID, std::vector<B1SECS2DataV> >& reportData)
{
}

void D1AMHSClientSession::onRecvMessageS64F2(const std::vector<uint8>& systemBytes,
                                             const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps)
{
}

auto D1AMHSClientSession::createSECS2DataManager() -> std::shared_ptr<B1SECS2DataManager>
{
    return createAMHSDataManager();
}

void D1AMHSClientSession::onSelectCompleted()
{
    onAMHSSelectCompleted();
}

void D1AMHSClientSession::implOnConnect()
{
    onAMHSConnect();
}

void D1AMHSClientSession::implOnDisconnected(int32 reason)
{
    onAMHSDisconnected(reason);
}

const D1AMHSDataManager* D1AMHSClientSession::amhsDataManager() const
{
    return static_cast<const D1AMHSDataManager*>(secs2DataManager());
}
