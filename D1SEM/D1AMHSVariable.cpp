//
// D1AMHSVariable.cpp
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1SEM.h"
#include "D1AMHSVariable.h"

using namespace BnD;

D1AMHSVariable::D1AMHSVariable(B1String&& label, const D1AMHSDataManager* dataManager)
    : B1GEMVariable(std::move(label))
    , _dataManager(dataManager)
{
}

void D1AMHSVariable::setData(const B1SECS2DataVID& vID)
{
    _vID = std::make_shared<const B1SECS2DataVID>(vID);
}

std::shared_ptr<B1SECS2DataV> D1AMHSVariableLIST::implGetValue(const B1GEMDataValueCondition& gemCondition) const
{
    std::shared_ptr<B1SECS2DataV> v(new B1SECS2DataV(SPB1SECS2Data(new B1SECS2DataLIST(label().copy()))));
    if (setValue(gemCondition, static_cast<B1SECS2DataLIST*>(v->get()), &v->_list) != true) {
        return std::shared_ptr<B1SECS2DataV>();
    }
    return v;
}

void D1AMHSVariableLIST::addValueList(SPB1SECS2Data data, std::list<SPB1SECS2Data>* valueList) const
{
    valueList->push_back(data);
}

void D1AMHSVariableLIST::addValueList(std::shared_ptr<B1SECS2DataV> v, std::list<SPB1SECS2Data>* valueList) const
{
    valueList->push_back(v->data());
    if (v->data()->isFormatList()) {
        valueList->insert(valueList->end(), v->_list.begin(), v->_list.end());
    }
}
