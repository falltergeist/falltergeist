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

// Falltergeist includes
#include "../Game/GameCritterObject.h"
#include "../Engine/Exception.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/Animation.h"
#include "../VM/VM.h"

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
            value += 20 + 2*(statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_DOCTOR:
            value += 20 + 5 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_SNEAK:
            value += 20 + 5 + 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_LOCKPICK:
            value += 20 + 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_STEAL:
            value += 20 + 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_TRAPS:
            value += 20 + 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_SCIENCE:
            value += 20 + 4*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_REPAIR:
            value += 20 + 3*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_SPEECH:
            value += 20 + 5*statTotal(STATS_CHARISMA);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_BARTER:
            value += 20 + 4*statTotal(STATS_CHARISMA);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_GAMBLING:
            value += 20 + 5*statTotal(STATS_LUCK);
            break;
        case SKILLS_OUTDOORSMAN:
            value += 20 + 2*(statTotal(STATS_ENDURANCE) + statTotal(STATS_INTELLIGENCE));
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

int GameCritterObject::actionPointsMax()
{
    return _actionPointsMax;
}

void GameCritterObject::setActionPointsMax(int value)
{
    _actionPointsMax = value;
}

unsigned int GameCritterObject::carryWeight()
{
    unsigned int weight = 0;
    for (auto item : _inventory)
    {
        weight += item->weight();
    }

    if (auto armor = dynamic_cast<GameItemObject*>(armorSlot()))
    {
        weight += armor->weight();
    }

    if (auto leftHand = dynamic_cast<GameItemObject*>(leftHandSlot()))
    {
        weight += leftHand->weight();
    }

    if (auto rightHand = dynamic_cast<GameItemObject*>(rightHandSlot()))
    {
        weight += rightHand->weight();
    }

    return weight;
}

void GameCritterObject::setCarryWeightMax(unsigned int value)
{
    _carryWeightMax = value;
}

unsigned int GameCritterObject::carryWeightMax()
{
    return _carryWeightMax;
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

int GameCritterObject::damageResist(unsigned int type)
{
    if (type > DAMAGE_POISON) throw Exception("GameCritterObject::damageResist(type) - type out of range: " + std::to_string(type));
    return _damageResist.at(type);
}

void GameCritterObject::setDamageResist(unsigned int type, int value)
{
    if (type > DAMAGE_POISON) throw Exception("GameCritterObject::setDamageResist(type, value) - type out of range: " + std::to_string(type));
    _damageResist.at(type) = value;
}

int GameCritterObject::damageThreshold(unsigned int type)
{
    if ( type > DAMAGE_POISON) throw Exception("GameCritterObject::damageThreshold(type) - type out of range: " + std::to_string(type));
    return _damageThreshold.at(type);
}

void GameCritterObject::setDamageThreshold(unsigned int type, int value)
{
    if ( type > DAMAGE_POISON) throw Exception("GameCritterObject::setDamageThreshold(type, value) - type out of range: " + std::to_string(type));
    _damageThreshold.at(type) = value;
}

unsigned int GameCritterObject::currentHand()
{
    return _currentHand;
}

void GameCritterObject::setCurrentHand(unsigned int value)
{
    if (value > HAND_LEFT) throw Exception("GameCritterObject::setCurrentHand(value) - value out of range: " + std::to_string(value));
    _currentHand = value;
}

GameItemObject* GameCritterObject::currentHandSlot()
{
    return currentHand() == HAND_RIGHT ? rightHandSlot() : leftHandSlot();
}

void GameCritterObject::talk_p_proc()
{
    for(auto script : *scripts())
    {
        script->call("talk_p_proc");
    }
}

void GameCritterObject::damage_p_proc()
{
}

void GameCritterObject::combat_p_proc()
{
}

void GameCritterObject::critter_p_proc()
{
}

void GameCritterObject::is_dropping_p_proc()
{
}

void GameCritterObject::use_skill_on_p_proc()
{
}

}
