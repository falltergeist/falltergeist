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

int GameCritterObject::statTotal(unsigned int num)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::statTotal(num) - num out of range:" + std::to_string(num));
    return stat(num) + statBonus(num);
}

int GameCritterObject::statBonus(unsigned int num)
{
    if (num >= _statsBonus.size()) throw Exception("GameCritterObject::statBonus(num) - num out of range:" + std::to_string(num));
    int bonus = 0;
    if (trait(TRAITS_GIFTED)) bonus += 1;
    switch (num)
    {
        case STATS_STRENGTH:
            if (trait(TRAITS_BRUISER)) bonus += 2;
            break;
        case STATS_AGILITY:
            if (trait(TRAITS_SMALL_FRAME)) bonus += 1;
            break;
    }
    return _statsBonus.at(num) + bonus;
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

int GameCritterObject::skillValue(unsigned int num)
{
    if (num >= _skills.size()) throw Exception("GameCritterObject::skillValue(num) - num out of range:" + std::to_string(num));
    int value = 0;
    switch(num)
    {
        case SKILLS_SMALL_GUNS:
            value += 5 + 4 * statTotal(STATS_AGILITY);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_BIG_GUNS:
            value += 2*statTotal(STATS_AGILITY);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_ENERGY_WEAPONS:
            value += 2*statTotal(STATS_AGILITY);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_UNARMED:
            value += 30 + 2*(statTotal(STATS_AGILITY) + statTotal(STATS_STRENGTH));
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_MELEE_WEAPONS:
            value += 20 + 2*(statTotal(STATS_AGILITY) + statTotal(STATS_STRENGTH));
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_THROWING:
            value += 4*statTotal(STATS_AGILITY);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_FIRST_AID:
            value += 2*(statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_DOCTOR:
            value += 5 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_SNEAK:
            value += 5 + 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_LOCKPICK:
            value += 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_STEAL:
            value += 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_TRAPS:
            value += 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_SCIENCE:
            value += 4*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_REPAIR:
            value += 3*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_SPEECH:
            value += 5*statTotal(STATS_CHARISMA);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_BARTER:
            value += 4*statTotal(STATS_CHARISMA);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_GAMBLING:
            value += 5*statTotal(STATS_LUCK);
            break;
        case SKILLS_OUTDOORSMAN:
            value += 2 * (statTotal(STATS_ENDURANCE) + statTotal(STATS_INTELLIGENCE));
            break;
    }

    if (trait(TRAITS_GIFTED))
    {
        value -= 10;
    }

    if (skill(num))
    {
        value += 20;
    }

    return value;
}

int GameCritterObject::trait(unsigned int num)
{
    if (num >= _traits.size()) throw Exception("GameCritterObject::trait(num) - num out of range:" + std::to_string(num));
    return _traits.at(num);
}

void GameCritterObject::setTrait(unsigned int num, int value)
{
    if (num >= _traits.size()) throw Exception("GameCritterObject::setTrait(num, value) - num out of range:" + std::to_string(num));
    _traits.at(num) = value;
}

int GameCritterObject::hitPoints()
{
    return _hitPoints;
}

void GameCritterObject::setHitPoints(int value)
{
    _hitPoints = value;
}

int GameCritterObject::hitPointsMax()
{
    return _hitPointsMax;
}

void GameCritterObject::setHitPointsMax(int value)
{
    _hitPointsMax = value;
}

int GameCritterObject::armorClass()
{
    return _armorClass;
}

void GameCritterObject::setArmorClass(int value)
{
    _armorClass = value;
}

int GameCritterObject::actionPoints()
{
    return _actionPoints;
}

void GameCritterObject::setActionPoints(int value)
{
    _actionPoints = value;
}

int GameCritterObject::carryWeight()
{
    return _carryWeight;
}

void GameCritterObject::setCarryWeight(int value)
{
    _carryWeight = value;
}

int GameCritterObject::meleeDamage()
{
    return _meleeDamage;
}

void GameCritterObject::setMeleeDamage(int value)
{
    _meleeDamage = value;
}

int GameCritterObject::sequence()
{
    return _sequence;
}

void GameCritterObject::setSequence(int value)
{
    _sequence = value;
}

int GameCritterObject::criticalChance()
{
    return _criticalChance;
}

void GameCritterObject::setCriticalChance(int value)
{
    _criticalChance = value;
}

int GameCritterObject::healingRate()
{
    return _healingRate;
}

void GameCritterObject::setHealingRate(int value)
{
    _healingRate = value;
}

}
