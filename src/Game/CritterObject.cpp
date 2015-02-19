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
#include <string>

// Falltergeist includes
#include "CritterObject.h"
#include "WeaponItemObject.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Animation.h"
#include "../Graphics/AnimationFrame.h"
#include "../Graphics/AnimationQueue.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

GameCritterObject::GameCritterObject() : GameObject()
{
    _type = TYPE_CRITTER;
}

GameCritterObject::~GameCritterObject()
{
}

std::vector<GameItemObject*>* GameCritterObject::inventory()
{
    return &_inventory;
}

void GameCritterObject::setOrientation(int value)
{
    GameObject::setOrientation(value);
}

GameArmorItemObject* GameCritterObject::armorSlot()
{
    return _armorSlot;
}

void GameCritterObject::setArmorSlot(GameArmorItemObject* object)
{
    _armorSlot = object;
}

GameItemObject* GameCritterObject::leftHandSlot()
{
    return _leftHandSlot;
}

void GameCritterObject::setLeftHandSlot(GameItemObject* object)
{
    _leftHandSlot = object;
}

GameItemObject* GameCritterObject::rightHandSlot()
{
    return _rightHandSlot;
}

void GameCritterObject::setRightHandSlot(GameItemObject* object)
{
    _rightHandSlot = object;
}

int GameCritterObject::gender()
{
    return _gender;
}

void GameCritterObject::setGender(unsigned int value)
{
    if (value > 1) throw Exception("GameCritterObject::setGender(value) - value out of range:" + std::to_string(value));
    _gender = value;
}

int GameCritterObject::stat(unsigned int num)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::stat(num) - num out of range:" + std::to_string(num));
    return _stats.at(num);
}

void GameCritterObject::setStat(unsigned int num, int value)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::setStat(num, value) - num out of range:" + std::to_string(num));
    _stats.at(num) = value;
}

int GameCritterObject::statTotal(unsigned int num)
{
    if (num >= _stats.size()) throw Exception("GameCritterObject::statTotal(num) - num out of range:" + std::to_string(num));
    return stat(num) + statBonus(num);
}

int GameCritterObject::statBonus(unsigned int num)
{
    if (num >= _statsBonus.size()) throw Exception("GameCritterObject::statBonus(num) - num out of range:" + std::to_string(num));
    int bonus = 0;
    if (traitTagged(TRAITS_GIFTED)) bonus += 1;
    switch (num)
    {
        case STATS_STRENGTH:
            if (traitTagged(TRAITS_BRUISER)) bonus += 2;
            break;
        case STATS_AGILITY:
            if (traitTagged(TRAITS_SMALL_FRAME)) bonus += 1;
            break;
    }
    return _statsBonus.at(num) + bonus;
}

void GameCritterObject::setStatBonus(unsigned int num, int value)
{
    if (num >= _statsBonus.size()) throw Exception("GameCritterObject::setStatBonus(num, value) - num out of range:" + std::to_string(num));
    _statsBonus.at(num) = value;
}

int GameCritterObject::skillTagged(unsigned int num)
{
    if (num >= _skillsTagged.size()) throw Exception("GameCritterObject::skillTagged(num) - num out of range:" + std::to_string(num));
    return _skillsTagged.at(num);
}

void GameCritterObject::setSkillTagged(unsigned int num, int value)
{
    if (num >= _skillsTagged.size()) throw Exception("GameCritterObject::setSkillTagged(num, value) - num out of range:" + std::to_string(num));
    _skillsTagged.at(num) = value;
}

