/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAME_DUDEOBJECT_H
#define FALLTERGEIST_GAME_DUDEOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/CritterObject.h"
#include "../Graphics/Point.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Gcd
{
    class File;
}
}
namespace Game
{

using Graphics::Point;

/**
 * Player-controlled critter
 */
class DudeObject : public CritterObject
{
public:
    DudeObject();
    ~DudeObject() override;

    void loadFromGCDFile(Format::Gcd::File* gcd);

    int experience() const;
    void setExperience(int value);

    std::string biography() const;
    void setBiography(const std::string& value);

    int statsPoints() const;
    void setStatsPoints(int value);

    int skillsPoints() const;
    void setSkillsPoints(int value);

    int level() const;
    void setLevel(int value);

    int damageResistance() const;
    int poisonResistance() const;
    int radiationResistance() const;

    int hitPointsMax() const override;
    int actionPointsMax() const override;
    int armorClass() const override;
    int meleeDamage() const override;
    int sequence() const override;
    int healingRate() const override;
    int criticalChance() const override;
    unsigned int carryWeightMax() const override;

    virtual std::string scrName() const override;

    /**
     * Offset where to draw egg relative to dude hex.
     */
    Point eggOffset();

protected:
    int _level = 1;
    int _experience = 0;
    int _statsPoints = 0;
    int _skillsPoints = 3;
    std::string _biography;
    void _generateUi() override;
};

}
}
#endif // FALLTERGEIST_GAME_DUDEOBJECT_H
