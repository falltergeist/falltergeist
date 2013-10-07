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

#include <string.h>

#include "../Engine/Player.h"
#include <iostream>
#include <cmath>

namespace Falltergeist
{
    
Player::Player()
{
    _characterPoints = 0;
    _skillPoints = 0;
    _bio = 0;    
    _name = 0;
    _hitPoints = 0;
    _gender = 0;
    _age = 0;
    _level = 1;
    _experience = 0;
    _stats = new unsigned int[7]();
    _statsBonus = new unsigned int[7]();
    _traits = new unsigned int[16]();
    _skills = new unsigned int[18]();
}

Player::Player(libfalltergeist::GcdFileType * gcd)
{
    _characterPoints = 0;
    _skillPoints = 3;
    _bio = 0;
    _name = 0;
    _hitPoints = 0;
    _gender = 0;
    _level = 1;
    _experience = 0;
    _stats = new unsigned int[7]();
    _statsBonus = new unsigned int[7]();
    _traits = new unsigned int[16]();
    _skills = new unsigned int[18]();

    this->setStrength(        gcd->strength());
    this->setStrengthBonus(   gcd->strengthBonus());

    this->setPerception(      gcd->perception());
    this->setPerceptionBonus( gcd->perceptionBonus());

    this->setEndurance(       gcd->endurance());
    this->setEnduranceBonus(  gcd->enduranceBonus());

    this->setCharisma(        gcd->charisma());
    this->setCharismaBonus(   gcd->charismaBonus());

    this->setIntelligence(    gcd->intelligence());
    this->setIntelligenceBonus(gcd->intelligenceBonus());

    this->setAgility(         gcd->agility());
    this->setAgilityBonus(    gcd->agilityBonus());

    this->setLuck(            gcd->luck());
    this->setLuckBonus(       gcd->luckBonus());

    this->setCharacterPoints( gcd->characterPoints());
    this->setName(            gcd->name());
    this->setAge(             gcd->age());

    this->setHitPoints(       gcd->hitPoints() + gcd->hitPointsBonus());

    this->setTrait(gcd->firstTrait(), 1);
    this->setTrait(gcd->secondTrait(), 1);

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
    delete [] _bio;
    delete [] _name;
    delete [] _stats;
    delete [] _traits;
    delete [] _skills;
}

const char * Player::bio()
{
    return _bio;
}

void Player::setBio(const char * text)
{
    delete _bio;
    _bio = new char[strlen(text)+1]();
    strcpy(_bio,text);
}

const char * Player::name()
{
    return _name;
}

void Player::setName(const char * name)
{
    delete _name;
    _name = new char[strlen(name)+1]();
    strcpy(_name,name);    
}

bool Player::statsIncrease(unsigned char stat)
{
    if (_characterPoints <= 0) return false;

    if (this->stat(stat) + this->statBonus(stat) >= 10) return false;

    _stats[stat]++;
    _characterPoints--;
    return true;
}

bool Player::statsDecrease(unsigned char stat)
{
    if (_stats[stat] <= 1 + _statsBonus[stat]) return false;

    _stats[stat]--;
    _characterPoints++;
    return true;
}

unsigned int Player::strength()
{
    return _stats[STATS_STRENGTH];
}

void Player::setStrength(unsigned int strength)
{
    _stats[STATS_STRENGTH] = strength;
}

unsigned int Player::strengthBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    if (this->trait(TRAITS_BRUISER)) bonus += 2;
    return _statsBonus[STATS_STRENGTH] + bonus;
}

void Player::setStrengthBonus(unsigned int bonus)
{
    _statsBonus[STATS_STRENGTH] = bonus;
}

unsigned int Player::perception()
{
    return _stats[STATS_PERCEPTION];
}

void Player::setPerception(unsigned int perception)
{
    _stats[STATS_PERCEPTION] = perception;
}

unsigned int Player::perceptionBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_PERCEPTION] + bonus;
}

void Player::setPerceptionBonus(unsigned int bonus)
{
    _statsBonus[STATS_PERCEPTION] = bonus;
}

unsigned int Player::endurance()
{
    return _stats[STATS_ENDURANCE];
}

void Player::setEndurance(unsigned int endurance)
{
    _stats[STATS_ENDURANCE] = endurance;
}

unsigned int Player::enduranceBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_ENDURANCE] + bonus;
}

void Player::setEnduranceBonus(unsigned int bonus)
{
    _statsBonus[STATS_ENDURANCE] = bonus;
}

