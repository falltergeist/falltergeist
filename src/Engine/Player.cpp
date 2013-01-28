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
    /*
    this->strength = gcd->strength;
    this->perception = gcd->perception;
    this->endurance = gcd->endurance;
    this->charisma = gcd->charisma;
    this->intelligence = gcd->intelligence;
    this->agility = gcd->agility;
    this->luck = gcd->luck;
    this->freeStatsPoints = gcd->characterPoints;
    this->setName(gcd->name);*/
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

}

