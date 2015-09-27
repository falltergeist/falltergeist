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

// Related headers
#include "../Game/CritterObject.h"

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Exception.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/WeaponItemObject.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationFrame.h"
#include "../UI/AnimationQueue.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

CritterObject::CritterObject() : Object()
{
    _type = Type::CRITTER;
    _setupNextIdleAnim();
}

CritterObject::~CritterObject()
{
}

std::vector<ItemObject*>* CritterObject::inventory()
{
    return &_inventory;
}

void CritterObject::setOrientation(Orientation value)
{
    Object::setOrientation(value);
}

ArmorItemObject* CritterObject::armorSlot() const
{
    return _armorSlot;
}

void CritterObject::setArmorSlot(ArmorItemObject* object)
{
    if (object)
    {
        setFID((_gender == GENDER::FEMALE) ? object->femaleFID() : object->maleFID());
    }
    else
    {
        setFID((_gender == GENDER::FEMALE) ? FID_HFJMPS : FID_HMJMPS);
    }
    _armorSlot = object;
}

ItemObject* CritterObject::leftHandSlot() const
{
    return _leftHandSlot;
}

void CritterObject::setLeftHandSlot(ItemObject* object)
{
    _leftHandSlot = object;
}

ItemObject* CritterObject::rightHandSlot() const
{
    return _rightHandSlot;
}

void CritterObject::setRightHandSlot(ItemObject* object)
{
    _rightHandSlot = object;
}

GENDER CritterObject::gender() const
{
    return _gender;
}

void CritterObject::setGender(GENDER value)
{
    if (value > GENDER::FEMALE) throw Exception("CritterObject::setGender(value) - value out of range:" + std::to_string((unsigned)value));
    _gender = value;
}

int CritterObject::stat(STAT num) const
{
    if (num > STAT::LUCK) throw Exception("CritterObject::stat(num) - num out of range:" + std::to_string((unsigned)num));
    return _stats.at((unsigned)num);
}

void CritterObject::setStat(STAT num, int value)
{
    if (num > STAT::LUCK) throw Exception("CritterObject::setStat(num, value) - num out of range:" + std::to_string((unsigned)num));
    _stats.at((unsigned)num) = value;
}

int CritterObject::statTotal(STAT num) const
{
    if (num > STAT::LUCK) throw Exception("CritterObject::statTotal(num) - num out of range:" + std::to_string((unsigned)num));
    return stat(num) + statBonus(num);
}

int CritterObject::statBonus(STAT num) const
{
    if (num > STAT::LUCK) throw Exception("CritterObject::statBonus(num) - num out of range:" + std::to_string((unsigned)num));
    int bonus = 0;
    if (traitTagged(TRAIT::GIFTED)) bonus += 1;
    switch(num)
    {
        case STAT::STRENGTH:
            if (traitTagged(TRAIT::BRUISER)) bonus += 2;
            break;
        case STAT::AGILITY:
            if (traitTagged(TRAIT::SMALL_FRAME)) bonus += 1;
            break;
        default:
            break;
    }
    return _statsBonus.at((unsigned)num) + bonus;
}

void CritterObject::setStatBonus(STAT num, int value)
{
    if (num > STAT::LUCK) throw Exception("CritterObject::setStatBonus(num, value) - num out of range:" + std::to_string((unsigned)num));
    _statsBonus.at((unsigned)num) = value;
}

int CritterObject::skillTagged(SKILL num) const
{
    if (num > SKILL::OUTDOORSMAN) throw Exception("CritterObject::skillTagged(num) - num out of range:" + std::to_string((unsigned)num));
    return _skillsTagged.at((unsigned)num);
}

void CritterObject::setSkillTagged(SKILL num, int value)
{
    if (num > SKILL::OUTDOORSMAN) throw Exception("CritterObject::setSkillTagged(num, value) - num out of range:" + std::to_string((unsigned)num));
    _skillsTagged.at((unsigned)num) = value;
}

