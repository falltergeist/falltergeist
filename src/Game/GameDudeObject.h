/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../Game/GameCritterObject.h"
#include <libfalltergeist.h>

// Third party includes

namespace Falltergeist
{

class GameDudeObject : public GameCritterObject
{
protected:
    int _level = 1;
    int _experience = 0;
    int _statsPoints = 0;
    int _skillsPoints = 3;
    int _age = 0;
    unsigned int _radiationLevel = 0;
    std::string _biography;
    virtual void _generateUi();
public:
    GameDudeObject();
    virtual ~GameDudeObject();

    void loadFromGCDFile(std::shared_ptr<libfalltergeist::GcdFileType> gcd);

    int experience();
    void setExperience(int value);

    std::string biography();
    void setBiography(std::string value);

    int age();
    void setAge(int value);

    int statsPoints();
    void setStatsPoints(int value);

    int skillsPoints();
    void setSkillsPoints(int value);

    int level();
    void setLevel(int value);

    int damageResistance();
    int poisonResistance();
    int radiationResistance();
    // Overloaded
    int hitPointsMax();
    int actionPointsMax();
    int armorClass();
    int meleeDamage();
    int sequence();
    int healingRate();
    int criticalChance();
    unsigned int carryWeightMax();

    unsigned int radiationLevel();
    void setRadiationLevel(unsigned int value);
};

}
#endif // FALLTERGEIST_GAMEDUDEOBJECT_H