unsigned int Player::charisma()
{
    return _stats[STATS_CHARISMA];
}

void Player::setCharisma(unsigned int charisma)
{
    _stats[STATS_CHARISMA] = charisma;
}

unsigned int Player::charismaBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_CHARISMA] + bonus;
}

void Player::setCharismaBonus(unsigned int bonus)
{
    _statsBonus[STATS_CHARISMA] = bonus;
}

unsigned int Player::intelligence()
{
    return _stats[STATS_INTELLIGENCE];
}

void Player::setIntelligence(unsigned int intelligence)
{
    _stats[STATS_INTELLIGENCE] = intelligence;
}

unsigned int Player::intelligenceBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_INTELLIGENCE] + bonus;
}

void Player::setIntelligenceBonus(unsigned int bonus)
{
    _statsBonus[STATS_INTELLIGENCE] = bonus;
}

unsigned int Player::agility()
{
    return _stats[STATS_AGILITY];
}

void Player::setAgility(unsigned int agility)
{
    _stats[STATS_AGILITY] = agility;
}

unsigned int Player::agilityBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_SMALL_FRAME)) bonus += 1;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_AGILITY] + bonus;
}

void Player::setAgilityBonus(unsigned int bonus)
{
    _statsBonus[STATS_AGILITY] = bonus;
}

unsigned int Player::luck()
{
    return _stats[STATS_LUCK];
}

void Player::setLuck(unsigned int luck)
{
    _stats[STATS_LUCK] = luck;
}

unsigned int Player::luckBonus()
{
    unsigned int bonus = 0;
    if (this->trait(TRAITS_GIFTED)) bonus += 1;
    return _statsBonus[STATS_LUCK] + bonus;
}

void Player::setLuckBonus(unsigned int bonus)
{
    _statsBonus[STATS_LUCK] = bonus;
}

unsigned int Player::characterPoints()
{
    return _characterPoints;
}

void Player::setCharacterPoints(unsigned int characterPoints)
{
    _characterPoints = characterPoints;
}

unsigned int Player::trait(unsigned int traitNumber)
{
    return _traits[traitNumber];
}

void Player::setTrait(unsigned int traitNumber, unsigned int value)
{
    _traits[traitNumber] = value;
}

bool Player::traitToggle(unsigned int traitNumber)
{
    if (trait(traitNumber))
    {
        setTrait(traitNumber, 0);
        return true;
    }
    else
    {
        unsigned int selectedTraits = 0;
        for (unsigned int i = 0; i != 16; ++i) if (trait(i)) selectedTraits++;
        if (selectedTraits < 2)
        {
            setTrait(traitNumber, 1);
            return true;
        }
    }
    return false;
}

unsigned int Player::skill(unsigned int skillNumber)
{
    return _skills[skillNumber];
}

void Player::setSkill(unsigned int skillNumber, unsigned int value)
{
    _skills[skillNumber] = value;
}

