//
// D1AMHSStatusVariable.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSStatusVariable.h"

using namespace BnD;

D1AMHSStatusVariable::D1AMHSStatusVariable(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
    : B1GEMStatusVariable(std::move(label))
    , _hostID(hostID)
    , _dataManager(dataManager)
{
}

void D1AMHSStatusVariable::setData(const B1SECS2DataSVID& svID, const B1SECS2DataSVNAME& svNAME, const B1SECS2DataUNITS& units)
{
    _svID = std::make_shared<const B1SECS2DataSVID>(svID);
    _svName = std::make_shared<const B1SECS2DataSVNAME>(svNAME);
    _units = std::make_shared<const B1SECS2DataUNITS>(units);
}

B1SECS2DataSV D1AMHSStatusVariableLIST::implGetValue() const
{
    B1SECS2DataSV sv(SPB1SECS2Data(new B1SECS2DataLIST(label().copy())));
    setValue(static_cast<B1SECS2DataLIST*>(sv.get()), &sv._list);
    return sv;
}

void D1AMHSStatusVariableLIST::addValueList(SPB1SECS2Data data, std::list<SPB1SECS2Data>* valueList) const
{
    valueList->push_back(data);
}

void D1AMHSStatusVariableLIST::addValueList(B1SECS2DataSV sv, std::list<SPB1SECS2Data>* valueList) const
{
    valueList->push_back(sv.data());
    if (sv.data()->isFormatList()) {
        valueList->insert(valueList->end(), sv._list.begin(), sv._list.end());
    }
}

void D1AMHSStatusVariableLIST::addValueList(std::shared_ptr<B1SECS2DataV> v, std::list<SPB1SECS2Data>* valueList) const
{
    valueList->push_back(v->data());
    if (v->data()->isFormatList()) {
        valueList->insert(valueList->end(), v->_list.begin(), v->_list.end());
    }
}
