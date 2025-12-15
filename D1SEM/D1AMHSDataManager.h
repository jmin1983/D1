//
// D1AMHSDataManager.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_DATA_MANAGER_H
#define _D1SEM_AMHS_DATA_MANAGER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2DataManager.h>

#include <D1SEM/D1AMHSDataDictionary.h>

#define IMPL_AMHS_DATA_FUNCTION(t, d)\
    std::shared_ptr<t##d> getNew##d() const\
    { return std::dynamic_pointer_cast<t##d>(getNewData(B1SECS2DataBase::INDEX_##d)); }\
    const t##d* getData##d(const B1SECS2DataBase& secs2Data) const\
    { return static_cast<const t##d*>(secs2Data.data().get()); }

namespace BnD {
    class D1AMHSDataManager : public B1SECS2DataManager {
    protected:
        B1SECS2Data* createOriginalData(B1SECS2DataBase::INDEX index) const final;
    protected:
        virtual B1SECS2Data* createALID() const = 0;
        virtual B1SECS2Data* createALTX() const = 0;
        virtual B1SECS2Data* createCEID() const = 0;
        virtual B1SECS2Data* createECID() const = 0;
        virtual B1SECS2Data* createECNAME() const = 0;
        virtual B1SECS2Data* createMDLN() const = 0;
        virtual B1SECS2Data* createRPTID() const = 0;
        virtual B1SECS2Data* createSOFTREV() const = 0;
        virtual B1SECS2Data* createSVID() const = 0;
        virtual B1SECS2Data* createSVNAME() const = 0;
        virtual B1SECS2Data* createVID() const = 0;
    public:
#define IMPL_AMHS_DATA_FUNCTION_BASE(d) IMPL_AMHS_DATA_FUNCTION(D1AMHSData, d)
        IMPL_AMHS_DATA_FUNCTION_BASE(ACKC5);
        IMPL_AMHS_DATA_FUNCTION_BASE(ACKC6);
        IMPL_AMHS_DATA_FUNCTION_BASE(ALCD);
        IMPL_AMHS_DATA_FUNCTION_BASE(ALED);
        IMPL_AMHS_DATA_FUNCTION_BASE(CEED);
        IMPL_AMHS_DATA_FUNCTION_BASE(CENAME);
        IMPL_AMHS_DATA_FUNCTION_BASE(CEPACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(COMMACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(CPACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(CPNAME);
        IMPL_AMHS_DATA_FUNCTION_BASE(DATAID);
        IMPL_AMHS_DATA_FUNCTION_BASE(DRACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(DVVALNAME);
        IMPL_AMHS_DATA_FUNCTION_BASE(EAC);
        IMPL_AMHS_DATA_FUNCTION_BASE(ERACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(HCACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(LRACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(OBJSPEC);
        IMPL_AMHS_DATA_FUNCTION_BASE(OFLACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(ONLACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(RCMD);
        IMPL_AMHS_DATA_FUNCTION_BASE(TIACK);
        IMPL_AMHS_DATA_FUNCTION_BASE(TIME);
        IMPL_AMHS_DATA_FUNCTION_BASE(UNITS);
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_DATA_MANAGER_H
