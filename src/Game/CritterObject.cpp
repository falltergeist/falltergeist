#include <array>
#include <string>
#include <memory>
#include "../Game/CritterObject.h"
#include "../Exception.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/ExitMiscObject.h"
#include "../Game/Game.h"
#include "../Game/WeaponItemObject.h"
#include "../Helpers/CritterAnimationHelper.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/Animation.h"
#include "../UI/AnimationFrame.h"
#include "../VM/Script.h"

namespace Falltergeist
{
    namespace Game
    {
        using namespace std;
        using namespace Base;
        using Helpers::CritterAnimationHelper;

        CritterObject::CritterObject() : Object()
        {
            _type = Type::CRITTER;
            _setupNextIdleAnim();
        }

        vector<ItemObject*>* CritterObject::inventory()
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
            if (object) {
                setFID((_gender == GENDER::FEMALE) ? object->femaleFID() : object->maleFID());
            } else {
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
            if (value > GENDER::FEMALE) {
                throw Exception("CritterObject::setGender(value) - value out of range:" + std::to_string((unsigned)value));
            }
            _gender = value;
        }

        int CritterObject::stat(STAT num) const
        {
            if (num > STAT::LUCK) {
                throw Exception("CritterObject::stat(num) - num out of range:" + std::to_string((unsigned)num));
            }
            return _stats.at((unsigned)num);
        }

        void CritterObject::setStat(STAT num, int value)
        {
            if (num > STAT::LUCK) {
                throw Exception("CritterObject::setStat(num, value) - num out of range:" + std::to_string((unsigned)num));
            }
            _stats.at((unsigned)num) = value;
        }

        int CritterObject::statTotal(STAT num) const
        {
            if (num > STAT::LUCK) {
                throw Exception("CritterObject::statTotal(num) - num out of range:" + std::to_string((unsigned)num));
            }
            return stat(num) + statBonus(num);
        }

        int CritterObject::statBonus(STAT num) const
        {
            if (num > STAT::LUCK) {
                throw Exception("CritterObject::statBonus(num) - num out of range:" + std::to_string((unsigned)num));
            }
            int bonus = 0;
            if (traitTagged(TRAIT::GIFTED)) {
                bonus += 1;
            }
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
            if (num > STAT::LUCK) {
                throw Exception("CritterObject::setStatBonus(num, value) - num out of range:" + std::to_string((unsigned)num));
            }
            _statsBonus.at((unsigned)num) = value;
        }

        int CritterObject::skillTagged(SKILL num) const
        {
            if (num > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::skillTagged(num) - num out of range:" + std::to_string((unsigned)num));
            }
            return _skillsTagged.at((unsigned)num);
        }

        void CritterObject::setSkillTagged(SKILL num, int value)
        {
            if (num > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::setSkillTagged(num, value) - num out of range:" + std::to_string((unsigned)num));
            }
            _skillsTagged.at((unsigned)num) = value;
        }

        int CritterObject::skillBaseValue(SKILL skill) const
        {
            if (skill > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::skillBaseValue(num) - num out of range:" + std::to_string((unsigned)skill));
            }
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

            if (traitTagged(TRAIT::GIFTED)) {
                value -= 10;
            }

            if (skillTagged(skill)) {
                value += 20;
            }

            return value;
        }

        int CritterObject::traitTagged(TRAIT num) const
        {
            if (num > TRAIT::GIFTED) {
                throw Exception("CritterObject::traitTagged(num) - num out of range:" + std::to_string((unsigned)num));
            }
            return _traitsTagged.at((unsigned)num);
        }

        void CritterObject::setTraitTagged(TRAIT num, int value)
        {
            if (num > TRAIT::GIFTED) {
                throw Exception("CritterObject::setTraitTagged(num, value) - num out of range:" + std::to_string((unsigned)num));
            }
            _traitsTagged.at((unsigned)num) = value;
        }

