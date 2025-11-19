//
// D1AMHSServer.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_SERVER_H
#define _D1SEM_AMHS_SERVER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1GEM/B1GEMServer.h>
#include <B1SEM/B1AMHSCarrierTransferStateRepositoryListener.h>
#include <B1SEM/B1AMHSPortStateRepositoryListener.h>
#include <B1SEM/B1AMHSStorageLocationStateRepositoryListener.h>
#include <B1SEM/B1AMHSTSSCStateRepositoryListener.h>
#include <B1SEM/B1AMHSVehicleStateRepositoryListener.h>

namespace BnD {
    class B1AMHSCarrierTransferStateRepository;
    class B1AMHSPortStateRepository;
    class B1AMHSStorageLocationStateRepository;
    class B1AMHSTSSCStateRepository;
    class B1AMHSVehicleStateRepository;
    class D1AMHSServer : protected B1AMHSCarrierTransferStateRepositoryListener
                       , protected B1AMHSPortStateRepositoryListener
                       , protected B1AMHSStorageLocationStateRepositoryListener
                       , protected B1AMHSTSSCStateRepositoryListener
                       , protected B1AMHSVehicleStateRepositoryListener
                       , public B1GEMServer {
    public:
        D1AMHSServer(uint16 deviceID, B1GEMConsts::COMM_STATE initialCommState, B1GEMConsts::CONTROL_STATE initialControlState);
        virtual ~D1AMHSServer();
    protected:
        std::shared_ptr<B1AMHSCarrierTransferStateRepository> _carrierTransferStateRepository;
        std::shared_ptr<B1AMHSPortStateRepository> _portStateRepository;
        std::shared_ptr<B1AMHSStorageLocationStateRepository> _storageLocationStateRepository;
        std::shared_ptr<B1AMHSTSSCStateRepository> _tsscStateRepository;
        std::shared_ptr<B1AMHSVehicleStateRepository> _vehicleStateRepository;
    protected:  //  return NULL if not used.
        virtual std::shared_ptr<B1AMHSCarrierTransferStateRepository> implInitializeCarrierTransferStateRepository();
        virtual std::shared_ptr<B1AMHSPortStateRepository> implInitializePortStateRepository();
        virtual std::shared_ptr<B1AMHSStorageLocationStateRepository> implInitializeStorageLocationStateRepository();
        virtual std::shared_ptr<B1AMHSTSSCStateRepository> implInitializeTSSCStateRepository();
        virtual std::shared_ptr<B1AMHSVehicleStateRepository> implInitializeVehicleStateRepository();
    protected:
        virtual bool implInitialize(int32 port) override;
        virtual void implFinalize() override;
    public:
        bool setCarrierStateWaitIn(int64 taskID);
        bool setCarrierStateTransferring(int64 taskID);
        bool setCarrierStateCompleted(int64 taskID);
        bool setCarrierStateWaitOut(int64 taskID);
        bool setCarrierStateNone(int64 taskID);
        bool setCarrierStateAlternate(int64 taskID);
        bool setTransferCommandStateQueued(int64 taskID);
        bool setTransferCommandStateWaiting(int64 taskID);
        bool setTransferCommandStateTransferring(int64 taskID);
        bool setTransferCommandStateCanceling(int64 taskID);
        bool setTransferCommandStateNone(int64 taskID);
        bool setTransferCommandStatePaused(int64 taskID);
        bool setTransferCommandStateAborting(int64 taskID);

        void setPortStateInService(int32 portID);
        void setPortStateOutOfService(int32 portID);
        bool isPortStateInService(int32 portID) const;

        void setStorageLocationStateEnabled(int32 locationID);
        void setStorageLocationStateDisabled(int32 locationID);
        bool isStorageLocationStateEnabled(int32 locationID) const;

        bool setSystemStateInit();
        bool setSystemStatePausing();
        bool setSystemStatePaused();
        bool setSystemStateAuto();
        void setSystemAvailStateInService();
        void setSystemAvailStateOutOfService();
        bool isSystemStatePausing() const;
        bool isSystemStatePaused() const;
        bool isSystemStateAuto() const;
        bool isSystemAvailStateInService() const;
        bool isSystemAvailStateOutOfService() const;

        //  B1AMHSVehicleStateRepository is not ready.
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_SERVER_H
