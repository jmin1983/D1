//
// D1AMHSVariable.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_VARIABLE_H
#define _D1SEM_AMHS_VARIABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2Data.h>
#include <B1GEM/B1GEMVariable.h>

namespace BnD {
    class D1AMHSDataManager;
    class D1AMHSVariable : public B1GEMVariable {
    protected:
        D1AMHSVariable(B1String&& label, const D1AMHSDataManager* dataManager);
    protected:
        const D1AMHSDataManager* _dataManager;
    public:
        const D1AMHSDataManager* dataManager() const { return _dataManager; }
        void setData(const B1SECS2DataVID& vID);
    };

    template <typename T, typename U>
    class D1AMHSVariableBase : public D1AMHSVariable {
    protected:
        D1AMHSVariableBase(B1String&& label, const D1AMHSDataManager* dataManager)
            : D1AMHSVariable(std::move(label), dataManager) {}
    private:
        T* createData(const U& data) const { auto t = new T(data); t->setLabel(_label.copy()); return t; }
    protected:
        std::shared_ptr<B1SECS2DataV> implGetValue(const B1GEMDataValueCondition& gemCondition) const final
        {
            U value;
            if (setValue(gemCondition, &value) != true) {
                return std::shared_ptr<B1SECS2DataV>();
            }
            return std::shared_ptr<B1SECS2DataV>(new B1SECS2DataV(SPB1SECS2Data(createData(value))));
        }
    protected:
        virtual bool setValue(const B1GEMDataValueCondition& gemCondition, U* value) const = 0;
    };

    class D1AMHSVariableLIST : public D1AMHSVariable {
    public:
        D1AMHSVariableLIST(B1String&& label, const D1AMHSDataManager* dataManager)
            : D1AMHSVariable(std::move(label), dataManager) {}
    protected:
        std::shared_ptr<B1SECS2DataV> implGetValue(const B1GEMDataValueCondition& gemCondition) const final;
    protected:
        virtual bool setValue(const B1GEMDataValueCondition& gemCondition, B1SECS2DataLIST* value, std::list<SPB1SECS2Data>* valueList) const = 0;
    protected:
        void addValueList(SPB1SECS2Data data, std::list<SPB1SECS2Data>* valueList) const;
        void addValueList(std::shared_ptr<B1SECS2DataV> v, std::list<SPB1SECS2Data>* valueList) const;
    };

    class D1AMHSVariableASCII : public D1AMHSVariableBase<B1SECS2DataASCII, B1String> {
    public:
        D1AMHSVariableASCII(B1String&& label, const D1AMHSDataManager* dataManager)
            : D1AMHSVariableBase<B1SECS2DataASCII, B1String>(std::move(label), dataManager) {}
    };
    class D1AMHSVariableUINT8 : public D1AMHSVariableBase<B1SECS2DataUINT8, uint8> {
    public:
        D1AMHSVariableUINT8(B1String&& label, const D1AMHSDataManager* dataManager)
            : D1AMHSVariableBase<B1SECS2DataUINT8, uint8>(std::move(label), dataManager) {}
    };
    class D1AMHSVariableUINT16 : public D1AMHSVariableBase<B1SECS2DataUINT16, uint16> {
    public:
        D1AMHSVariableUINT16(B1String&& label, const D1AMHSDataManager* dataManager)
            : D1AMHSVariableBase<B1SECS2DataUINT16, uint16>(std::move(label), dataManager) {}
    };
}   //  !BnD

#endif  // !_D1SEM_AMHS_VARIABLE_H