int Player::skillValue(unsigned int skillNumber)
{
    int value = 0;
    unsigned int st = strength() + strengthBonus();
    unsigned int pe = perception() + perceptionBonus();
    unsigned int en = endurance() + enduranceBonus();
    unsigned int ch = charisma() + charismaBonus();
    unsigned int in = intelligence() + intelligenceBonus();
    unsigned int ag = agility() + agilityBonus();
    unsigned int lk = luck() + luckBonus();
    switch(skillNumber)
    {
        case SKILLS_SMALL_GUNS:
            value += 5 + 4 * ag;
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_BIG_GUNS:
            value += 2*ag;
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_ENERGY_WEAPONS:
            value += 2*ag;
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_UNARMED:
            value += 30 + 2*(ag + st);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_MELEE_WEAPONS:
            value += 20 + 2*(ag + st);
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_THROWING:
            value += 4*ag;
            if (trait(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_FIRST_AID:
            value += 2*(pe + in);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_DOCTOR:
            value += 5 + (pe + in);
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_SNEAK:
            value += 5 + 3*ag;
            break;
        case SKILLS_LOCKPICK:
            value += 10 + (pe + ag);
            break;
        case SKILLS_STEAL:
            value += 3*ag;
            break;
        case SKILLS_TRAPS:
            value += 10 + (pe + ag);
            break;
        case SKILLS_SCIENCE:
            value += 4*in;
            break;
        case SKILLS_REPAIR:
            value += 3*in;
            break;
        case SKILLS_SPEECH:
            value += 5*ch;
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_BARTER:
            value += 4*ch;
            if (trait(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_GAMBLING:
            value += 5*lk;
            break;
        case SKILLS_OUTDOORSMAN:
            value += 2 * (en + in);
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
    unsigned int en = endurance() + enduranceBonus();
    unsigned int hitPoints = 15;
    hitPoints += en * 2;
    hitPoints += strength() + strengthBonus();
    hitPoints += (2 + ceil(en/2))*(level() - 1);
    return hitPoints;
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
    unsigned int armorClass = 0;
    unsigned int ag = agility() + agilityBonus();
    if (!trait(TRAITS_KAMIKAZE))
    {
        armorClass += ag > 10 ? 10 : ag;
    }
    return armorClass;
}

unsigned int Player::actionPoints()
{
    unsigned int actionPoints = 0;
    unsigned int ag = agility() + agilityBonus();
    actionPoints += 5 + ceil(ag/2);
    if (trait(TRAITS_BRUISER))
    {
        actionPoints -= 2;
    }
    return actionPoints;
}

unsigned int Player::carryWeight()
{
    unsigned int carryWeight = 0;
    unsigned int st = strength() + strengthBonus();

    if (trait(TRAITS_SMALL_FRAME))
    {
        carryWeight += 25 + 15*(st > 10 ? 10 : st);
        if (trait(TRAITS_GIFTED) && st <= 10)
        {
            carryWeight += 10;
        }
    }
    else
    {
        carryWeight += 25 + 25*(st > 10 ? 10 : st);
    }
    return carryWeight;
}

unsigned int Player::stat(unsigned int number)
{
    switch (number)
    {
        case STATS_STRENGTH: return strength();
        case STATS_PERCEPTION: return perception();
        case STATS_ENDURANCE: return endurance();
        case STATS_CHARISMA: return charisma();
        case STATS_INTELLIGENCE: return intelligence();
        case STATS_AGILITY: return agility();
        case STATS_LUCK: return luck();
    }
    return 0;
}

unsigned int Player::statBonus(unsigned int number)
{
    switch (number)
    {
        case STATS_STRENGTH: return strengthBonus();
        case STATS_PERCEPTION: return perceptionBonus();
        case STATS_ENDURANCE: return enduranceBonus();
        case STATS_CHARISMA: return charismaBonus();
        case STATS_INTELLIGENCE: return intelligenceBonus();
        case STATS_AGILITY: return agilityBonus();
        case STATS_LUCK: return luckBonus();
    }
    return 0;
}

unsigned int Player::meleeDamage()
{
    unsigned int meleeDamage = 0;
    unsigned int st = strength() + strengthBonus();
    if (st > 10) st = 10;
    meleeDamage += st > 5 ? st - 5 : 1;
    if (trait(TRAITS_HEAVY_HANDED))
    {
        meleeDamage += 4;
    }
    return meleeDamage;
}

unsigned int Player::damageResistance()
{
    unsigned int resistance = 0;

    return resistance;
}

unsigned int Player::poisonResistance()
{
    unsigned int resistance = 0;
    unsigned int en = endurance() + enduranceBonus();
    if (!trait(TRAITS_FAST_METABOLISM))
    {
        resistance += 5*en;
    }
    return resistance;
}

unsigned int Player::radiationResistance()
{
    unsigned int resistance = 0;
    unsigned int en = endurance() + enduranceBonus();
    if (!trait(TRAITS_FAST_METABOLISM))
    {
        resistance += 2*en;
    }
    return resistance;
}

unsigned int Player::sequence()
{
    unsigned int sequence = 0;
    unsigned int pe = perception() + perceptionBonus();
    sequence += 2*(pe > 10 ? 10 : pe);
    if (trait(TRAITS_KAMIKAZE))
    {
        sequence += 5;
    }
    return sequence;
}

unsigned int Player::healingRate()
{
    unsigned int rate = 0;
    unsigned int en = endurance() + enduranceBonus();
    rate += ceil((en > 10 ? 10 : en) / 3);
    if (rate == 0) rate = 1;

    if (trait(TRAITS_FAST_METABOLISM))
    {
        rate += 2;
    }
    return rate;
}

unsigned int Player::criticalChance()
{
    unsigned int chance = 0;
    unsigned int lk = luck() + luckBonus();
    chance += lk > 10 ? 10 : lk;
    if (trait(TRAITS_FINESSE))
    {
        chance += 10;
    }
    return chance;
}

}

