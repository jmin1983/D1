//
// D1AMHSDataManager.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSDataManager.h"

using namespace BnD;

B1SECS2Data* D1AMHSDataManager::createOriginalData(B1SECS2DataBase::INDEX index) const
{
#define CREATE_AMHS_DATA(d) case B1SECS2DataBase::INDEX_##d: return new D1AMHSData##d()
#define CREATE_AMHS_SPECIFIC_DATA(d) case B1SECS2DataBase::INDEX_##d: return create##d()
    switch (index) {
        CREATE_AMHS_DATA(ACKC5);
        CREATE_AMHS_DATA(ACKC6);
        CREATE_AMHS_DATA(ALCD);
        CREATE_AMHS_DATA(ALED);
        CREATE_AMHS_DATA(CEED);
        CREATE_AMHS_DATA(CENAME);
        CREATE_AMHS_DATA(CEPACK);
        CREATE_AMHS_DATA(COMMACK);
        CREATE_AMHS_DATA(CPACK);
        CREATE_AMHS_DATA(CPNAME);
        CREATE_AMHS_DATA(DATAID);
        CREATE_AMHS_DATA(DRACK);
        CREATE_AMHS_DATA(DVVALNAME);
        CREATE_AMHS_DATA(EAC);
        CREATE_AMHS_DATA(ERACK);
        CREATE_AMHS_DATA(HCACK);
        CREATE_AMHS_DATA(LRACK);
        CREATE_AMHS_DATA(OBJSPEC);
        CREATE_AMHS_DATA(OFLACK);
        CREATE_AMHS_DATA(ONLACK);
        CREATE_AMHS_DATA(RCMD);
        CREATE_AMHS_DATA(TIACK);
        CREATE_AMHS_DATA(TIME);
        CREATE_AMHS_DATA(UNITS);

        CREATE_AMHS_SPECIFIC_DATA(ALID);
        CREATE_AMHS_SPECIFIC_DATA(ALTX);
        CREATE_AMHS_SPECIFIC_DATA(CEID);
        CREATE_AMHS_SPECIFIC_DATA(ECID);
        CREATE_AMHS_SPECIFIC_DATA(ECNAME);
        CREATE_AMHS_SPECIFIC_DATA(MDLN);
        CREATE_AMHS_SPECIFIC_DATA(RPTID);
        CREATE_AMHS_SPECIFIC_DATA(SOFTREV);
        CREATE_AMHS_SPECIFIC_DATA(SVID);
        CREATE_AMHS_SPECIFIC_DATA(SVNAME);
        CREATE_AMHS_SPECIFIC_DATA(VID);
        default:
            break;
    }
    return NULL;
}

B1SECS2DataSVID D1AMHSDataManager::makeSVIDProcessState() const
{
    return implMakeSVIDProcessState();
}

bool D1AMHSDataManager::isSVIDProcessStatePaused(const B1SECS2DataSV& sv) const
{
    return implIsSVIDProcessStatePaused(sv);
}
