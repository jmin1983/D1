//
// D1AMHSServer.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSServer.h"
#include "D1AMHSServerSession.h"

#include <B1SEM/B1AMHSCarrierTransferStateRepository.h>
#include <B1SEM/B1AMHSPortStateRepository.h>
#include <B1SEM/B1AMHSStorageLocationStateRepository.h>
#include <B1SEM/B1AMHSTSSCStateRepository.h>
#include <B1SEM/B1AMHSVehicleStateRepository.h>

using namespace BnD;

D1AMHSServer::D1AMHSServer(uint16 deviceID, B1GEMConsts::COMM_STATE initialCommState, B1GEMConsts::CONTROL_STATE initialControlState)
    : B1GEMServer(deviceID, initialCommState, initialControlState)
{
}

D1AMHSServer::~D1AMHSServer()
{
}

auto D1AMHSServer::implInitializeCarrierTransferStateRepository() -> std::shared_ptr<B1AMHSCarrierTransferStateRepository>
{
    return std::shared_ptr<B1AMHSCarrierTransferStateRepository>();
}

auto D1AMHSServer::implInitializePortStateRepository() -> std::shared_ptr<B1AMHSPortStateRepository>
{
    return std::shared_ptr<B1AMHSPortStateRepository>();
}

auto D1AMHSServer::implInitializeStorageLocationStateRepository() -> std::shared_ptr<B1AMHSStorageLocationStateRepository>
{
    return std::shared_ptr<B1AMHSStorageLocationStateRepository>();
}

auto D1AMHSServer::implInitializeTSSCStateRepository() -> std::shared_ptr<B1AMHSTSSCStateRepository>
{
    auto repository = std::make_shared<B1AMHSTSSCStateRepository>();
    repository->initialize(this);
    return repository;
}

auto D1AMHSServer::implInitializeVehicleStateRepository() -> std::shared_ptr<B1AMHSVehicleStateRepository>
{
    return std::shared_ptr<B1AMHSVehicleStateRepository>();
}

bool D1AMHSServer::implInitialize(int32 port)
{
    if (B1GEMServer::implInitialize(port) != true) {
        return false;
    }
    _carrierTransferStateRepository = implInitializeCarrierTransferStateRepository();
    _portStateRepository = implInitializePortStateRepository();
    _storageLocationStateRepository = implInitializeStorageLocationStateRepository();
    _tsscStateRepository = implInitializeTSSCStateRepository();
    _vehicleStateRepository = implInitializeVehicleStateRepository();

    if (_vehicleStateRepository) {
        assert(false);  //  not implemented yet.
        return false;
    }

    return true;
}

void D1AMHSServer::implFinalize()
{
    if (_carrierTransferStateRepository) {
        _carrierTransferStateRepository->finalize();
        _carrierTransferStateRepository.reset();
    }
    if (_portStateRepository) {
        _portStateRepository->finalize();
        _portStateRepository.reset();
    }
    if (_storageLocationStateRepository) {
        _storageLocationStateRepository->finalize();
        _storageLocationStateRepository.reset();
    }
    if (_tsscStateRepository) {
        _tsscStateRepository->finalize();
        _tsscStateRepository.reset();
    }
    if (_vehicleStateRepository) {
        _vehicleStateRepository->finalize();
        _vehicleStateRepository.reset();
    }
    B1GEMServer::implFinalize();
}

bool D1AMHSServer::setCarrierStateWaitIn(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateWaitIn(taskID) : false;
}

bool D1AMHSServer::setCarrierStateTransferring(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateTransferring(taskID) : false;
}

bool D1AMHSServer::setCarrierStateCompleted(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateCompleted(taskID) : false;
}

bool D1AMHSServer::setCarrierStateWaitOut(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateWaitOut(taskID) : false;
}

bool D1AMHSServer::setCarrierStateNone(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateNone(taskID) : false;
}

bool D1AMHSServer::setCarrierStateAlternate(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setCarrierStateAlternate(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateQueued(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateQueued(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateWaiting(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateWaiting(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateTransferring(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateTransferring(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateCanceling(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateCanceling(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateNone(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateNone(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStatePaused(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStatePaused(taskID) : false;
}

bool D1AMHSServer::setTransferCommandStateAborting(int64 taskID)
{
    return _carrierTransferStateRepository ? _carrierTransferStateRepository->setTransferCommandStateAborting(taskID) : false;
}

void D1AMHSServer::setPortStateInService(int32 portID)
{
    if (_portStateRepository) {
        _portStateRepository->setPortStateInService(portID);
    }
}

void D1AMHSServer::setPortStateOutOfService(int32 portID)
{
    if (_portStateRepository) {
        _portStateRepository->setPortStateOutOfService(portID);
    }
}

bool D1AMHSServer::isPortStateInService(int32 portID) const
{
    return _portStateRepository ? _portStateRepository->isPortStateInService(portID) : false;
}

void D1AMHSServer::setStorageLocationStateEnabled(int32 locationID)
{
    if (_storageLocationStateRepository) {
        _storageLocationStateRepository->setStorageLocationStateEnabled(locationID);
    }
}

void D1AMHSServer::setStorageLocationStateDisabled(int32 locationID)
{
    if (_storageLocationStateRepository) {
        _storageLocationStateRepository->setStorageLocationStateDisabled(locationID);
    }
}

bool D1AMHSServer::isStorageLocationStateEnabled(int32 locationID) const
{
    return _storageLocationStateRepository ? _storageLocationStateRepository->isStorageLocationStateEnabled(locationID) : false;
}

bool D1AMHSServer::setSystemStateInit()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemStateInit() : false;
}

bool D1AMHSServer::setSystemStatePausing()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemStatePausing() : false;
}

bool D1AMHSServer::setSystemStatePaused()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemStatePaused() : false;
}

bool D1AMHSServer::setSystemStateAuto()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemStateAuto() : false;
}

void D1AMHSServer::setSystemAvailStateInService()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemAvailStateInService() : false;
}

void D1AMHSServer::setSystemAvailStateOutOfService()
{
    return _tsscStateRepository ? _tsscStateRepository->setSystemAvailStateOutOfService() : false;
}

bool D1AMHSServer::isSystemStatePausing() const
{
    return _tsscStateRepository ? _tsscStateRepository->isSystemStatePausing() : false;
}

bool D1AMHSServer::isSystemStatePaused() const
{
    return _tsscStateRepository ? _tsscStateRepository->isSystemStatePaused() : false;
}

bool D1AMHSServer::isSystemStateAuto() const
{
    return _tsscStateRepository ? _tsscStateRepository->isSystemStateAuto() : false;
}

bool D1AMHSServer::isSystemAvailStateInService() const
{
    return _tsscStateRepository ? _tsscStateRepository->isSystemAvailStateInService() : false;
}

bool D1AMHSServer::isSystemAvailStateOutOfService() const
{
    return _tsscStateRepository ? _tsscStateRepository->isSystemAvailStateOutOfService() : false;
}
