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

// Related headers
#include "../Game/ArmorItemObject.h"

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

ArmorItemObject::ArmorItemObject() : ItemObject()
{
    _subtype = TYPE_ITEM_ARMOR;
}

ArmorItemObject::~ArmorItemObject()
{
}

int ArmorItemObject::damageResist(DAMAGE type) const
{
    if (type > DAMAGE::POISON) throw Exception("ArmorItemObject::damageResist(type) - type out of range:" + std::to_string((unsigned)type));
    return _damageResist.at((unsigned)type);
}

void ArmorItemObject::setDamageResist(DAMAGE type, int value)
{
    if (type > DAMAGE::POISON) throw Exception("ArmorItemObject::setDamageResist(type, value) - type out of range:" + std::to_string((unsigned)type));
    _damageResist.at((unsigned)type) = value;
}

int ArmorItemObject::damageThreshold(DAMAGE type) const
{
    if ( type > DAMAGE::POISON) throw Exception("ArmorItemObject::damageThreshold(type) - type out of range:" + std::to_string((unsigned)type));
    return _damageThreshold.at((unsigned)type);
}

void ArmorItemObject::setDamageThreshold(DAMAGE type, int value)
{
    if ( type > DAMAGE::POISON) throw Exception("ArmorItemObject::setDamageThreshold(type, value) - type out of range:" + std::to_string((unsigned)type));
    _damageThreshold.at((unsigned)type) = value;
}

int ArmorItemObject::perk() const
{
    return _perk;
}

void ArmorItemObject::setPerk(int value)
{
    _perk = value;
}

unsigned int ArmorItemObject::maleFID() const
{
    return _maleFID;
}

void ArmorItemObject::setMaleFID(unsigned int value)
{
    _maleFID = value;
}

unsigned int ArmorItemObject::femaleFID() const
{
    return _femaleFID;
}

void ArmorItemObject::setFemaleFID(unsigned int value)
{
    _femaleFID = value;
}

unsigned int ArmorItemObject::armorClass() const
{
    return _armorClass;
}

void ArmorItemObject::setArmorClass(unsigned int value)
{
    _armorClass = value;
}

}
}
