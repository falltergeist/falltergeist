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
#include "ArmorItemObject.h"
#include "../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameArmorItemObject::GameArmorItemObject() : GameItemObject()
{
    _subtype = TYPE_ITEM_ARMOR;
}

GameArmorItemObject::~GameArmorItemObject()
{
}

int GameArmorItemObject::damageResist(DAMAGE type) const
{
    if (type > DAMAGE::POISON) throw Exception("GameArmorItemObject::damageResist(type) - type out of range:" + std::to_string((unsigned)type));
    return _damageResist.at((unsigned)type);
}

void GameArmorItemObject::setDamageResist(DAMAGE type, int value)
{
    if (type > DAMAGE::POISON) throw Exception("GameArmorItemObject::setDamageResist(type, value) - type out of range:" + std::to_string((unsigned)type));
    _damageResist.at((unsigned)type) = value;
}

int GameArmorItemObject::damageThreshold(DAMAGE type) const
{
    if ( type > DAMAGE::POISON) throw Exception("GameArmorItemObject::damageThreshold(type) - type out of range:" + std::to_string((unsigned)type));
    return _damageThreshold.at((unsigned)type);
}

void GameArmorItemObject::setDamageThreshold(DAMAGE type, int value)
{
    if ( type > DAMAGE::POISON) throw Exception("GameArmorItemObject::setDamageThreshold(type, value) - type out of range:" + std::to_string((unsigned)type));
    _damageThreshold.at((unsigned)type) = value;
}

int GameArmorItemObject::perk() const
{
    return _perk;
}

void GameArmorItemObject::setPerk(int value)
{
    _perk = value;
}

unsigned int GameArmorItemObject::maleFID() const
{
    return _maleFID;
}

void GameArmorItemObject::setMaleFID(unsigned int value)
{
    _maleFID = value;
}

unsigned int GameArmorItemObject::femaleFID() const
{
    return _femaleFID;
}

void GameArmorItemObject::setFemaleFID(unsigned int value)
{
    _femaleFID = value;
}

unsigned int GameArmorItemObject::armorClass() const
{
    return _armorClass;
}

void GameArmorItemObject::setArmorClass(unsigned int value)
{
    _armorClass = value;
}

}
}
