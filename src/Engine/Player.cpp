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

namespace Falltergeist
{
    
Player::Player()
{
    _characterPoints = 0;
    _bio = 0;    
    _name = 0;
    _stats = new unsigned int[7]();
    _traits = new unsigned int[16]();
    _skills = new unsigned int[10](); // temporary
}

Player::Player(libfalltergeist::GcdFileType * gcd)
{
    _characterPoints = 0;
    _bio = 0;
    _name = 0;
    _stats = new unsigned int[7]();
    _traits = new unsigned int[16]();
    _skills = new unsigned int[10](); // temporary

    this->setStrength(        gcd->strength());
    this->setPerception(      gcd->perception());
    this->setEndurance(       gcd->endurance());
    this->setCharisma(        gcd->charisma());
    this->setIntelligence(    gcd->intelligence());
    this->setAgility(         gcd->agility());
    this->setLuck(            gcd->luck());
    this->setCharacterPoints( gcd->characterPoints());
    this->setName(            gcd->name());
    this->setTrait(gcd->firstTrait(), 1);
    this->setTrait(gcd->secondTrait(), 1);

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

void Player::statsIncrease(unsigned char stat)
{
    if (_characterPoints <= 0) return;

    if (_stats[stat] >= 10) return;

    _stats[stat]++;
    _characterPoints--;

}

void Player::statsDecrease(unsigned char stat)
{
    if (_stats[stat] <= 2) return;

    _stats[stat]--;
    _characterPoints++;
}

unsigned int Player::strength()
{
    return _stats[STATS_STRENGTH];
}

void Player::setStrength(unsigned int strength)
{
    _stats[STATS_STRENGTH] = strength;
}

unsigned int Player::perception()
{
    return _stats[STATS_PERCEPTION];
}

void Player::setPerception(unsigned int perception)
{
    _stats[STATS_PERCEPTION] = perception;
}

unsigned int Player::endurance()
{
    return _stats[STATS_ENDURANCE];
}

void Player::setEndurance(unsigned int endurance)
{
    _stats[STATS_ENDURANCE] = endurance;
}

unsigned int Player::charisma()
{
    return _stats[STATS_CHARISMA];
}

void Player::setCharisma(unsigned int charisma)
{
    _stats[STATS_CHARISMA] = charisma;
}

unsigned int Player::intelligence()
{
    return _stats[STATS_INTELLIGENCE];
}

void Player::setIntelligence(unsigned int intelligence)
{
    _stats[STATS_INTELLIGENCE] = intelligence;
}

unsigned int Player::agility()
{
    return _stats[STATS_AGILITY];
}

void Player::setAgility(unsigned int agility)
{
    _stats[STATS_AGILITY] = agility;
}

unsigned int Player::luck()
{
    return _stats[STATS_LUCK];
}

void Player::setLuck(unsigned int luck)
{
    _stats[STATS_LUCK] = luck;
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

}