int GameCritterObject::skillBaseValue(unsigned int skill)
{
    if (skill >= _skillsTagged.size()) throw Exception("GameCritterObject::skillBaseValue(num) - num out of range:" + std::to_string(skill));
    int value = 0;
    switch(skill)
    {
        case SKILLS_SMALL_GUNS:
            value += 5 + 4 * statTotal(STATS_AGILITY);
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_BIG_GUNS:
            value += 2*statTotal(STATS_AGILITY);
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_ENERGY_WEAPONS:
            value += 2*statTotal(STATS_AGILITY);
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_UNARMED:
            value += 30 + 2*(statTotal(STATS_AGILITY) + statTotal(STATS_STRENGTH));
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_MELEE_WEAPONS:
            value += 20 + 2*(statTotal(STATS_AGILITY) + statTotal(STATS_STRENGTH));
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_THROWING:
            value += 4*statTotal(STATS_AGILITY);
            if (traitTagged(TRAITS_GOOD_NATURED)) value -= 10;
            break;
        case SKILLS_FIRST_AID:
            value += 20 + 2*(statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (traitTagged(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_DOCTOR:
            value += 20 + 5 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_INTELLIGENCE));
            if (traitTagged(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_SNEAK:
            value += 20 + 5 + 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_LOCKPICK:
            value += 20 + 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_STEAL:
            value += 20 + 3*statTotal(STATS_AGILITY);
            break;
        case SKILLS_TRAPS:
            value += 20 + 10 + (statTotal(STATS_PERCEPTION) + statTotal(STATS_AGILITY));
            break;
        case SKILLS_SCIENCE:
            value += 20 + 4*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_REPAIR:
            value += 20 + 3*statTotal(STATS_INTELLIGENCE);
            break;
        case SKILLS_SPEECH:
            value += 20 + 5*statTotal(STATS_CHARISMA);
            if (traitTagged(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_BARTER:
            value += 20 + 4*statTotal(STATS_CHARISMA);
            if (traitTagged(TRAITS_GOOD_NATURED)) value += 15;
            break;
        case SKILLS_GAMBLING:
            value += 20 + 5*statTotal(STATS_LUCK);
            break;
        case SKILLS_OUTDOORSMAN:
            value += 20 + 2*(statTotal(STATS_ENDURANCE) + statTotal(STATS_INTELLIGENCE));
            break;
    }

    if (traitTagged(TRAITS_GIFTED))
    {
        value -= 10;
    }

    if (skillTagged(skill))
    {
        value += 20;
    }

    return value;
}

int GameCritterObject::traitTagged(unsigned int num)
{
    if (num >= _traitsTagged.size()) throw Exception("GameCritterObject::traitTagged(num) - num out of range:" + std::to_string(num));
    return _traitsTagged.at(num);
}

void GameCritterObject::setTraitTagged(unsigned int num, int value)
{
    if (num >= _traitsTagged.size()) throw Exception("GameCritterObject::setTraitTagged(num, value) - num out of range:" + std::to_string(num));
    _traitsTagged.at(num) = value;
}

int GameCritterObject::hitPoints()
{
    return _hitPoints;
}

void GameCritterObject::setHitPoints(int value)
{
    _hitPoints = value;
}

int GameCritterObject::hitPointsMax()
{
    return _hitPointsMax;
}

void GameCritterObject::setHitPointsMax(int value)
{
    _hitPointsMax = value;
}

int GameCritterObject::armorClass()
{
    return _armorClass;
}

void GameCritterObject::setArmorClass(int value)
{
    _armorClass = value;
}

int GameCritterObject::actionPoints()
{
    return _actionPoints;
}

void GameCritterObject::setActionPoints(int value)
{
    _actionPoints = value;
}

int GameCritterObject::actionPointsMax()
{
    return _actionPointsMax;
}

void GameCritterObject::setActionPointsMax(int value)
{
    _actionPointsMax = value;
}

unsigned int GameCritterObject::carryWeight()
{
    unsigned int weight = 0;
    for (auto item : _inventory)
    {
        weight += item->weight();
    }

    if (auto armor = dynamic_cast<GameItemObject*>(armorSlot()))
    {
        weight += armor->weight();
    }

    if (auto leftHand = dynamic_cast<GameItemObject*>(leftHandSlot()))
    {
        weight += leftHand->weight();
    }

    if (auto rightHand = dynamic_cast<GameItemObject*>(rightHandSlot()))
    {
        weight += rightHand->weight();
    }

    return weight;
}

void GameCritterObject::setCarryWeightMax(unsigned int value)
{
    _carryWeightMax = value;
}

unsigned int GameCritterObject::carryWeightMax()
{
    return _carryWeightMax;
}

int GameCritterObject::meleeDamage()
{
    return _meleeDamage;
}

void GameCritterObject::setMeleeDamage(int value)
{
    _meleeDamage = value;
}

int GameCritterObject::sequence()
{
    return _sequence;
}

void GameCritterObject::setSequence(int value)
{
    _sequence = value;
}

int GameCritterObject::criticalChance()
{
    return _criticalChance;
}

void GameCritterObject::setCriticalChance(int value)
{
    _criticalChance = value;
}

int GameCritterObject::healingRate()
{
    return _healingRate;
}

void GameCritterObject::setHealingRate(int value)
{
    _healingRate = value;
}

int GameCritterObject::damageResist(unsigned int type)
{
    if (type > DAMAGE_POISON) throw Exception("GameCritterObject::damageResist(type) - type out of range: " + std::to_string(type));
    return _damageResist.at(type);
}

void GameCritterObject::setDamageResist(unsigned int type, int value)
{
    if (type > DAMAGE_POISON) throw Exception("GameCritterObject::setDamageResist(type, value) - type out of range: " + std::to_string(type));
    _damageResist.at(type) = value;
}

int GameCritterObject::damageThreshold(unsigned int type)
{
    if ( type > DAMAGE_POISON) throw Exception("GameCritterObject::damageThreshold(type) - type out of range: " + std::to_string(type));
    return _damageThreshold.at(type);
}

void GameCritterObject::setDamageThreshold(unsigned int type, int value)
{
    if ( type > DAMAGE_POISON) throw Exception("GameCritterObject::setDamageThreshold(type, value) - type out of range: " + std::to_string(type));
    _damageThreshold.at(type) = value;
}

unsigned int GameCritterObject::currentHand()
{
    return _currentHand;
}

void GameCritterObject::setCurrentHand(unsigned int value)
{
    if (value > HAND_LEFT) throw Exception("GameCritterObject::setCurrentHand(value) - value out of range: " + std::to_string(value));
    _currentHand = value;
}

GameItemObject* GameCritterObject::currentHandSlot()
{
    return currentHand() == HAND_RIGHT ? rightHandSlot() : leftHandSlot();
}

void GameCritterObject::talk_p_proc()
{
    script()->call("talk_p_proc");
}

void GameCritterObject::damage_p_proc()
{
}

void GameCritterObject::combat_p_proc()
{
}

void GameCritterObject::critter_p_proc()
{
    script()->call("critter_p_proc");
}

void GameCritterObject::is_dropping_p_proc()
{
}

void GameCritterObject::use_skill_on_p_proc()
{
}

std::vector<Hexagon*>* GameCritterObject::movementQueue()
{
    return &_movementQueue;
}

void GameCritterObject::think()
{
    if (movementQueue()->size() > 0)
    {
        if (!_moving)
        {
            _moving = true;

            delete _ui;
            _orientation = hexagon()->orientationTo(movementQueue()->back());
            auto animation = _generateMovementAnimation();
            animation->setActionFrame(_running ? 2 : 4);
            animation->addEventHandler("actionFrame",    std::bind(&GameCritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
            animation->addEventHandler("animationEnded", std::bind(&GameCritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
            animation->play();
            _ui = animation;
        }
    }
    GameObject::think();
}

void GameCritterObject::onMovementAnimationEnded(Event* event)
{
    auto hexagon = movementQueue()->back();
    movementQueue()->pop_back();
    Game::getInstance()->locationState()->moveObjectToHexagon(this, hexagon);

    if (movementQueue()->size() == 0)
    {
        _moving = false;
        dynamic_cast<Animation*>(_ui)->stop();
        setActionAnimation("aa");
        return;
    }

    auto newHexagon = movementQueue()->back();
    auto newOrientation = this->hexagon()->orientationTo(newHexagon);

    if (event->name() == "actionFrame" && newOrientation == orientation())
    {
        // at each action frame critter switches to the next hex and frame positions are offset relative to the action frame offsets
        auto animation = dynamic_cast<Animation*>(ui());
        auto actionFrame = animation->frames()->at(animation->actionFrame());
        for (auto it = animation->frames()->rbegin(); it != animation->frames()->rend(); ++it)
        {
            auto frame = (*it);
            frame->setXOffset(frame->xOffset() - actionFrame->xOffset());
            frame->setYOffset(frame->yOffset() - actionFrame->yOffset());
            if (frame == actionFrame) break;
        }

        if (_running)
        {
            switch (animation->actionFrame())
            {
                // those frame numbers were guessed to make seamless running animation
                case 2:
                    animation->setActionFrame(4);
                    break;
                case 4:
                    animation->setActionFrame(6);
                    break;
                case 5:
                    animation->setActionFrame(7);
                    break;
            }
        }

    }
    else // animationEnded || new orientation
    {
        delete _ui;
        _orientation = newOrientation;
        auto animation = _generateMovementAnimation();
        animation->setActionFrame(_running ? 2 : 4);
        animation->addEventHandler("actionFrame",    std::bind(&GameCritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
        animation->addEventHandler("animationEnded", std::bind(&GameCritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
        animation->play();
        _ui = animation;
    }
}

Animation* GameCritterObject::_generateMovementAnimation()
{
    std::string frmString = _generateArmorFrmString();

    if (_running)
    {
        frmString += "at";
    }
    else
    {
        frmString += _generateWeaponFrmString() + "b";
    }

    return new Animation("art/critters/" + frmString + ".frm", orientation());
}

Animation* GameCritterObject::setActionAnimation(std::string action)
{
    Animation* animation = new Animation("art/critters/" + _generateArmorFrmString() + action + ".frm", orientation());
    animation->play();
    auto queue = new AnimationQueue();
    queue->setRepeat(true);
    queue->animations()->push_back(animation);
    queue->start();
    setUI(queue);
    return animation;
}

void GameCritterObject::setRadiationLevel(int radiationLevel)
{
    this->_radiationLevel = radiationLevel;
}

int GameCritterObject::radiationLevel()
{
    return _radiationLevel;
}

std::string GameCritterObject::_generateArmorFrmString()
{
    if (!armorSlot())
    {
        return ResourceManager::FIDtoFrmName(FID()).substr(13,6);
    }

    switch(gender())
    {
        case GENDER_FEMALE:
        {
            return ResourceManager::FIDtoFrmName(armorSlot()->femaleFID()).substr(13, 6);
        }
        default: // MALE
        {
            return ResourceManager::FIDtoFrmName(armorSlot()->maleFID()).substr(13, 6);
        }
    }
}

std::string GameCritterObject::_generateWeaponFrmString()
{
    if (auto weapon = dynamic_cast<GameWeaponItemObject*>(currentHandSlot()))
    {
        switch (weapon->animationCode())
        {
            case 1: // knife
                return "d";
            case 2: // club
                return "e";
            case 3: // hammer
                return "f";
            case 4: // spear
                return "g";
            case 5: // pistol
                return "h";
            case 6: // smg
                return "i";
            case 7: // rifle
                return "j";
            case 8: // big gun
                return "k";
            case 9: // minigun
                return "l";
            case 10: // rocket launcher
                return "m";
        }
    }
    return "a";
}

int GameCritterObject::poisonLevel()
{
    return _poisonLevel;
}

void GameCritterObject::setPoisonLevel(int value)
{
    _poisonLevel = value;
}

int GameCritterObject::skillValue(unsigned int skill)
{
    if (skill >= _skillsTagged.size()) throw Exception("GameCritterObject::skillValue(skill) - skill out of range:" + std::to_string(skill));
    return skillBaseValue(skill) + skillGainedValue(skill);
}

int GameCritterObject::skillGainedValue(unsigned int skill)
{
    if (skill >= _skillsTagged.size()) throw Exception("GameCritterObject::skillGainedValue(skill) - skill out of range:" + std::to_string(skill));
    return _skillsGainedValue.at(skill);
}

void GameCritterObject::setSkillGainedValue(unsigned int skill, int value)
{
    if (skill >= _skillsTagged.size()) throw Exception("GameCritterObject::setSkillGainedCalue(skill) - skill out of range:" + std::to_string(skill));
    _skillsGainedValue.at(skill) = value;
}

bool GameCritterObject::running()
{
    return _running;
}

void GameCritterObject::setRunning(bool value)
{
    _running = value;
}

void GameCritterObject::stopMovement()
{
    _movementQueue.clear();
    auto queue = dynamic_cast<AnimationQueue*>(_ui);
    if (queue) queue->stop();
    _moving = false;
}


}
}
