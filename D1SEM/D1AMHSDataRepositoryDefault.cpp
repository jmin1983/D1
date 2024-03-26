//
// D1AMHSDataRepositoryDefault.cpp
//
// Library: D1SEM
// Package: AMHSDefault
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSDataRepositoryDefault.h"
#include "D1AMHSDataManagerDefault.h"
#include "D1AMHSStatusVariable.h"
#include "D1AMHSVariable.h"

#include <B1GEM/B1GEMAlarmRepository.h>
#include <B1GEM/B1GEMEventRepository.h>
#include <B1GEM/B1GEMReportRepository.h>
#include <B1GEM/B1GEMVariableRepository.h>

using namespace BnD;
using namespace D1AMHSDataDictionaryDefault;

B1GEMAlarmRepository* D1AMHSDataRepositoryDefault::createAlarmRepository(const B1SECS2DataManager* secs2DataManager)
{
    auto dataManager = dynamic_cast<const D1AMHSDataManagerDefault*>(secs2DataManager);
    if (dataManager == NULL) {
        assert(false);
        return NULL;
    }
    std::map<B1SECS2DataALID, std::pair<B1GEMAlarm, B1GEMAlarm> > alarms;


    //addAlarm(DEFAULT_ALID_SYSTEM_FAILOVERED, DEFAULT_CEID_ALARM_SYSTEM_FAILOVERED_SET, DEFAULT_CEID_ALARM_SYSTEM_FAILOVERED_CLR,
    //         "System failover completed", dataManager, &alarms);



    auto repository = new B1GEMAlarmRepository();
    if (repository->initialize(alarms) != true) {
        delete repository;
        repository = NULL;
    }
    return repository;
}

B1GEMEventRepository* D1AMHSDataRepositoryDefault::createEventRepository(const B1SECS2DataManager* secs2DataManager)
{
    auto dataManager = dynamic_cast<const D1AMHSDataManagerDefault*>(secs2DataManager);
    if (dataManager == NULL) {
        assert(false);
        return NULL;
    }
    std::set<B1GEMEvent> events;
    //addEvent(DEFAULT_CEID_ALARM_CARRIER_FOUND_SET, "AlarmCarrierFoundSet", dataManager, &events);



    auto repository = new B1GEMEventRepository();
    if (repository->initialize(events) != true) {
        delete repository;
        repository = NULL;
    }
    return repository;
}

B1GEMVariableRepository* D1AMHSDataRepositoryDefault::createVariableRepository(const B1SECS2DataManager* secs2DataManager)
{
    auto dataManager = dynamic_cast<const D1AMHSDataManagerDefault*>(secs2DataManager);
    if (dataManager == NULL) {
        assert(false);
        return NULL;
    }
    std::map<const B1SECS2DataECID, SPGEMEquipmentConstant> ecs;
    //addEC(DEFAULT_VID_EQP_MODEL, new ECEqpModel(), dataManager, &ecs);

    const int32 hostID = 0;
    std::map<const B1SECS2DataSVID, SPB1GEMStatusVariable> svs;
    //addSV(DEFAULT_VID_ACTIVE_CARRIERS, new SVActiveCarriersDefault(), dataManager, &svs);


    std::map<const B1SECS2DataVID, SPGEMVariable> vs;
    //addV(DEFAULT_VID_CARRIER_ID, new VCarrierID(), dataManager, &vs);


    auto repository = new B1GEMVariableRepository();
    if (repository->initialize(ecs, svs, vs) != true) {
        delete repository;
        repository = NULL;
    }
    return repository;
}

