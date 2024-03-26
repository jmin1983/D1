//
// D1AMHSStatusVariable.h
//
// Library: D1SEM
// Package: AMHS
// Module:  D1SEM
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1SEM_AMHS_STATUS_VARIABLE_H
#define _D1SEM_AMHS_STATUS_VARIABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <B1SECS2/B1SECS2Data.h>
#include <B1GEM/B1GEMStatusVariable.h>

namespace BnD {
    class D1AMHSDataManager;
    class D1AMHSStatusVariable : public B1GEMStatusVariable {
    protected:
        D1AMHSStatusVariable(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager);
    protected:
        const int32 _hostID;
        const D1AMHSDataManager* _dataManager;
    public:
        int32 hostID() const { return _hostID; }
        const D1AMHSDataManager* dataManager() const { return _dataManager; }
        void setData(const B1SECS2DataSVID& svID, const B1SECS2DataSVNAME& svNAME, const B1SECS2DataUNITS& units);
    };

    template <typename T, typename U>
    class D1AMHSStatusVariableBase : public D1AMHSStatusVariable {
    protected:
        D1AMHSStatusVariableBase(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
            : D1AMHSStatusVariable(std::move(label), hostID, dataManager) {}
    private:
        T* createData(const U& data) const { auto t = new T(data); t->setLabel(_label.copy()); return t; }
    protected:
        B1SECS2DataSV implGetValue() const final { return B1SECS2DataSV(SPB1SECS2Data(createData(value()))); }
    protected:
        virtual U value() const = 0;
    };

    class D1AMHSStatusVariableLIST : public D1AMHSStatusVariable {
    public:
        D1AMHSStatusVariableLIST(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
            : D1AMHSStatusVariable(std::move(label), hostID, dataManager) {}
    protected:
        B1SECS2DataSV implGetValue() const final;
    protected:
        virtual void setValue(B1SECS2DataLIST* value, std::list<SPB1SECS2Data>* valueList) const = 0;
    protected:
        void addValueList(SPB1SECS2Data data, std::list<SPB1SECS2Data>* valueList) const;
        void addValueList(B1SECS2DataSV sv, std::list<SPB1SECS2Data>* valueList) const;
        void addValueList(std::shared_ptr<B1SECS2DataV> v, std::list<SPB1SECS2Data>* valueList) const;
    };

    class D1AMHSStatusVariableASCII : public D1AMHSStatusVariableBase<B1SECS2DataASCII, B1String> {
    public:
        D1AMHSStatusVariableASCII(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
            : D1AMHSStatusVariableBase<B1SECS2DataASCII, B1String>(std::move(label), hostID, dataManager) {}
    };
    class D1AMHSStatusVariableUINT8 : public D1AMHSStatusVariableBase<B1SECS2DataUINT8, uint8> {
    public:
        D1AMHSStatusVariableUINT8(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
            : D1AMHSStatusVariableBase<B1SECS2DataUINT8, uint8>(std::move(label), hostID, dataManager) {}
    };
    class D1AMHSStatusVariableUINT16 : public D1AMHSStatusVariableBase<B1SECS2DataUINT16, uint16> {
    public:
        D1AMHSStatusVariableUINT16(B1String&& label, int32 hostID, const D1AMHSDataManager* dataManager)
            : D1AMHSStatusVariableBase<B1SECS2DataUINT16, uint16>(std::move(label), hostID, dataManager) {}
    };

    typedef std::shared_ptr<D1AMHSStatusVariable> SPD1AMHSStatusVariable;
}   //  !BnD

#endif  // !_D1SEM_AMHS_STATUS_VARIABLE_H
