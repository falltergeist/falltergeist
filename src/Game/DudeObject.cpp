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

// C++ standard includes
#include <cmath>
#include <functional>

// Falltergeist includes
#include "DudeObject.h"
#include "WeaponItemObject.h"
#include "../Game/Game.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationQueue.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Image.h"

// Third party includes

using namespace libfalltergeist;

namespace Falltergeist
{
namespace Game
{

GameDudeObject::GameDudeObject() : GameCritterObject()
{
    _type = Type::DUDE;
}

GameDudeObject::~GameDudeObject()
{
}

void GameDudeObject::loadFromGCDFile(libfalltergeist::Gcd::File* gcd)
{
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        setStat((STAT)i, gcd->stat((STAT)i));
        setStatBonus((STAT)i, gcd->statBonus((STAT)i));
    }    

    _statsPoints = gcd->characterPoints();
    _name = gcd->name();
    _age = gcd->age();

    _hitPointsMax = gcd->hitPoints() + gcd->hitPointsBonus();
    _hitPoints = _hitPointsMax;

    if ((signed)gcd->firstTrait() >= 0) setTraitTagged(gcd->firstTrait(), 1);
    if ((signed)gcd->secondTrait() >= 0) setTraitTagged(gcd->secondTrait(), 1);

    if ((signed)gcd->firstTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->firstTaggedSkill(), 1);
        _skillsPoints--;
    }
    if ((signed)gcd->secondTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->secondTaggedSkill(), 1);
        _skillsPoints--;
    }
    if ((signed)gcd->thirdTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->thirdTaggedSkill(), 1);
        _skillsPoints--;
    }

    setGender(gcd->gender());
    setActionPoints(actionPointsMax());
}

int GameDudeObject::experience() const
{
    return _experience;
}

void GameDudeObject::setExperience(int value)
{
    _experience = value;
}

std::string GameDudeObject::biography() const
{
    return _biography;
}

void GameDudeObject::setBiography(const std::string& value)
{
    _biography = value;
}

int GameDudeObject::statsPoints() const
{
    return _statsPoints;
}

void GameDudeObject::setStatsPoints(int value)
{
    _statsPoints = value;
}

int GameDudeObject::skillsPoints() const
{
    return _skillsPoints;
}

void GameDudeObject::setSkillsPoints(int value)
{
    _skillsPoints = value;
}

int GameDudeObject::hitPointsMax() const
{
    int value = 15;
    value += statTotal(STAT::ENDURANCE) * 2;
    value += statTotal(STAT::STRENGTH);
    value += (2 + ceil(statTotal(STAT::ENDURANCE)/2))*(level() - 1);
    return value;
}

int GameDudeObject::level() const
{
    return _level;
}

void GameDudeObject::setLevel(int value)
{
    _level = value;
}

int GameDudeObject::armorClass() const
{
    unsigned int value = 0;
    if (!traitTagged(TRAIT::KAMIKAZE))
    {
        value += statTotal(STAT::AGILITY) > 10 ? 10 : statTotal(STAT::AGILITY);
    }
    return value;

}

int GameDudeObject::actionPointsMax() const
{
    unsigned int value = 0;
    value += 5 + ceil(statTotal(STAT::AGILITY)/2);
    if (traitTagged(TRAIT::BRUISER))
    {
        value -= 2;
    }
    return value;
}

unsigned int GameDudeObject::carryWeightMax() const
{
    unsigned int value = 0;
    unsigned int st = statTotal(STAT::STRENGTH);

    if (traitTagged(TRAIT::SMALL_FRAME))
    {
        value += 25 + 15*(st > 10 ? 10 : st);
        if (traitTagged(TRAIT::GIFTED) && st <= 10)
        {
            value += 10;
        }
    }
    else
    {
        value += 25 + 25*(st > 10 ? 10 : st);
    }
    return value;
}

int GameDudeObject::meleeDamage() const
{
    unsigned int value = 0;
    unsigned int st = statTotal(STAT::STRENGTH);
    if (st > 10) st = 10;
    value += st > 5 ? st - 5 : 1;
    if (traitTagged(TRAIT::HEAVY_HANDED))
    {
        value += 4;
    }
    return value;
}

int GameDudeObject::damageResistance() const
{
    return 0;
}

int GameDudeObject::radiationResistance() const
{
    return 0;
}

int GameDudeObject::poisonResistance() const
{
    int value = 0;
    if (!traitTagged(TRAIT::FAST_METABOLISM))
    {
        value += 5*statTotal(STAT::ENDURANCE);
    }
    return value;
}

int GameDudeObject::sequence() const
{
    unsigned int value = 0;
    unsigned int pe = statTotal(STAT::PERCEPTION);
    value += 2*(pe > 10 ? 10 : pe);
    if (traitTagged(TRAIT::KAMIKAZE))
    {
        value += 5;
    }
    return value;
}

int GameDudeObject::healingRate() const
{
    unsigned int value = 0;
    unsigned int en = statTotal(STAT::ENDURANCE);
    value += ceil((en > 10 ? 10 : en) / 3);
    if (value == 0) value = 1;

    if (traitTagged(TRAIT::FAST_METABOLISM))
    {
        value += 2;
    }
    return value;
}

int GameDudeObject::criticalChance() const
{
    unsigned int value = 0;
    unsigned int lk = statTotal(STAT::LUCK);
    value += lk > 10 ? 10 : lk;
    if (traitTagged(TRAIT::FINESSE))
    {
        value += 10;
    }
    return value;
}

void GameDudeObject::_generateUi()
{
    GameCritterObject::_generateUi();
    return;
    delete _ui; _ui = 0;

    auto queue = new AnimationQueue();
    auto animation = _generateMovementAnimation();
    queue->animations()->push_back(animation);
    queue->setRepeat(true);
    queue->start();
    _ui = queue;

    addUIEventHandlers();
}

}
}
