//
// D1AMHSDataRepositoryDefault.h
//
// Library: D1SEM
// Package: AMHSDefault
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_DATA_REPOSITORY_DEFAULT_H
#define _D1SEM_AMHS_DATA_REPOSITORY_DEFAULT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1GEM/B1GEMDataRepository.h>

namespace BnD {
    namespace D1AMHSDataDictionaryDefault {
        enum class DEFAULT_VID;
        enum class DEFAULT_CEID;
        enum class DEFAULT_ALID;
    };
    class B1GEMEquipmentConstant;
    class B1GEMEquipmentConstantSetter;
    class B1GEMVariable;
    class D1AMHSDataManagerDefault;
    class D1AMHSStatusVariable;
    class D1AMHSVariable;
    class D1AMHSDataRepositoryDefault : public B1GEMDataRepository {
    protected:
        B1GEMAlarmRepository* createAlarmRepository(const B1SECS2DataManager* secs2DataManager) final;          //  return NULL if init failed.
        B1GEMEventRepository* createEventRepository(const B1SECS2DataManager* secs2DataManager) final;          //  return NULL if init failed.
        B1GEMVariableRepository* createVariableRepository(const B1SECS2DataManager* secs2DataManager) final;    //  return NULL if init failed.
    protected:
        void addAlarm(D1AMHSDataDictionaryDefault::DEFAULT_ALID alID,
                      D1AMHSDataDictionaryDefault::DEFAULT_CEID ceIDSet, D1AMHSDataDictionaryDefault::DEFAULT_CEID ceIDCleared, B1String&& txt,
                      const D1AMHSDataManagerDefault* dataManager, std::map<B1SECS2DataALID, std::pair<B1GEMAlarm, B1GEMAlarm> >* alarms) const;
        void addEvent(D1AMHSDataDictionaryDefault::DEFAULT_CEID ceID, B1String&& name,
                      const D1AMHSDataManagerDefault* dataManager, std::set<B1GEMEvent>* events) const;
        void addEC(D1AMHSDataDictionaryDefault::DEFAULT_VID vID, B1GEMEquipmentConstantSetter* ec,
                   const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataECID, std::shared_ptr<B1GEMEquipmentConstant> >* ecs) const;
        void addSV(D1AMHSDataDictionaryDefault::DEFAULT_VID vID, D1AMHSStatusVariable* sv,
                   const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataSVID, std::shared_ptr<B1GEMStatusVariable> >* svs) const;
        void addV(D1AMHSDataDictionaryDefault::DEFAULT_VID vID, D1AMHSVariable* v,
                   const D1AMHSDataManagerDefault* dataManager, std::map<const B1SECS2DataVID, std::shared_ptr<B1GEMVariable> >* vs) const;
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_DATA_REPOSITORY_DEFAULT_H
