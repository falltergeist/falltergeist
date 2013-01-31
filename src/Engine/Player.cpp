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

namespace Falltergeist
{
    
Player::Player()
{
    _bio = 0;
    _name = 0;
}

Player::Player(libfalltergeist::GcdFileType * gcd)
{
    _bio = 0;
    _name = 0;

    this->strength = gcd->strength();
    this->perception = gcd->perception();
    this->endurance = gcd->endurance();
    this->charisma = gcd->charisma();
    this->intelligence = gcd->intelligence();
    this->agility = gcd->agility();
    this->luck = gcd->luck();
    this->freeStatsPoints = gcd->characterPoints();
    this->setName(gcd->name());
}

Player::~Player()
{
    delete [] _bio;
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
    if (freeStatsPoints <= 0) return;
    unsigned char value;
    switch (stat)
    {
        case STATS_STRENGTH:
            value = strength;
            break;
        case STATS_PERCEPTION:
            value = perception;
            break;
        case STATS_ENDURANCE:
            value = endurance;
            break;
        case STATS_CHARISMA:
            value = charisma;
            break;
        case STATS_INTELLIGENCE:
            value = intelligence;
            break;
        case STATS_AGILITY:
            value = agility;
            break;
        case STATS_LUCK:
            value = luck;
            break;
    }

    if (value >= 10) return;

    value++;
    freeStatsPoints--;

    switch (stat)
    {
        case STATS_STRENGTH:
            strength = value;
            break;
        case STATS_PERCEPTION:
            perception = value;
            break;
        case STATS_ENDURANCE:
            endurance = value;
            break;
        case STATS_CHARISMA:
            charisma = value;
            break;
        case STATS_INTELLIGENCE:
            intelligence = value;
            break;
        case STATS_AGILITY:
            agility = value;
            break;
        case STATS_LUCK:
            luck = value;
            break;
    }
}

void Player::statsDecrease(unsigned char stat)
{
    unsigned char value;
    switch (stat)
    {
        case STATS_STRENGTH:
            value = strength;
            break;
        case STATS_PERCEPTION:
            value = perception;
            break;
        case STATS_ENDURANCE:
            value = endurance;
            break;
        case STATS_CHARISMA:
            value = charisma;
            break;
        case STATS_INTELLIGENCE:
            value = intelligence;
            break;
        case STATS_AGILITY:
            value = agility;
            break;
        case STATS_LUCK:
            value = luck;
            break;
    }

    if (value <= 2) return;

    value--;
    freeStatsPoints++;

    switch (stat)
    {
        case STATS_STRENGTH:
            strength = value;
            break;
        case STATS_PERCEPTION:
            perception = value;
            break;
        case STATS_ENDURANCE:
            endurance = value;
            break;
        case STATS_CHARISMA:
            charisma = value;
            break;
        case STATS_INTELLIGENCE:
            intelligence = value;
            break;
        case STATS_AGILITY:
            agility = value;
            break;
        case STATS_LUCK:
            luck = value;
            break;
    }
}


}