int CritterObject::skillBaseValue(SKILL skill) const
{
    if (skill > SKILL::OUTDOORSMAN) throw Exception("CritterObject::skillBaseValue(num) - num out of range:" + std::to_string((unsigned)skill));
    int value = 0;
    switch(skill)
    {
        case SKILL::SMALL_GUNS:
            value += 5 + 4 * statTotal(STAT::AGILITY);
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::BIG_GUNS:
            value += 2*statTotal(STAT::AGILITY);
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::ENERGY_WEAPONS:
            value += 2*statTotal(STAT::AGILITY);
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::UNARMED:
            value += 30 + 2*(statTotal(STAT::AGILITY) + statTotal(STAT::STRENGTH));
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::MELEE_WEAPONS:
            value += 20 + 2*(statTotal(STAT::AGILITY) + statTotal(STAT::STRENGTH));
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::THROWING:
            value += 4*statTotal(STAT::AGILITY);
            if (traitTagged(TRAIT::GOOD_NATURED)) value -= 10;
            break;
        case SKILL::FIRST_AID:
            value += 20 + 2*(statTotal(STAT::PERCEPTION) + statTotal(STAT::INTELLIGENCE));
            if (traitTagged(TRAIT::GOOD_NATURED)) value += 15;
            break;
        case SKILL::DOCTOR:
            value += 20 + 5 + (statTotal(STAT::PERCEPTION) + statTotal(STAT::INTELLIGENCE));
            if (traitTagged(TRAIT::GOOD_NATURED)) value += 15;
            break;
        case SKILL::SNEAK:
            value += 20 + 5 + 3*statTotal(STAT::AGILITY);
            break;
        case SKILL::LOCKPICK:
            value += 20 + 10 + (statTotal(STAT::PERCEPTION) + statTotal(STAT::AGILITY));
            break;
        case SKILL::STEAL:
            value += 20 + 3*statTotal(STAT::AGILITY);
            break;
        case SKILL::TRAPS:
            value += 20 + 10 + (statTotal(STAT::PERCEPTION) + statTotal(STAT::AGILITY));
            break;
        case SKILL::SCIENCE:
            value += 20 + 4*statTotal(STAT::INTELLIGENCE);
            break;
        case SKILL::REPAIR:
            value += 20 + 3*statTotal(STAT::INTELLIGENCE);
            break;
        case SKILL::SPEECH:
            value += 20 + 5*statTotal(STAT::CHARISMA);
            if (traitTagged(TRAIT::GOOD_NATURED)) value += 15;
            break;
        case SKILL::BARTER:
            value += 20 + 4*statTotal(STAT::CHARISMA);
            if (traitTagged(TRAIT::GOOD_NATURED)) value += 15;
            break;
        case SKILL::GAMBLING:
            value += 20 + 5*statTotal(STAT::LUCK);
            break;
        case SKILL::OUTDOORSMAN:
            value += 20 + 2*(statTotal(STAT::ENDURANCE) + statTotal(STAT::INTELLIGENCE));
            break;
        default:
            break;
    }

    if (traitTagged(TRAIT::GIFTED))
    {
        value -= 10;
    }

    if (skillTagged(skill))
    {
        value += 20;
    }

    return value;
}

int CritterObject::traitTagged(TRAIT num) const
{
    if (num > TRAIT::GIFTED) throw Exception("CritterObject::traitTagged(num) - num out of range:" + std::to_string((unsigned)num));
    return _traitsTagged.at((unsigned)num);
}

void CritterObject::setTraitTagged(TRAIT num, int value)
{
    if (num > TRAIT::GIFTED) throw Exception("CritterObject::setTraitTagged(num, value) - num out of range:" + std::to_string((unsigned)num));
    _traitsTagged.at((unsigned)num) = value;
}

int CritterObject::hitPoints() const
{
    return _hitPoints;
}

void CritterObject::setHitPoints(int value)
{
    _hitPoints = value;
}

int CritterObject::hitPointsMax() const
{
    return _hitPointsMax;
}

void CritterObject::setHitPointsMax(int value)
{
    _hitPointsMax = value;
}

int CritterObject::armorClass() const
{
    return _armorClass;
}

void CritterObject::setArmorClass(int value)
{
    _armorClass = value;
}

int CritterObject::actionPoints() const
{
    return _actionPoints;
}

void CritterObject::setActionPoints(int value)
{
    _actionPoints = value;
}

int CritterObject::actionPointsMax() const
{
    return _actionPointsMax;
}

void CritterObject::setActionPointsMax(int value)
{
    _actionPointsMax = value;
}

unsigned int CritterObject::carryWeight() const
{
    unsigned int weight = 0;
    for (auto item : _inventory)
    {
        weight += item->weight();
    }

    if (auto armor = dynamic_cast<ItemObject*>(armorSlot()))
    {
        weight += armor->weight();
    }

    if (auto leftHand = dynamic_cast<ItemObject*>(leftHandSlot()))
    {
        weight += leftHand->weight();
    }

    if (auto rightHand = dynamic_cast<ItemObject*>(rightHandSlot()))
    {
        weight += rightHand->weight();
    }

    return weight;
}

