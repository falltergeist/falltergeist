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

#ifndef FALLTERGEIST_PLAYER_H
#define	FALLTERGEIST_PLAYER_H
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{
    
class Player
{
protected:
    // text from .bio file
    char * _bio;
    char * _name;
public:
    enum {STATS_STRENGTH = 0, STATS_PERCEPTION, STATS_ENDURANCE, STATS_CHARISMA, STATS_INTELLIGENCE, STATS_AGILITY, STATS_LUCK };
    // primary stats
    unsigned int strength;
    unsigned int perception;
    unsigned int endurance;
    unsigned int charisma;
    unsigned int intelligence;
    unsigned int agility;
    unsigned int luck;
    unsigned int freeStatsPoints;
    
    Player();
    Player(libfalltergeist::GcdFileType * gcd);
    virtual ~Player();

    void setName(const char * name);    
    const char * bio();

    void setBio(const char * text);
    const char * name();

    void statsIncrease(unsigned char stat);
    void statsDecrease(unsigned char stat);
};

}
#endif	/* FALLTERGEIST_PLAYER_H */

