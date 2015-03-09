/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAMEDUDEOBJECT_H
#define FALLTERGEIST_GAMEDUDEOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "CritterObject.h"
#include <libfalltergeist.h>

// Third party includes

namespace Falltergeist
{
namespace Game
{

/**
 * Player-controlled critter
 */
class GameDudeObject : public GameCritterObject
{
protected:
    int _level = 1;
    int _experience = 0;
    int _statsPoints = 0;
    int _skillsPoints = 3;
    std::string _biography;
    virtual void _generateUi();
public:
    GameDudeObject();
    virtual ~GameDudeObject();

    void loadFromGCDFile(libfalltergeist::Gcd::File* gcd);

    int experience() const;
    void setExperience(int value);

    std::string biography() const;
    void setBiography(std::string value);

    int statsPoints() const;
    void setStatsPoints(int value);

    int skillsPoints() const;
    void setSkillsPoints(int value);

    int level() const;
    void setLevel(int value);

    int damageResistance() const;
    int poisonResistance() const;
    int radiationResistance() const;
    // Overloaded
    int hitPointsMax() const;
    int actionPointsMax() const;
    int armorClass() const;
    int meleeDamage() const;
    int sequence() const;
    int healingRate() const;
    int criticalChance() const;
    unsigned int carryWeightMax() const;
    
};

}
}

#endif // FALLTERGEIST_GAMEDUDEOBJECT_H
