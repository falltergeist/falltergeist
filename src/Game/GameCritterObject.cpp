/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <string>
#include <iostream>

// Falltergeist includes
#include "../Game/GameCritterObject.h"
#include "../Engine/Exception.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Animation.h"

// Third party includes

namespace Falltergeist
{

GameCritterObject::GameCritterObject() : GameObject()
{
    _type = TYPE_CRITTER;
}

GameCritterObject::~GameCritterObject()
{
}

std::vector<GameItemObject*>* GameCritterObject::inventory()
{
    return &_inventory;
}

void GameCritterObject::setOrientation(int value)
{
    GameObject::setOrientation(value);

    unsigned int frmId = FID() & 0x00000FFF;
    unsigned int ID1 = (FID() & 0x0000F000) >> 12;
    unsigned int ID2 = (FID() & 0x00FF0000) >> 16;
    unsigned int ID3 = (FID() & 0xF0000000) >> 28;
    auto lst = ResourceManager::lstFileType("art/critters/critters.lst");
    std::string frmName = lst->strings()->at(frmId);
    std::string frmBase = frmName.substr(0, 6);

    if (ID2 >= 0x26 && ID2 <= 0x2F)
    {
        if (ID1 >= 0x0B || ID1 == 0) throw Exception("Critter ID1 unsupported value");
        frmBase += ID1 + 0x63;
        frmBase += ID2 + 0x3D;
    }
    else if (ID2 == 0x24)
    {
        frmBase += "ch";
    }
    else if (ID2 == 0x25)
    {
        frmBase += "cj";
    }
    else if (ID2 == 0x40)
    {
        frmBase += "na";
    }
    else if (ID2 >= 0x30)
    {
        frmBase += "r";
        frmBase += ID2 + 0x31;
    }
    else if (ID2 >= 0x14)
    {
        frmBase += "b";
        frmBase += ID2 + 0x4d;
    }
    else if (ID2 == 0x12)
    {
        if (ID1 == 0x01)
        {
            frmBase += "dm";
        }
        else if (ID1 == 0x04)
        {
            frmBase += "gm";
        }
        else
        {
            frmBase += "as";
        }
    }
    else if (ID2 == 0x0D)
    {
        if (ID1 > 0)
        {
            frmBase += ID1 + 0x63;
            frmBase += "e";
        }
        else
        {
            frmBase += "an";
        }
    }
    else if (ID2 <= 0x01 && ID1 > 0)
    {
        frmBase += ID1 + 0x63;
        frmBase += ID2 + 0x61;
    }
    else
    {
        frmBase += "a";
        frmBase += ID2 + 0x61;
    }

    std::string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
    frmBase += "." + extensions[ID3];

    auto frm = ResourceManager::frmFileType("art/critters/" + frmBase);
    animationQueue()->clear();

    auto animation = new Animation(frm);

    if (ID3 == 0)
    {
        animation->setCurrentSurfaceSet(this->orientation());
    }
    animationQueue()->add(animation);
}

GameArmorItemObject* GameCritterObject::armorSlot()
{
    return _armorSlot;
}

void GameCritterObject::setArmorSlot(GameArmorItemObject* object)
{
    _armorSlot = object;
}

GameItemObject* GameCritterObject::leftHandSlot()
{
    return _leftHandSlot;
}

void GameCritterObject::setLeftHandSlot(GameItemObject* object)
{
    _leftHandSlot = object;
}

GameItemObject* GameCritterObject::rightHandSlot()
{
    return _rightHandSlot;
}

void GameCritterObject::setRightHandSlot(GameItemObject* object)
{
    _rightHandSlot = object;
}

int GameCritterObject::gender()
{
    return _gender;
}

void GameCritterObject::setGender(unsigned int value)
{
    if (value > 1) throw Exception("GameCritterObject::setGender(value) - value out of range:" + std::to_string(value));
    _gender = value;
}

int GameCritterObject::stat(unsigned int num)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::stat(num) - num out of range:" + std::to_string(num));
    return _stats.at(num);
}

void GameCritterObject::setStat(unsigned int num, int value)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::setStat(num, value) - num out of range:" + std::to_string(num));
    _stats.at(num) = value;
}

int GameCritterObject::statBonus(unsigned int num)
{
    if (num >= _statsBonus.size()) throw Exception("GameCritterObject::statBonus(num) - num out of range:" + std::to_string(num));
    return _statsBonus.at(num);
}

void GameCritterObject::setStatBonus(unsigned int num, int value)
{
    if (num >= _statsBonus.size()) throw Exception("GameCritterObject::setStatBonus(num, value) - num out of range:" + std::to_string(num));
    _statsBonus.at(num) = value;
}

int GameCritterObject::skill(unsigned int num)
{
    if (num >= _skills.size()) throw Exception("GameCritterObject::skill(num) - num out of range:" + std::to_string(num));
    return _skills.at(num);
}

void GameCritterObject::setSkill(unsigned int num, int value)
{
    if (num >= _skills.size()) throw Exception("GameCritterObject::setSkill(num, value) - num out of range:" + std::to_string(num));
    _skills.at(num) = value;
}

}
