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

// C++ standard includes
#include <cmath>
#include <functional>

// Falltergeist includes
#include "../Game/GameDudeObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../Game.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationQueue.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimatedImage.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

GameDudeObject::GameDudeObject() : GameCritterObject()
{
    _type = TYPE_DUDE;
}

GameDudeObject::~GameDudeObject()
{
}

void GameDudeObject::loadFromGCDFile(std::shared_ptr<libfalltergeist::GcdFileType> gcd)
{
    for (unsigned int i = 0; i <= 6; i++)
    {
        setStat(i, gcd->stat(i));
        setStatBonus(i, gcd->statBonus(i));
    }

    _statsPoints = gcd->characterPoints();
    _name = gcd->name();
    _age = gcd->age();

    _hitPointsMax = gcd->hitPoints() + gcd->hitPointsBonus();
    _hitPoints = _hitPointsMax;

    if (gcd->firstTrait() >= 0) setTraitTagged(gcd->firstTrait(), 1);
    if (gcd->secondTrait() >= 0) setTraitTagged(gcd->secondTrait(), 1);

    if (gcd->firstTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->firstTaggedSkill(), 1);
        _skillsPoints--;
    }
    if (gcd->secondTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->secondTaggedSkill(), 1);
        _skillsPoints--;
    }
    if (gcd->thirdTaggedSkill() >= 0)
    {
        setSkillTagged(gcd->thirdTaggedSkill(), 1);
        _skillsPoints--;
    }

    setGender(gcd->gender());
    setActionPoints(actionPointsMax());
}

int GameDudeObject::experience()
{
    return _experience;
}

void GameDudeObject::setExperience(int value)
{
    _experience = value;
}

std::string GameDudeObject::biography()
{
    return _biography;
}

void GameDudeObject::setBiography(std::string value)
{
    _biography = value;
}

int GameDudeObject::age()
{
    return _age;
}

void GameDudeObject::setAge(int value)
{
    _age = value;
}

int GameDudeObject::statsPoints()
{
    return _statsPoints;
}

void GameDudeObject::setStatsPoints(int value)
{
    _statsPoints = value;
}

int GameDudeObject::skillsPoints()
{
    return _skillsPoints;
}

void GameDudeObject::setSkillsPoints(int value)
{
    _skillsPoints = value;
}

int GameDudeObject::hitPointsMax()
{
    int value = 15;
    value += statTotal(STATS_ENDURANCE) * 2;
    value += statTotal(STATS_STRENGTH);
    value += (2 + ceil(statTotal(STATS_ENDURANCE)/2))*(level() - 1);
    return value;
}

int GameDudeObject::level()
{
    return _level;
}

void GameDudeObject::setLevel(int value)
{
    _level = value;
}

int GameDudeObject::armorClass()
{
    unsigned int value = 0;
    if (!traitTagged(TRAITS_KAMIKAZE))
    {
        value += statTotal(STATS_AGILITY) > 10 ? 10 : statTotal(STATS_AGILITY);
    }
    return value;

}

int GameDudeObject::actionPointsMax()
{
    unsigned int value = 0;
    value += 5 + ceil(statTotal(STATS_AGILITY)/2);
    if (traitTagged(TRAITS_BRUISER))
    {
        value -= 2;
    }
    return value;
}

unsigned int GameDudeObject::carryWeightMax()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);

    if (traitTagged(TRAITS_SMALL_FRAME))
    {
        value += 25 + 15*(st > 10 ? 10 : st);
        if (traitTagged(TRAITS_GIFTED) && st <= 10)
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

int GameDudeObject::meleeDamage()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);
    if (st > 10) st = 10;
    value += st > 5 ? st - 5 : 1;
    if (traitTagged(TRAITS_HEAVY_HANDED))
    {
        value += 4;
    }
    return value;
}

int GameDudeObject::damageResistance()
{
    return 0;
}

int GameDudeObject::radiationResistance()
{
    return 0;
}

int GameDudeObject::poisonResistance()
{
    int value = 0;
    if (!traitTagged(TRAITS_FAST_METABOLISM))
    {
        value += 5*statTotal(STATS_ENDURANCE);
    }
    return value;
}

int GameDudeObject::sequence()
{
    unsigned int value = 0;
    unsigned int pe = statTotal(STATS_PERCEPTION);
    value += 2*(pe > 10 ? 10 : pe);
    if (traitTagged(TRAITS_KAMIKAZE))
    {
        value += 5;
    }
    return value;
}

int GameDudeObject::healingRate()
{
    unsigned int value = 0;
    unsigned int en = statTotal(STATS_ENDURANCE);
    value += ceil((en > 10 ? 10 : en) / 3);
    if (value == 0) value = 1;

    if (traitTagged(TRAITS_FAST_METABOLISM))
    {
        value += 2;
    }
    return value;
}

int GameDudeObject::criticalChance()
{
    unsigned int value = 0;
    unsigned int lk = statTotal(STATS_LUCK);
    value += lk > 10 ? 10 : lk;
    if (traitTagged(TRAITS_FINESSE))
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

    if (_ui)
    {
        _ui->addEventHandler("mouseleftdown", std::bind(&State::Location::onMouseDown, Game::getInstance()->Location(), std::placeholders::_1, static_cast<GameObject*>(this)));
    }
}

unsigned int GameDudeObject::radiationLevel()
{
    return _radiationLevel;
}

void GameDudeObject::setRadiationLevel(unsigned int value)
{
    _radiationLevel = value;
}

}
