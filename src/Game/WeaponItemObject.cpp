/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// Falltergeist includes
#include "WeaponItemObject.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameWeaponItemObject::GameWeaponItemObject() : GameItemObject()
{
    _subtype = TYPE_ITEM_WEAPON;
}

GameWeaponItemObject::~GameWeaponItemObject()
{
}

unsigned int GameWeaponItemObject::animationCode() const
{
    return _animationCode;
}

void GameWeaponItemObject::setAnimationCode(unsigned int value)
{
    _animationCode = value;
}

unsigned int GameWeaponItemObject::damageMin() const
{
    return _damageMin;
}

void GameWeaponItemObject::setDamageMin(unsigned int value)
{
    _damageMin = value;
}

unsigned int GameWeaponItemObject::damageMax() const
{
    return _damageMax;
}

void GameWeaponItemObject::setDamageMax(unsigned int value)
{
    _damageMax = value;
}

unsigned int GameWeaponItemObject::damageType() const
{
    return _damageType;
}

void GameWeaponItemObject::setDamageType(unsigned int value)
{
    _damageType = value;
}

unsigned int GameWeaponItemObject::rangePrimary() const
{
    return _rangePrimary;
}

void GameWeaponItemObject::setRangePrimary(unsigned int value)
{
    _rangePrimary = value;
}

unsigned int GameWeaponItemObject::rangeSecondary() const
{
    return _rangeSecondary;
}

void GameWeaponItemObject::setRangeSecondary(unsigned int value)
{
    _rangeSecondary = value;
}

unsigned int GameWeaponItemObject::minimumStrength() const
{
    return _minimumStrength;
}

void GameWeaponItemObject::setMinimumStrength(unsigned int value)
{
    _minimumStrength = value;
}

unsigned int GameWeaponItemObject::actionCostPrimary() const
{
    return _actionCostPrimary;
}

void GameWeaponItemObject::setActionCostPrimary(unsigned int value)
{
    _actionCostPrimary = value;
}

unsigned int GameWeaponItemObject::actionCostSecondary() const
{
    return _actionCostSecondary;
}

void GameWeaponItemObject::setActionCostSecondary(unsigned int value)
{
    _actionCostSecondary = value;
}

unsigned int GameWeaponItemObject::burstRounds() const
{
    return _burstRounds;
}

void GameWeaponItemObject::setBurstRounds(unsigned int value)
{
    _burstRounds = value;
}

unsigned int GameWeaponItemObject::ammoType() const
{
    return _ammoType;
}

void GameWeaponItemObject::setAmmoType(unsigned int value)
{
    _ammoType = value;
}

unsigned int GameWeaponItemObject::ammoPID() const
{
    return _ammoPID;
}

void GameWeaponItemObject::setAmmoPID(unsigned int value)
{
    _ammoPID = value;
}

unsigned int GameWeaponItemObject::ammoCapacity() const
{
    return _ammoCapacity;
}

void GameWeaponItemObject::setAmmoCapacity(unsigned int value)
{
    _ammoCapacity = value;
}

int GameWeaponItemObject::perk() const
{
    return _perk;
}

void GameWeaponItemObject::setPerk(int value)
{
    _perk = value;
}

}
}