        void CritterObject::setCritterFlags(unsigned int flags)
        {
            setCanTrade((flags & 0x00000002));
            setCanStealFrom((flags & 0x00000020));
            setCanDropItems((flags & 0x00000040));
            setCanLoseLimbs((flags & 0x00000080));
            setCanAge((flags & 0x00000100));
            setCanHeal((flags & 0x00000200));
            setInvulnerable((flags & 0x00000400));
            setLeavesBody((flags & 0x00000800));
            setHasSpecialDeath((flags & 0x00001000));
            setHasMeleeRange((flags & 0x00002000));
            setCanKnockdown((flags & 0x00004000));
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
            for (auto item : _inventory) {
                weight += item->weight();
            }

            if (auto armor = dynamic_cast<ItemObject*>(armorSlot())) {
                weight += armor->weight();
            }

            if (auto leftHand = dynamic_cast<ItemObject*>(leftHandSlot())) {
                weight += leftHand->weight();
            }

            if (auto rightHand = dynamic_cast<ItemObject*>(rightHandSlot())) {
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
            if (type > DAMAGE::POISON) {
                throw Exception("CritterObject::damageResist(type) - type out of range: " + std::to_string((unsigned)type));
            }
            return _damageResist.at((unsigned)type);
        }

        void CritterObject::setDamageResist(DAMAGE type, int value)
        {
            if (type > DAMAGE::POISON) {
                throw Exception("CritterObject::setDamageResist(type, value) - type out of range: " + std::to_string((unsigned)type));
            }
            _damageResist.at((unsigned)type) = value;
        }

        int CritterObject::damageThreshold(DAMAGE type) const
        {
            if ( type > DAMAGE::POISON) {
                throw Exception("CritterObject::damageThreshold(type) - type out of range: " + std::to_string((unsigned)type));
            }
            return _damageThreshold.at((unsigned)type);
        }

        void CritterObject::setDamageThreshold(DAMAGE type, int value)
        {
            if ( type > DAMAGE::POISON) {
                throw Exception("CritterObject::setDamageThreshold(type, value) - type out of range: " + std::to_string((unsigned)type));
            }
            _damageThreshold.at((unsigned)type) = value;
        }

        HAND CritterObject::currentHand() const
        {
            return _currentHand;
        }

        void CritterObject::setCurrentHand(HAND value)
        {
            if (value > HAND::LEFT) {
                throw Exception("CritterObject::setCurrentHand(value) - value out of range: " + std::to_string((unsigned)value));
            }
            _currentHand = value;
        }

        ItemObject* CritterObject::currentHandSlot() const
        {
            return currentHand() == HAND::RIGHT ? rightHandSlot() : leftHandSlot();
        }

        void CritterObject::talk_p_proc()
        {
            if (_script && _script->hasFunction("talk_p_proc")) {
                _script
                    ->setSourceObject(Game::getInstance()->player().get())
                    ->call("talk_p_proc")
                ;
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
            if (_script && _script->hasFunction("critter_p_proc")) {
                _script->call("critter_p_proc");
            }
        }

        void CritterObject::is_dropping_p_proc()
        {
        }

        void CritterObject::use_skill_on_p_proc()
        {
        }

        // TODO: probably need to remove movement queue logic to separate class.
        vector<Hexagon*>* CritterObject::movementQueue()
        {
            return &_movementQueue;
        }

        void CritterObject::think()
        {
            if (!movementQueue()->empty()) {
                if (!_moving) {
                    _moving = true;

                    _orientation = hexagon()->orientationTo(movementQueue()->back());
                    auto animation = _generateMovementAnimation();
                    animation->frameHandler().add(bind(&CritterObject::onMovementAnimationFrame, this, placeholders::_1));
                    animation->animationEndedHandler().add(bind(&CritterObject::onMovementAnimationEnded, this, placeholders::_1));
                    animation->play();
                    _ui = move(animation);
                }
            } else {
                auto anim = (UI::Animation*)ui();
                if (!_moving && (!anim || !anim->playing())) {
                    if (SDL_GetTicks() > _nextIdleAnim) {
                        setActionAnimation("aa");
                        _setupNextIdleAnim();
                    }
                }
            }
            Object::think();
        }

        static const std::array<int, 6> xTileOffsets = {{16, 32, 16, -16, -32, -16}};
        static const std::array<int, 6> yTileOffsets = {{-12, 0, 12,  12,   0, -12}};

        // TODO: move somewhere appropriate
        bool isOutsideOfHexForDirection(Point offset, Orientation orient)
        {
            int xThreshold = xTileOffsets[orient];
            int yThreshold = yTileOffsets[orient];
            return (xThreshold > 0 && offset.x() >= xThreshold)
                || (xThreshold < 0 && offset.x() <= xThreshold)
                || (yThreshold > 0 && offset.y() >= yThreshold)
                || (yThreshold < 0 && offset.y() <= yThreshold);
        }

        // TODO: refactor
        // I suggest processing all frames beforehand - adjusting positions to remain within hex boundaries
        // and defining "action frames" (multiple frames per animation). This will allow to re-use Animation object
        // for different animation cycles.
        void CritterObject::onMovementAnimationFrame(Event::Event* event)
        {
            auto animation = dynamic_cast<UI::Animation*>(ui());
            auto curFrameOfs = animation->frameOffset();
            if (isOutsideOfHexForDirection(curFrameOfs, _orientation)) {
                // if we stepped too much away from current hex center, switch to the next hex
                auto moveQueue = movementQueue();
                if (!moveQueue->empty()) {
                    auto hexagon = moveQueue->back();
                    moveQueue->pop_back();
                    Game::getInstance()->locationState()->moveObjectToHexagon(this, hexagon);

                    // This hack is needed for prevent game crash when player goes to the
                    // exit tile and location is changed but movement is not finished
                    for (auto object : *hexagon->objects()) {
                        if (dynamic_cast<ExitMiscObject*>(object)) {
                            moveQueue->clear();
                            break;
                        }
                    }
                }
                if (moveQueue->empty()) {
                    _moving = false;
                    animation->stop();
                    setActionAnimation("aa")->stop();
                    _setupNextIdleAnim();
                } else {
                    auto nextHexagon = moveQueue->back();
                    auto nextOrientation = this->hexagon()->orientationTo(nextHexagon);
                    Point ofs;
                    if (nextOrientation != _orientation) {
                        _orientation = nextOrientation;
                        auto newAnimation = _generateMovementAnimation();
                        newAnimation->setCurrentFrame(animation->currentFrame());
                        newAnimation->frameHandler().add(bind(&CritterObject::onMovementAnimationFrame, this, placeholders::_1));
                        newAnimation->animationEndedHandler().add(bind(&CritterObject::onMovementAnimationEnded, this, placeholders::_1));
                        newAnimation->play();
                        animation = newAnimation.get();
                        _ui = move(newAnimation);
                        curFrameOfs = animation->frameOffset();

                        // on turns, center frames on current hex
                        ofs -= curFrameOfs;
                    } else {
                        ofs -= Point(xTileOffsets[_orientation], yTileOffsets[_orientation]);
                    }
                    animation->setOffset(animation->offset() + ofs);
                }
            }
        }

        void CritterObject::onMovementAnimationEnded(Event::Event* event)
        {
            auto animation = dynamic_cast<UI::Animation*>(ui());
            if (!animation) throw Exception("UI::Animation expected!");
            // get offset of the last frame
            Point lastFrameOfs = animation->offset() + animation->currentFramePtr()->offset();
            animation->setCurrentFrame(0);
            animation->setOffset(lastFrameOfs);
            animation->play();
        }

        unique_ptr<UI::Animation> CritterObject::_generateMovementAnimation()
        {
            CritterAnimationHelper critterAnimationHelper;

            string frmString = _generateArmorFrmString();

            unsigned weaponId = WEAPON_NONE;
            if (auto weapon = dynamic_cast<WeaponItemObject*>(currentHandSlot())) {
                weaponId = weapon->animationCode();
            }

            unsigned animationId = _running ? ANIM_RUNNING : ANIM_WALK;

            frmString += critterAnimationHelper.getSuffix(animationId, weaponId);

            return std::make_unique<UI::Animation>("art/critters/" + frmString + ".frm", orientation());
        }

        UI::Animation* CritterObject::setActionAnimation(const string& action)
        {
            auto animation = generateAnimation(action, orientation());
            animation->play();
            setUI(animation);
            return animation;
        }

        UI::Animation* CritterObject::generateAnimation(const string& action, Orientation orientation)
        {
            string animName = _generateArmorFrmString();

            unsigned weaponId = WEAPON_NONE;
            if (auto weapon = dynamic_cast<WeaponItemObject*>(currentHandSlot())) {
                weaponId = weapon->animationCode();
            }

            if (action == "aa") {
                CritterAnimationHelper critterAnimationHelper;
                animName += critterAnimationHelper.getSuffix(ANIM_STAND, weaponId);
            } else {
                animName += action;
            }

            UI::Animation* animation = new UI::Animation("art/critters/" + animName + ".frm", orientation);
            animation->animationEndedHandler().add([animation](Event::Event* event) {
                animation->setCurrentFrame(0);
            });
            return animation;
        }

        bool CritterObject::canTrade() const
        {
            return _canTrade;
        }

        void CritterObject::setCanTrade(bool canTrade)
        {
            _canTrade = canTrade;
        }

        bool CritterObject::canStealFrom() const
        {
            return _canStealFrom;
        }

        void CritterObject::setCanStealFrom(bool canStealFrom)
        {
            _canStealFrom = canStealFrom;
        }

        bool CritterObject::canDropItems() const
        {
            return _canDropItems;
        }

        void CritterObject::setCanDropItems(bool canDropItems)
        {
            _canDropItems = canDropItems;
        }

        bool CritterObject::canLoseLimbs() const
        {
            return _canLoseLimbs;
        }

        void CritterObject::setCanLoseLimbs(bool canLoseLimbs)
        {
            _canLoseLimbs = canLoseLimbs;
        }

        bool CritterObject::canAge() const
        {
            return _canAge;
        }

        void CritterObject::setCanAge(bool canAge)
        {
            _canAge = canAge;
        }

        bool CritterObject::canHeal() const
        {
            return _canHeal;
        }

        void CritterObject::setCanHeal(bool canHeal)
        {
            _canHeal = canHeal;
        }

        bool CritterObject::invulnerable() const
        {
            return _invulnerable;
        }

        void CritterObject::setInvulnerable(bool invulnerable)
        {
            _invulnerable = invulnerable;
        }

        bool CritterObject::leavesBody() const
        {
            return _leavesBody;
        }

        void CritterObject::setLeavesBody(bool leavesBody)
        {
            _leavesBody = leavesBody;
        }

        bool CritterObject::hasSpecialDeath() const
        {
            return _hasSpecialDeath;
        }

        void CritterObject::setHasSpecialDeath(bool hasSpecialDeath)
        {
            _hasSpecialDeath = hasSpecialDeath;
        }

        bool CritterObject::hasMeleeRange() const
        {
            return _hasMeleeRange;
        }

        void CritterObject::setHasMeleeRange(bool hasMeleeRange)
        {
            _hasMeleeRange = hasMeleeRange;
        }

        bool CritterObject::canKnockdown() const
        {
            return _canKnockdown;
        }

        void CritterObject::setCanKnockdown(bool knockdown)
        {
            _canKnockdown = knockdown;
        }

        UI::Animation* CritterObject::setWeaponAnimation(unsigned animationId)
        {
            unsigned weaponId = WEAPON_NONE;
            if (auto weapon = dynamic_cast<WeaponItemObject*>(currentHandSlot())) {
                weaponId = weapon->animationCode();
            }

            CritterAnimationHelper critterAnimationHelper;
            auto anim = setActionAnimation(critterAnimationHelper.getSuffix(animationId, weaponId));
            anim->animationEndedHandler().add([this](Event::Event* evt) {
                setActionAnimation("aa")->stop();
            });
            return anim;
        }

        void CritterObject::_generateUi()
        {
            setActionAnimation("aa")->stop();
        }

        void CritterObject::setRadiationLevel(int radiationLevel)
        {
            this->_radiationLevel = radiationLevel;
        }

        int CritterObject::radiationLevel() const
        {
            return _radiationLevel;
        }

        string CritterObject::_generateArmorFrmString()
        {
            CritterAnimationHelper critterAnimationHelper;

            if (!armorSlot()) {
                return critterAnimationHelper.getPrefix(FID());
            }

            if (gender() == GENDER::FEMALE) {
                return critterAnimationHelper.getPrefix(armorSlot()->femaleFID());
            }

            return critterAnimationHelper.getPrefix(armorSlot()->maleFID());
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
            if (skill > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::skillValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
            }
            return skillBaseValue(skill) + skillGainedValue(skill);
        }

        int CritterObject::skillGainedValue(SKILL skill) const
        {
            if (skill > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::skillGainedValue(skill) - skill out of range:" + std::to_string((unsigned)skill));
            }
            return _skillsGainedValue.at((unsigned)skill);
        }

        void CritterObject::setSkillGainedValue(SKILL skill, int value)
        {
            if (skill > SKILL::OUTDOORSMAN) {
                throw Exception("CritterObject::setSkillGainedCalue(skill) - skill out of range:" + std::to_string((unsigned)skill));
            }
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
            if (auto animation = dynamic_cast<UI::Animation*>(_ui.get())) {
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

        UI::Animation* CritterObject::animation()
        {
            return dynamic_cast<UI::Animation*>(ui());
        }
    }
}
