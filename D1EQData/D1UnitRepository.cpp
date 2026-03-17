//
// D1UnitRepository.cpp
//
// Library: D1EQData
// Package: Unit
// Module:  D1EQData
//
// Written by jmin1983@gmail.com
// Feel free to use, for any purpose.
//

#include "D1EQData.h"
#include "D1UnitRepository.h"

using namespace BnD;

bool D1UnitRepository::initialize(std::map<int32, SPD1Unit>&& units)
{
    if (_units.empty() != true) {
        return false;
    }
    _units.swap(units);
    return implInitialize();
}

bool D1UnitRepository::initialize(const std::list<SPD1Unit>& units)
{
    if (_units.empty() != true) {
        return false;
    }
    for (const auto& unit : units) {
        _units.emplace(unit->unitID(), unit);
    }
    return implInitialize();
}

void D1UnitRepository::finalize()
{
    implFinalize();
    _units.clear();
}

bool D1UnitRepository::isValid() const
{
    return _units.empty() != true;
}

SPD1Unit D1UnitRepository::findUnit(int32 unitID) const
{
    auto itr = _units.find(unitID);
    return itr != _units.end() ? itr->second : SPD1Unit();
}
