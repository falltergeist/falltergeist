// Project includes
#include "../Game/CritterObject.h"
#include "../Exception.h"
#include "../Game/ArmorItemObject.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/ExitMiscObject.h"
#include "../Game/Game.h"
#include "../Game/WeaponItemObject.h"
#include "../Helpers/CritterHelper.h"
#include "../Graphics/CritterAnimationFactory.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../UI/AnimationFrame.h"
#include "../UI/TextArea.h"

// Third-party includes

// stdlib
#include <array>
#include <string>
#include <memory>

namespace Falltergeist
{
    namespace Game
    {
        CritterObject::CritterObject(
            std::shared_ptr<ISkillCollection> skillCollection,
            std::shared_ptr<IStatCollection> statCollection,
            std::shared_ptr<ITraitCollection> traitCollection
        ) : Object(), _skillCollection(skillCollection), _statCollection(statCollection), _traitCollection(traitCollection) {
            _type = Type::CRITTER;
            _setupNextIdleAnim();
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

        std::shared_ptr<ISkillCollection> CritterObject::skillCollection() const {
            return _skillCollection;
        }

        std::shared_ptr<IStatCollection> CritterObject::statCollection() const {
            return _statCollection;
        }

        std::shared_ptr<ITraitCollection> CritterObject::traitCollection() const {
            return _traitCollection;
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

        void CritterObject::use_skill_on_p_proc(SKILL skill, Object* objectUsed, CritterObject* usedBy)
        {
        }

        // TODO: probably need to remove movement queue logic to separate class.
        std::vector<Hexagon*>* CritterObject::movementQueue()
        {
            return &_movementQueue;
        }

        void CritterObject::think(const float &deltaTime)
        {
            if (!movementQueue()->empty()) {
                if (!_moving) {
                    _moving = true;

                    _orientation = hexagon()->orientationTo(movementQueue()->back());
                    auto animation = _generateMovementAnimation();
                    animation->frameHandler().add(std::bind(&CritterObject::onMovementAnimationFrame, this, std::placeholders::_1));
                    animation->animationEndedHandler().add(std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
                    animation->play();
                    _ui = std::move(animation);
                }
            } else {
                auto anim = ui<UI::Animation>();
                if (!_moving && (!anim || !anim->playing())) {
                    if (SDL_GetTicks() > _nextIdleAnim) {
                        setActionAnimation("aa");
                        _setupNextIdleAnim();
                    }
                }
            }
            Object::think(deltaTime);
        }

        static const std::array<int, 6> xTileOffsets = {{16, 32, 16, -16, -32, -16}};
        static const std::array<int, 6> yTileOffsets = {{-12, 0, 12,  12,   0, -12}};

        // TODO: move somewhere appropriate
        bool isOutsideOfHexForDirection(Graphics::Point offset, Orientation orient)
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
            auto animation = ui<UI::Animation>();
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
                    Graphics::Point ofs;
                    if (nextOrientation != _orientation) {
                        _orientation = nextOrientation;
                        auto newAnimation = _generateMovementAnimation();
                        newAnimation->setCurrentFrame(animation->currentFrame());
                        newAnimation->frameHandler().add(std::bind(&CritterObject::onMovementAnimationFrame, this, std::placeholders::_1));
                        newAnimation->animationEndedHandler().add(std::bind(&CritterObject::onMovementAnimationEnded, this, std::placeholders::_1));
                        newAnimation->play();
                        animation = newAnimation;
                        _ui = newAnimation;
                        curFrameOfs = animation->frameOffset();

                        // on turns, center frames on current hex
                        ofs -= curFrameOfs;
                    } else {
                        ofs -= Graphics::Point(xTileOffsets[_orientation], yTileOffsets[_orientation]);
                    }
                    animation->setOffset(animation->offset() + ofs);
                }
            }
        }

        void CritterObject::onMovementAnimationEnded(Event::Event* event)
        {
            auto animation = ui<UI::Animation>();
            if (!animation) {
                throw Exception("UI::Animation expected!");
            }
            // get offset of the last frame
            Graphics::Point lastFrameOfs = animation->offset() + animation->currentFramePtr()->offset();
            animation->setCurrentFrame(0);
            animation->setOffset(lastFrameOfs);
            animation->play();
        }

        std::shared_ptr<UI::Animation> CritterObject::_generateMovementAnimation()
        {
            Graphics::CritterAnimationFactory animationFactory;
            Helpers::CritterHelper critterHelper;

            if (_running) {
                return animationFactory.buildRunningAnimation(
                    critterHelper.armorFID(this),
                    critterHelper.weaponId(this),
                    orientation()
                );
            }

            return animationFactory.buildWalkingAnimation(
                critterHelper.armorFID(this),
                critterHelper.weaponId(this),
                orientation()
            );
        }

        std::shared_ptr<UI::Animation> CritterObject::setActionAnimation(const std::string& action)
        {
            Graphics::CritterAnimationFactory animationFactory;
            Helpers::CritterHelper critterHelper;

            auto animation = animationFactory.buildActionAnimation(
                critterHelper.armorFID(this),
                critterHelper.weaponId(this),
                action,
                orientation()
            );
            animation->play();
            _ui = animation;
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

        std::shared_ptr<UI::Animation> CritterObject::setWeaponAnimation(unsigned animationId)
        {
            Helpers::CritterHelper critterHelper;
            Graphics::CritterAnimationFactory animationFactory;
            auto animation = animationFactory.buildActionAnimation(
                critterHelper.armorFID(this),
                critterHelper.weaponId(this),
                animationId,
                orientation()
            );
            return animation;
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

        int CritterObject::poisonLevel() const
        {
            return _poisonLevel;
        }

        void CritterObject::setPoisonLevel(int value)
        {
            _poisonLevel = value;
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

        std::shared_ptr<UI::Animation> CritterObject::animation() {
            return std::dynamic_pointer_cast<UI::Animation>(ui());
        }
    }
}