void D1AMHSDataRepositoryDefault::addAlarm(DEFAULT_ALID alID, DEFAULT_CEID ceIDSet, DEFAULT_CEID ceIDCleared, B1String&& txt,
                                           const D1AMHSDataManagerDefault* dataManager, std::map<B1SECS2DataALID, std::pair<B1GEMAlarm, B1GEMAlarm> >* alarms) const
{
    auto amhsALID = dataManager->getNewALID();
    amhsALID->setData(static_cast<uint32>(alID));
    auto amhsALTX = dataManager->getNewALTX();
    amhsALTX->setData(std::move(txt));
    auto amhsALCDSet = dataManager->getNewALCD();
    amhsALCDSet->setAlarm(true);
    auto amhsALCDCleared = dataManager->getNewALCD();
    amhsALCDCleared->setAlarm(false);
    auto amhsCEIDSet = dataManager->getNewCEID();
    amhsCEIDSet->setData(static_cast<uint32>(ceIDSet));
    auto amhsCEIDCleared = dataManager->getNewCEID();
    amhsCEIDCleared->setData(static_cast<uint32>(ceIDCleared));

    const B1SECS2DataALID secs2DataALID(amhsALID);
    const B1SECS2DataALTX secs2DataALTX(amhsALTX);

    assert(alarms->find(secs2DataALID) == alarms->end());

    alarms->insert(std::make_pair(secs2DataALID,
                   std::make_pair(B1GEMAlarm(secs2DataALID, B1SECS2DataALCD(amhsALCDSet),     secs2DataALTX, B1SECS2DataCEID(amhsCEIDSet)),
                                  B1GEMAlarm(secs2DataALID, B1SECS2DataALCD(amhsALCDCleared), secs2DataALTX, B1SECS2DataCEID(amhsCEIDCleared)))));
}

void D1AMHSDataRepositoryDefault::addEvent(DEFAULT_CEID ceID, B1String&& name,
                                           const D1AMHSDataManagerDefault* dataManager, std::set<B1GEMEvent>* events) const
{
    auto amhsCEID = dataManager->getNewCEID();
    amhsCEID->setData(static_cast<uint32>(ceID));
    auto amhsCENAME = dataManager->getNewCENAME();
    amhsCENAME->setData(std::move(name));

    assert(events->find(B1GEMEvent(B1SECS2DataCEID(amhsCEID), B1SECS2DataCENAME(amhsCENAME))) == events->end());

    events->insert(B1GEMEvent(B1SECS2DataCEID(amhsCEID), B1SECS2DataCENAME(amhsCENAME)));
}

void D1AMHSDataRepositoryDefault::addEC(DEFAULT_VID vID, B1GEMEquipmentConstantSetter* ec,
                                        const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataECID, SPGEMEquipmentConstant>* ecs) const
{
    auto amhsDataECID = dataManager->getNewECID();
    amhsDataECID->setData(static_cast<uint32>(vID));
    auto amhsDataECNAME = dataManager->getNewECNAME();
    amhsDataECNAME->setData(ec->label().copy());
    auto amhsDataUNITS = dataManager->getNewUNITS();
    amhsDataUNITS->setData("");

    const B1SECS2DataECID secs2DataECID(amhsDataECID);

    assert(ecs->find(secs2DataECID) == ecs->end());

    ec->setData(secs2DataECID, B1SECS2DataECNAME(amhsDataECNAME), B1SECS2DataUNITS(amhsDataUNITS));
    ecs->insert(std::make_pair(secs2DataECID, ec));
}

void D1AMHSDataRepositoryDefault::addSV(DEFAULT_VID vID, D1AMHSStatusVariable* sv,
                                        const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataSVID, SPB1GEMStatusVariable>* svs) const
{
    auto amhsDataSVID = dataManager->getNewSVID();
    amhsDataSVID->setData(static_cast<uint32>(vID));
    auto amhsDataSVNAME = dataManager->getNewSVNAME();
    amhsDataSVNAME->setData(sv->label().copy());
    auto amhsDataUNITS = dataManager->getNewUNITS();
    amhsDataUNITS->setData("");

    const B1SECS2DataSVID secs2DataSVID(amhsDataSVID);

    assert(svs->find(secs2DataSVID) == svs->end());

    sv->setData(secs2DataSVID, B1SECS2DataSVNAME(amhsDataSVNAME), B1SECS2DataUNITS(amhsDataUNITS));
    svs->insert(std::make_pair(secs2DataSVID, sv));
}

void D1AMHSDataRepositoryDefault::addV(DEFAULT_VID vID, D1AMHSVariable* v,
                                       const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataVID, std::shared_ptr<B1GEMVariable> >* vs) const
{
    auto amhsDataVID = dataManager->getNewVID();
    amhsDataVID->setData(static_cast<uint32>(vID));

    const B1SECS2DataVID secs2DataVID(amhsDataVID);

    assert(vs->find(secs2DataVID) == vs->end());

    v->setData(secs2DataVID);
    vs->insert(std::make_pair(secs2DataVID, v));
}
