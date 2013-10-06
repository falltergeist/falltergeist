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
    unsigned char _age;

    char _gender;

    unsigned int * _stats;
    unsigned int * _traits;
    unsigned int * _skills;

    unsigned int _characterPoints;
    unsigned int _skillPoints;

public:
    enum {GENDER_MALE = 0, GENDER_FEMALE = 1};
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
    enum { SKILLS_1 = 0, // Small Guns
           SKILLS_2, // Big Guns
           SKILLS_3, // Energy Weapons
           SKILLS_4, // Unarmed
           SKILLS_5, // Melee Weapons
           SKILLS_6, // Throwing
           SKILLS_7, // First Aid
           SKILLS_8, // Doctor
           SKILLS_9, // Sneak
           SKILLS_10, // Lockpick
           SKILLS_11, // Steal
           SKILLS_12, // Traps
           SKILLS_13, // Science
           SKILLS_14, // Repair
           SKILLS_15, // Speech
           SKILLS_16, // Barter
           SKILLS_17, // Gambling
           SKILLS_18  // Outdoorsman
    };
    enum { SKILLS_SMALL_GUNS = 0,
           SKILLS_BIG_GUNS,
           SKILLS_ENERGY_WEAPONS,
           SKILLS_UNARMED,
           SKILLS_MELEE_WEAPONS,
           SKILLS_THROWING,
           SKILLS_FIRST_AID,
           SKILLS_DOCTOR,
           SKILLS_SNEAK,
           SKILLS_LOCKPICK,
           SKILLS_STEAL,
           SKILLS_TRAPS,
           SKILLS_SCIENCE,
           SKILLS_REPAIR,
           SKILLS_SPEECH,
           SKILLS_BARTER,
           SKILLS_GAMBLING,
           SKILLS_OUTDOORSMAN
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

    void setAge(unsigned char age);
    unsigned char age();

    void setBio(const char * text);
    const char * name();

    bool statsIncrease(unsigned char stat);
    bool statsDecrease(unsigned char stat);

    unsigned int trait(unsigned int traitNumber);
    void setTrait(unsigned int traitNumber, unsigned int value);

    bool traitToggle(unsigned int traitNumber);

    unsigned int skill(unsigned int skillNumber);
    void setSkill(unsigned int skillNumber, unsigned int value);

    bool skillToggle(unsigned int skillNumber);

    unsigned int skillPoints();
    void setSkillPoints(unsigned int skillPoints);

    char gender();
    void setGender(char gender);

};

}
#endif	/* FALLTERGEIST_PLAYER_H */

