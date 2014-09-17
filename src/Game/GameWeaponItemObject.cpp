/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Game/GameWeaponItemObject.h"

// Third party includes

namespace Falltergeist
{

GameWeaponItemObject::GameWeaponItemObject() : GameItemObject()
{
    _subtype = TYPE_ITEM_WEAPON;
}

GameWeaponItemObject::~GameWeaponItemObject()
{
}

unsigned int GameWeaponItemObject::animationCode()
{
    return _animationCode;
}

void GameWeaponItemObject::setAnimationCode(unsigned int value)
{
    _animationCode = value;
}

unsigned int GameWeaponItemObject::damageMin()
{
    return _damageMin;
}

void GameWeaponItemObject::setDamageMin(unsigned int value)
{
    _damageMin = value;
}

unsigned int GameWeaponItemObject::damageMax()
{
    return _damageMax;
}

void GameWeaponItemObject::setDamageMax(unsigned int value)
{
    _damageMax = value;
}

unsigned int GameWeaponItemObject::damageType()
{
    return _damageType;
}

void GameWeaponItemObject::setDamageType(unsigned int value)
{
    _damageType = value;
}

unsigned int GameWeaponItemObject::rangePrimary()
{
    return _rangePrimary;
}

void GameWeaponItemObject::setRangePrimary(unsigned int value)
{
    _rangePrimary = value;
}

unsigned int GameWeaponItemObject::rangeSecondary()
{
    return _rangeSecondary;
}

void GameWeaponItemObject::setRangeSecondary(unsigned int value)
{
    _rangeSecondary = value;
}

\
unsigned int GameWeaponItemObject::minimumStrenght()
{
    return _minimumStrenght;
}

void GameWeaponItemObject::setMinimumStrenght(unsigned int value)
{
    _minimumStrenght = value;
}

unsigned int GameWeaponItemObject::actionCostPrimary()
{
    return _actionCostPrimary;
}

void GameWeaponItemObject::setActionCostPrimary(unsigned int value)
{
    _actionCostPrimary = value;
}

unsigned int GameWeaponItemObject::actionCostSecondary()
{
    return _actionCostSecondary;
}

void GameWeaponItemObject::setActionCostSecondary(unsigned int value)
{
    _actionCostSecondary = value;
}

unsigned int GameWeaponItemObject::burstRounds()
{
    return _burstRounds;
}

void GameWeaponItemObject::setBurstRounds(unsigned int value)
{
    _burstRounds = value;
}

unsigned int GameWeaponItemObject::ammoType()
{
    return _ammoType;
}

void GameWeaponItemObject::setAmmoType(unsigned int value)
{
    _ammoType = value;
}

unsigned int GameWeaponItemObject::ammoPID()
{
    return _ammoPID;
}

void GameWeaponItemObject::setAmmoPID(unsigned int value)
{
    _ammoPID = value;
}

unsigned int GameWeaponItemObject::ammoCapacity()
{
    return _ammoCapacity;
}

void GameWeaponItemObject::setAmmoCapacity(unsigned int value)
{
    _ammoCapacity = value;
}

int GameWeaponItemObject::perk()
{
    return _perk;
}

void GameWeaponItemObject::setPerk(int value)
{
    _perk = value;
}


}
