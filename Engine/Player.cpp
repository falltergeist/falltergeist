#include <string.h>

#include "Player.h"

namespace Falltergeist
{
    
Player::Player()
{
    _bio = 0;
    _name = 0;
}

Player::Player(GcdFileType * gcd)
{
    _bio = 0;
    _name = 0;
    this->strength = gcd->strength;
    this->perception = gcd->perception;
    this->endurance = gcd->endurance;
    this->charisma = gcd->charisma;
    this->intelligence = gcd->intelligence;
    this->agility = gcd->agility;
    this->luck = gcd->luck;
    this->freeStatsPoints = gcd->characterPoints;
    this->setName(gcd->name);
}

Player::~Player()
{
    delete [] _bio;
}

const char * Player::getBio()
{
    return _bio;
}

void Player::setBio(const char * text)
{
    delete _bio;
    _bio = new char[strlen(text)+1]();
    strcpy(_bio,text);
}

const char * Player::getName()
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

