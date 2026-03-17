//
// D1UnitRepository.h
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#ifndef _D1EQDATA_UNIT_REPOSITORY_H
#define _D1EQDATA_UNIT_REPOSITORY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <D1EQData/D1Unit.h>

#include <map>
#include <list>

namespace BnD {
    class D1UnitRepository {
    public:
        D1UnitRepository() {}
        virtual ~D1UnitRepository() {}
    protected:
        std::map<int32, SPD1Unit> _units;   //  map<map<unit_id, unit>
    protected:
        virtual bool implInitialize() { return true; }
        virtual void implFinalize() {}
    public:
        bool initialize(std::map<int32, SPD1Unit>&& units); //  map<unit_id, unit>
        bool initialize(const std::list<SPD1Unit>& units);
        void finalize();
        bool isValid() const;
        SPD1Unit findUnit(int32 unitID) const;
        const std::map<int32, SPD1Unit >& allUnits() const { return _units; }
    };
}

#endif  // !_D1EQDATA_UNIT_REPOSITORY_H
