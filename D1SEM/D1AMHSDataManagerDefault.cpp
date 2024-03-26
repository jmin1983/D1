//
// D1AMHSDataManagerDefault.cpp
//
// Library: D1SEM
// Package: AMHSDefault
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSDataManagerDefault.h"

using namespace BnD;
using namespace D1AMHSDataDictionaryDefault;

B1SECS2DataSVID D1AMHSDataManagerDefault::implMakeSVIDProcessState() const
{
    auto svID = getNewSVID();
    svID->setData(static_cast<uint32>(DEFAULT_VID::PROCESS_STATE));
    return B1SECS2DataSVID(svID);
}

bool D1AMHSDataManagerDefault::implIsSVIDProcessStatePaused(const B1SECS2DataSV& sv) const
{
    //  PROCESS_STATE.
    if (sv._list.size() != 1) {
        return false;
    }
    auto value = sv._list.front();
    if (value->isFormatUint16() != true) {
        return false;
    }
    return static_cast<B1SECS2DataUINT16*>(value.get())->data() == 2;
}
