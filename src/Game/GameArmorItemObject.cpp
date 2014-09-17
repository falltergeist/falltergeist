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
#include "../Game/GameArmorItemObject.h"
#include "../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

GameArmorItemObject::GameArmorItemObject() : GameItemObject()
{
    _subtype = TYPE_ITEM_ARMOR;
}

GameArmorItemObject::~GameArmorItemObject()
{
}

int GameArmorItemObject::damageResist(unsigned int type)
{
    if (type > DAMAGE_POISON) throw Exception("GameArmorItemObject::damageResist(type) - type out of range:" + std::to_string(type));
    return _damageResist.at(type);
}

void GameArmorItemObject::setDamageResist(unsigned int type, int value)
{
    if (type > DAMAGE_POISON) throw Exception("GameArmorItemObject::setDamageResist(type, value) - type out of range:" + std::to_string(type));
    _damageResist.at(type) = value;
}

int GameArmorItemObject::damageThreshold(unsigned int type)
{
    if ( type > DAMAGE_POISON) throw Exception("GameArmorItemObject::damageThreshold(type) - type out of range:" + std::to_string(type));
    return _damageThreshold.at(type);
}

void GameArmorItemObject::setDamageThreshold(unsigned int type, int value)
{
    if ( type > DAMAGE_POISON) throw Exception("GameArmorItemObject::setDamageThreshold(type, value) - type out of range:" + std::to_string(type));
    _damageThreshold.at(type) = value;
}

int GameArmorItemObject::perk()
{
    return _perk;
}

void GameArmorItemObject::setPerk(int value)
{
    _perk = value;
}

unsigned int GameArmorItemObject::maleFID()
{
    return _maleFID;
}

void GameArmorItemObject::setMaleFID(unsigned int value)
{
    _maleFID = value;
}

unsigned int GameArmorItemObject::femaleFID()
{
    return _femaleFID;
}

void GameArmorItemObject::setFemaleFID(unsigned int value)
{
    _femaleFID = value;
}

}