void CritterObject::setCarryWeightMax(unsigned int value)
{
    _carryWeightMax = value;
}

unsigned int CritterObject::carryWeightMax() const
{
    return _carryWeightMax;
}

int CritterObject::meleeDamage() const
{
    return _meleeDamage;
}

void CritterObject::setMeleeDamage(int value)
{
    _meleeDamage = value;
}

int CritterObject::sequence() const
{
    return _sequence;
}

void CritterObject::setSequence(int value)
{
    _sequence = value;
}

int CritterObject::criticalChance() const
{
    return _criticalChance;
}

void CritterObject::setCriticalChance(int value)
{
    _criticalChance = value;
}

int CritterObject::healingRate() const
{
    return _healingRate;
}

void CritterObject::setHealingRate(int value)
{
    _healingRate = value;
}

int CritterObject::damageResist(DAMAGE type) const
{
    if (type > DAMAGE::POISON) throw Exception("CritterObject::damageResist(type) - type out of range: " + std::to_string((unsigned)type));
    return _damageResist.at((unsigned)type);
}

void CritterObject::setDamageResist(DAMAGE type, int value)
{
    if (type > DAMAGE::POISON) throw Exception("CritterObject::setDamageResist(type, value) - type out of range: " + std::to_string((unsigned)type));
    _damageResist.at((unsigned)type) = value;
}

int CritterObject::damageThreshold(DAMAGE type) const
{
    if ( type > DAMAGE::POISON) throw Exception("CritterObject::damageThreshold(type) - type out of range: " + std::to_string((unsigned)type));
    return _damageThreshold.at((unsigned)type);
}

void CritterObject::setDamageThreshold(DAMAGE type, int value)
{
    if ( type > DAMAGE::POISON) throw Exception("CritterObject::setDamageThreshold(type, value) - type out of range: " + std::to_string((unsigned)type));
    _damageThreshold.at((unsigned)type) = value;
}

HAND CritterObject::currentHand() const
{
    return _currentHand;
}

void CritterObject::setCurrentHand(HAND value)
{
    if (value > HAND::LEFT) throw Exception("CritterObject::setCurrentHand(value) - value out of range: " + std::to_string((unsigned)value));
    _currentHand = value;
}

ItemObject* CritterObject::currentHandSlot() const
{
    return currentHand() == HAND::RIGHT ? rightHandSlot() : leftHandSlot();
}

void CritterObject::talk_p_proc()
{
    if (_script && _script->hasFunction("talk_p_proc"))
    {
        _script
            ->setSourceObject(Game::getInstance()->player())
            ->call("talk_p_proc");
    }
}

void CritterObject::damage_p_proc()
{
}

void CritterObject::combat_p_proc()
{
}

void CritterObject::critter_p_proc()
{
    if (_script && _script->hasFunction("critter_p_proc"))
    {
        _script->call("critter_p_proc");
    }
}

void CritterObject::is_dropping_p_proc()
{
}

void CritterObject::use_skill_on_p_proc()
{
}

std::vector<Hexagon*>* CritterObject::movementQueue()
{
    return &_movementQueue;
}

void CritterObject::think()
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
            animation->addEventHandler("actionFrame",    std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
            animation->addEventHandler("animationEnded", std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
            animation->play();
            _ui = animation;
        }
    }
    else
    {
        auto anim = (UI::Animation*)ui();
        if (!_moving && (!anim || !anim->playing()))
        {
            if (SDL_GetTicks() > _nextIdleAnim)
            {
                setActionAnimation("aa");
                _setupNextIdleAnim();
            }
        }
    }
    Object::think();
}

