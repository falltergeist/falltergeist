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
 */

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Engine/Player.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{
    
Player::Player()
{
}

Player::Player(libfalltergeist::GcdFileType* gcd)
{
    for (unsigned int i = STATS_STRENGTH; i <= STATS_LUCK; i++)
    {
        setStat(i, gcd->stat(i));
        //setStatBonus(i, gcd->statBonus(i));
    }

    this->setCharacterPoints( gcd->characterPoints());
    this->setName(            gcd->name());
    this->setAge(             gcd->age());

    this->setHitPoints(       gcd->hitPoints() + gcd->hitPointsBonus());

    if (gcd->firstTrait() >= 0) this->setTrait(gcd->firstTrait(), 1);
    if (gcd->secondTrait() >= 0) this->setTrait(gcd->secondTrait(), 1);

    if (gcd->firstTaggedSkill() >= 0)
    {
        this->setSkill(gcd->firstTaggedSkill(), 1);
        _skillPoints--;
    }
    if (gcd->secondTaggedSkill() >= 0)
    {
        this->setSkill(gcd->secondTaggedSkill(), 1);
        _skillPoints--;
    }
    if (gcd->thirdTaggedSkill() >= 0)
    {
        this->setSkill(gcd->thirdTaggedSkill(), 1);
        _skillPoints--;
    }
    if (gcd->fourthTaggedSkill() >= 0)
    {
        this->setSkill(gcd->fourthTaggedSkill(), 1);
        if (_skillPoints > 0) _skillPoints--;
    }

    this->setGender(gcd->gender());
}

Player::~Player()
{
}

std::string Player::bio()
{
    return _bio;
}

void Player::setBio(std::string text)
{
    _bio = text;
}

std::string Player::name()
{
    return _name;
}

void Player::setName(std::string name)
{
    _name = name;
}

unsigned int Player::statTotal(unsigned int number)
{
    return stat(number) + statBonus(number);
}

void Player::setStat(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("Player::setStat() - number out of range: " + std::to_string(number));
    _stats.at(number) = value;
}

void Player::setStatBonus(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("Player::setStatBonus() - number out of range: " + std::to_string(number));
    _statsBonus.at(number) = value;
}

bool Player::statsIncrease(unsigned char stat)
{
    if (_characterPoints <= 0) return false;

    if (this->stat(stat) + this->statBonus(stat) >= 10) return false;

    this->setStat(stat, this->stat(stat) + 1);
    _characterPoints--;
    return true;
}

bool Player::statsDecrease(unsigned char stat)
{
    if (this->stat(stat) <= 1 + this->statBonus(stat)) return false;

     this->setStat(stat, this->stat(stat) - 1);
    _characterPoints++;
    return true;
}

unsigned int Player::characterPoints()
{
    return _characterPoints;
}

void Player::setCharacterPoints(unsigned int characterPoints)
{
    _characterPoints = characterPoints;
}

unsigned int Player::trait(unsigned int number)
{
    if (number > 15) throw Exception("Player::trait() - number out of range: " + std::to_string((int)number));
    return _traits.at(number);
}

void Player::setTrait(unsigned int number, unsigned int value)
{
    if (number > 15) throw Exception("Player::setTrait() - number out of range: " + std::to_string((int)number));
    _traits.at(number) = value;
}

bool Player::traitToggle(unsigned int number)
{
    if (trait(number))
    {
        setTrait(number, 0);
        return true;
    }
    else
    {
        unsigned int selectedTraits = 0;
        for (unsigned int i = 0; i != 16; ++i) if (trait(i)) selectedTraits++;
        if (selectedTraits < 2)
        {
            setTrait(number, 1);
            return true;
        }
    }
    return false;
}

unsigned int Player::skill(unsigned int number)
{
    if (number > 17) throw Exception("Player::skill() - number out of range: " + std::to_string(number));
    return _skills.at(number);
}

void Player::setSkill(int number, unsigned int value)
{
    if (number > 17) throw Exception("Player::setSkill() - number out of range: " + std::to_string(number));
    _skills.at(number) = value;
}

int Player::skillValue(unsigned int skillNumber)
{
    int value = 0;

    switch(skillNumber)
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

    if (skill(skillNumber))
    {
        value += 20;
    }

    return value;
}

bool Player::skillToggle(unsigned int skillNumber)
{
    if (skill(skillNumber))
    {
        setSkill(skillNumber, 0);
        _skillPoints++;
        return true;
    }
    else
    {
        if (_skillPoints > 0)
        {
            setSkill(skillNumber, 1);
            _skillPoints--;
            return true;
        }
    }
    return false;
}

unsigned int Player::skillPoints()
{
    return _skillPoints;
}

void Player::setSkillPoints(unsigned int skillPoints)
{
    _skillPoints = skillPoints;
}

char Player::gender()
{
    return _gender;
}

void Player::setGender(char gender)
{
    _gender = gender;
}

void Player::setAge(unsigned char age)
{
    _age = age;
}

unsigned char Player::age()
{
    return _age;
}

int Player::hitPoints()
{
    return _hitPoints;
}

void Player::setHitPoints(int hitPoints)
{
    _hitPoints = hitPoints;
}

unsigned int Player::hitPointsMaximum()
{
    unsigned int value = 15;
    value += statTotal(STATS_ENDURANCE) * 2;
    value += statTotal(STATS_STRENGTH);
    value += (2 + ceil(statTotal(STATS_ENDURANCE)/2))*(level() - 1);
    return value;
}

unsigned int Player::level()
{
    return _level;
}

void Player::setLevel(unsigned int level)
{
    _level = level;
}

unsigned int Player::experience()
{
    return _experience;
}

void Player::setExperience(unsigned int experience)
{
    _experience = experience;
}

unsigned int Player::armorClass()
{
    unsigned int value = 0;
    if (!trait(TRAITS_KAMIKAZE))
    {
        value += statTotal(STATS_AGILITY) > 10 ? 10 : statTotal(STATS_AGILITY);
    }
    return value;
}

unsigned int Player::actionPoints()
{
    unsigned int value = 0;
    value += 5 + ceil(statTotal(STATS_AGILITY)/2);
    if (trait(TRAITS_BRUISER))
    {
        value -= 2;
    }
    return value;
}

unsigned int Player::carryWeight()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);

    if (trait(TRAITS_SMALL_FRAME))
    {
        value += 25 + 15*(st > 10 ? 10 : st);
        if (trait(TRAITS_GIFTED) && st <= 10)
        {
            value += 10;
        }
    }
    else
    {
        value += 25 + 25*(st > 10 ? 10 : st);
    }
    return value;
}

