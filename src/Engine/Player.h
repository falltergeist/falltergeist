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

    unsigned int * _stats;
    unsigned int * _traits;
    unsigned int * _skills;

    unsigned int _characterPoints;

public:
    enum {STATS_STRENGTH = 0, STATS_PERCEPTION, STATS_ENDURANCE, STATS_CHARISMA, STATS_INTELLIGENCE, STATS_AGILITY, STATS_LUCK };
    enum {TRAITS_1 = 0, // Fast Metabolism
          TRAITS_2, // Bruiser
          TRAITS_3, // Small Frame
          TRAITS_4, // One Handed
          TRAITS_5, // Finesse
          TRAITS_6, // Kamikaze
          TRAITS_7, // Heavy Handed
          TRAITS_8, // Fast Shot
          TRAITS_9, // Bloody Mess
          TRAITS_10, // Jinxed
          TRAITS_11, // Good Natured
          TRAITS_12, // Chem Reliant
          TRAITS_13, // Chem Resistant
          TRAITS_14, // Sex Appeal
          TRAITS_15, // Skilled
          TRAITS_16  // Gifted
         };
    enum {TRAITS_FAST_METABOLISM = 0,
          TRAITS_BRUISER,
          TRAITS_SMALL_FRAME,
          TRAITS_ONE_HANDED,
          TRAITS_FINESSE,
          TRAITS_KAMIKAZE,
          TRAITS_HEAVY_HANDED,
          TRAITS_FAST_SHOT,
          TRAITS_BLOODY_MESS,
          TRAITS_JINXED,
          TRAITS_GOOD_NATURED,
          TRAITS_CHEM_RELIANT,
          TRAITS_CHEM_RESISTANT,
          TRAITS_SEX_APPEAL,
          TRAITS_SKILLED,
          TRAITS_GIFTES
         };

    // primary stats
    unsigned int strength();
    void setStrength(unsigned int strength);

    unsigned int perception();
    void setPerception(unsigned int perception);

    unsigned int endurance();
    void setEndurance(unsigned int endurance);

    unsigned int charisma();
    void setCharisma(unsigned int charisma);

    unsigned int intelligence();
    void setIntelligence(unsigned int intelligence);

    unsigned int agility();
    void setAgility(unsigned int agility);

    unsigned int luck();
    void setLuck(unsigned int luck);

    unsigned int characterPoints();
    void setCharacterPoints(unsigned int characterPoints);
    
    Player();
    Player(libfalltergeist::GcdFileType * gcd);
    virtual ~Player();

    void setName(const char * name);    
    const char * bio();

    void setBio(const char * text);
    const char * name();

    void statsIncrease(unsigned char stat);
    void statsDecrease(unsigned char stat);

    unsigned int trait(unsigned int traitNumber);
    void setTrait(unsigned int traitNumber, unsigned int value);

    bool traitToggle(unsigned int traitNumber);

};

}
#endif	/* FALLTERGEIST_PLAYER_H */