void CritterObject::onMovementAnimationEnded(Event::Event* event)
{
    auto hexagon = movementQueue()->back();
    movementQueue()->pop_back();
    Game::getInstance()->locationState()->moveObjectToHexagon(this, hexagon);
    auto animation = dynamic_cast<UI::Animation*>(ui());

    if (movementQueue()->size() == 0)
    {
        _moving = false;
        animation->stop();
        setActionAnimation("aa")->stop();
        _setupNextIdleAnim();
        return;
    }

    auto newHexagon = movementQueue()->back();
    auto newOrientation = this->hexagon()->orientationTo(newHexagon);

    if (event->name() == "animationEnded" || newOrientation != orientation())
    {
        _orientation = newOrientation;
        auto newAnimation = _generateMovementAnimation();
        if (event->name() == "actionFrame")
        {
            newAnimation->setCurrentFrame(animation->currentFrame());
            newAnimation->setActionFrame(animation->actionFrame());
        }
        else
        {
            newAnimation->setActionFrame(_running ? 2 : 4);
        }
        newAnimation->addEventHandler("actionFrame",    std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
        newAnimation->addEventHandler("animationEnded", std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
        newAnimation->play();
        delete _ui;
        _ui = animation = newAnimation;
    }

    if (event->name() == "actionFrame")
    {
        // at each action frame critter switches to the next hex and frame positions are offset relative to the action frame offsets
        auto actionFrame = animation->frames().at(animation->actionFrame()).get();
        for (auto it = animation->frames().rbegin(); it != animation->frames().rend(); ++it)
        {
            auto frame = (*it).get();
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
}

UI::Animation* CritterObject::_generateMovementAnimation()
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

    return new UI::Animation("art/critters/" + frmString + ".frm", orientation());
}

UI::Animation* CritterObject::setActionAnimation(const std::string& action)
{
    UI::Animation* animation = new UI::Animation("art/critters/" + _generateArmorFrmString() + action + ".frm", orientation());
    animation->addEventHandler("animationEnded", [animation](Event::Event* event)
    {
        animation->setCurrentFrame(0);
    });
    animation->play();
    /*auto queue = new AnimationQueue();
    queue->setRepeat(true);
    queue->animations()->push_back(animation);
    queue->start();*/
    setUI(animation);
    return animation;
}

void CritterObject::setRadiationLevel(int radiationLevel)
{
    this->_radiationLevel = radiationLevel;
}

int CritterObject::radiationLevel() const
{
    return _radiationLevel;
}

std::string CritterObject::_generateArmorFrmString()
{
    if (!armorSlot())
    {
        return ResourceManager::getInstance()->FIDtoFrmName(FID()).substr(13,6);
    }

    switch (gender())
    {
        case GENDER::FEMALE:
        {
            return ResourceManager::getInstance()->FIDtoFrmName(armorSlot()->femaleFID()).substr(13, 6);
        }
        default: // MALE
        {
            return ResourceManager::getInstance()->FIDtoFrmName(armorSlot()->maleFID()).substr(13, 6);
        }
    }
}

std::string CritterObject::_generateWeaponFrmString()
{
    if (auto weapon = dynamic_cast<WeaponItemObject*>(currentHandSlot()))
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

int CritterObject::poisonLevel() const
{
    return _poisonLevel;
}

void CritterObject::setPoisonLevel(int value)
{
    _poisonLevel = value;
}

int CritterObject::skillValue(SKILL skill) const
{
    if (skill > SKILL::OUTDOORSMAN) throw Exception("CritterObject::skillValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
    return skillBaseValue(skill) + skillGainedValue(skill);
}

int CritterObject::skillGainedValue(SKILL skill) const
{
    if (skill > SKILL::OUTDOORSMAN) throw Exception("CritterObject::skillGainedValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
    return _skillsGainedValue.at((unsigned)skill);
}

void CritterObject::setSkillGainedValue(SKILL skill, int value)
{
    if (skill > SKILL::OUTDOORSMAN) throw Exception("CritterObject::setSkillGainedCalue(skill) - skill out of range:" + std::to_string((unsigned)skill));
    _skillsGainedValue.at((unsigned)skill) = value;
}

bool CritterObject::running() const
{
    return _running;
}

void CritterObject::setRunning(bool value)
{
    _running = value;
}

void CritterObject::stopMovement()
{
    _movementQueue.clear();
    // @TODO: _ui probably needs to be always one type
    if (auto queue = dynamic_cast<UI::AnimationQueue*>(_ui))
    {
        queue->stop();
    }
    else if (auto animation = dynamic_cast<UI::Animation*>(_ui))
    {
        animation->stop();
    }
    _moving = false;
}

void CritterObject::_setupNextIdleAnim()
{
    _nextIdleAnim = SDL_GetTicks() + 10000 + (rand() % 7000);
}

unsigned CritterObject::age() const
{
    return _age;
}

void CritterObject::setAge(unsigned value)
{
    _age = value;
}


}
}