unsigned int Player::stat(unsigned int number)
{
    if (number > 7) throw Exception("Player::stat() - number out of range" + std::to_string(number));
    return _stats.at(number);
}

unsigned int Player::statBonus(unsigned int number)
{
    if (number > 7) throw Exception("Player::stat() - number out of range" + std::to_string(number));
    unsigned int bonus = 0;
    switch (number)
    {
        case STATS_STRENGTH:
            if (trait(TRAITS_GIFTED))  bonus += 1;
            if (trait(TRAITS_BRUISER)) bonus += 2;
            break;
        case STATS_PERCEPTION:
            if (trait(TRAITS_GIFTED))  bonus += 1;
            break;
        case STATS_ENDURANCE:
            if (trait(TRAITS_GIFTED))  bonus += 1;
            break;
        case STATS_CHARISMA:
            if (trait(TRAITS_GIFTED)) bonus += 1;
            break;
        case STATS_INTELLIGENCE:
            if (trait(TRAITS_GIFTED)) bonus += 1;
            break;
        case STATS_AGILITY:
            if (trait(TRAITS_SMALL_FRAME)) bonus += 1;
            if (trait(TRAITS_GIFTED)) bonus += 1;
            break;
        case STATS_LUCK:
            if (this->trait(TRAITS_GIFTED)) bonus += 1;
            break;
    }
    return _statsBonus.at(number) + bonus;
}

unsigned int Player::meleeDamage()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);
    if (st > 10) st = 10;
    value += st > 5 ? st - 5 : 1;
    if (trait(TRAITS_HEAVY_HANDED))
    {
        value += 4;
    }
    return value;
}

unsigned int Player::damageResistance()
{
    unsigned int resistance = 0;

    return resistance;
}

unsigned int Player::poisonResistance()
{
    unsigned int value = 0;
    if (!trait(TRAITS_FAST_METABOLISM))
    {
        value += 5*statTotal(STATS_ENDURANCE);
    }
    return value;
}

unsigned int Player::radiationResistance()
{
    unsigned int value = 0;
    if (!trait(TRAITS_FAST_METABOLISM))
    {
        value += 2*statTotal(STATS_ENDURANCE);
    }
    return value;
}

unsigned int Player::sequence()
{
    unsigned int value = 0;
    unsigned int pe = statTotal(STATS_PERCEPTION);
    value += 2*(pe > 10 ? 10 : pe);
    if (trait(TRAITS_KAMIKAZE))
    {
        value += 5;
    }
    return value;
}

unsigned int Player::healingRate()
{
    unsigned int value = 0;
    unsigned int en = statTotal(STATS_ENDURANCE);
    value += ceil((en > 10 ? 10 : en) / 3);
    if (value == 0) value = 1;

    if (trait(TRAITS_FAST_METABOLISM))
    {
        value += 2;
    }
    return value;
}

unsigned int Player::criticalChance()
{
    unsigned int value = 0;
    unsigned int lk = statTotal(STATS_LUCK);
    value += lk > 10 ? 10 : lk;
    if (trait(TRAITS_FINESSE))
    {
        value += 10;
    }
    return value;
}

}

