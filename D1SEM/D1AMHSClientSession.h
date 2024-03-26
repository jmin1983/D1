//
// D1AMHSClientSession.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_CLIENT_SESSION_H
#define _D1SEM_AMHS_CLIENT_SESSION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2ClientSession.h>

namespace BnD {
    class D1AMHSClientListener;
    class D1AMHSDataManager;
    class D1AMHSClientSession : public B1SECS2ClientSession {
    public:
        D1AMHSClientSession(B1ClientSocket* clientSocket, B1BaseClientSessionListener* listener,
                          uint16 secs2SessionID, const D1AMHSDataManager* secs2DataManager, D1AMHSClientListener* ownerListener);
    protected:
        D1AMHSClientListener* _ownerListener;
    protected:
        virtual void onRecvMessageS1F4(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const std::vector<B1SECS2DataSV>& svs) override;
        virtual void onRecvMessageS1F14(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                        const B1SECS2DataCOMMACK& commAck, const B1SECS2DataMDLN& mdln, const B1SECS2DataSOFTREV& softRev) override;
        virtual void onRecvMessageS1F16(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataOFLACK& oflAck) override;
        virtual void onRecvMessageS1F18(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataONLACK& onlAck) override;
        virtual void onRecvMessageS2F32(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataTIACK& tiAck) override;
        virtual void onRecvMessageS2F34(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataDRACK& drAck) override;
        virtual void onRecvMessageS2F36(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataLRACK& lrAck) override;
        virtual void onRecvMessageS2F38(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataERACK& erAck) override;
        virtual void onRecvMessageS2F42(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                        const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps) override;
        virtual void onRecvMessageS2F50(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                        const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCEPACK>& cps) override;
        virtual void onRecvMessageS5F1(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                       const B1SECS2DataALCD& alcd, const B1SECS2DataALID& alid, const B1SECS2DataALTX& altx) override;
        virtual void onRecvMessageS5F4(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes, const B1SECS2DataACKC5& ackc5) override;
        virtual void onRecvMessageS6F11(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                        const B1SECS2DataDATAID dataID, const B1SECS2DataCEID& ceID, const std::map<B1SECS2DataRPTID, std::vector<B1SECS2DataV> >& reportData) override;
        virtual void onRecvMessageS64F2(uint16 sessionID, bool wait, const std::vector<uint8>& systemBytes,
                                        const B1SECS2DataHCACK& hcAck, const std::map<B1SECS2DataCPNAME, B1SECS2DataCPACK>& cps) override;
    protected:
        void onSelectCompleted() final;
        void implOnConnect() final;
        void implOnDisconnected(int32 reason) final;
    protected:
        const D1AMHSDataManager* amhsDataManager() const;
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_CLIENT_SESSION_H
