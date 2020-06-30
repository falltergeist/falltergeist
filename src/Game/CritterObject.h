#pragma once

#include <vector>
#include "../Format/Enums.h"
#include "../Game/Object.h"

namespace Falltergeist
{
    namespace UI
    {
        class Animation;
    }

    namespace Game
    {
        class ArmorItemObject;
        class ItemObject;

        /**
         * Critter refers to player, all NPCs, creatures, robots, etc - all movable and shootable objects.
         */
        class CritterObject : public Object, public std::enable_shared_from_this<CritterObject>
        {
            public:

                CritterObject();
                ~CritterObject() = default;

                std::vector<std::shared_ptr<ItemObject>>* inventory(); // critter's own inventory
                void setOrientation(Orientation value) override;

                std::vector<std::shared_ptr<Hexagon>>* movementQueue();

                const std::shared_ptr<ArmorItemObject> &armorSlot() const;
                void setArmorSlot(const std::shared_ptr<ArmorItemObject> &object);

                const std::shared_ptr<ItemObject> &leftHandSlot() const;
                void setLeftHandSlot(const std::shared_ptr<ItemObject> &object);

                const std::shared_ptr<ItemObject> &rightHandSlot() const;
                void setRightHandSlot(const std::shared_ptr<ItemObject> &object);

                const std::shared_ptr<ItemObject> &currentHandSlot() const;

                GENDER gender() const;
                void setGender(GENDER value);

                unsigned age() const;
                void setAge(unsigned value);

                int stat(STAT stat) const;
                void setStat(STAT stat, int value);

                int statBonus(STAT stat) const;
                void setStatBonus(STAT stat, int value);

                // returns total stat value (with bonuses)
                int statTotal(STAT num) const;

                int skillTagged(SKILL skill) const;
                void setSkillTagged(SKILL skill, int value);

                int skillBaseValue(SKILL skill) const;
                int skillGainedValue(SKILL skill) const;
                void setSkillGainedValue(SKILL skill, int value);
                int skillValue(SKILL skill) const;

                int traitTagged(TRAIT num) const;
                void setTraitTagged(TRAIT num, int value);

                void setCritterFlags(unsigned int flags);

                int hitPoints() const;
                void setHitPoints(int value);

                virtual int hitPointsMax() const;
                void setHitPointsMax(int value);

                virtual int armorClass() const;
                void setArmorClass(int value);

                virtual int actionPoints() const;
                void setActionPoints(int value);

                virtual int actionPointsMax() const;
                void setActionPointsMax(int value);

                virtual unsigned int carryWeight() const;
                virtual unsigned int carryWeightMax() const;
                void setCarryWeightMax(unsigned int value);

                virtual int meleeDamage() const;
                void setMeleeDamage(int value);

                virtual int sequence() const;
                void setSequence(int value);

                virtual int criticalChance() const;
                void setCriticalChance(int value);

                virtual int healingRate() const;
                void setHealingRate(int value);

                int poisonLevel() const;
                void setPoisonLevel(int value);

                int radiationLevel() const;
                void setRadiationLevel(int radiationLevel);

                virtual int damageResist(DAMAGE type) const;
                void setDamageResist(DAMAGE type, int value);

                virtual int damageThreshold(DAMAGE type) const;
                void setDamageThreshold(DAMAGE type, int value);

                HAND currentHand() const;
                void setCurrentHand(HAND value);

                virtual void damage_p_proc();
                virtual void combat_p_proc();
                virtual void critter_p_proc();
                virtual void talk_p_proc();
                void use_skill_on_p_proc(SKILL skill, const std::shared_ptr<Object> &objectUsed, const std::shared_ptr<CritterObject> &usedBy) override;
                virtual void is_dropping_p_proc();

                void think(const float &deltaTime) override;
                virtual void onMovementAnimationEnded(Event::Event* event);
                virtual void onMovementAnimationFrame(Event::Event* event);

                virtual bool running() const;
                virtual void setRunning(bool value);

                virtual void stopMovement();

                virtual UI::Animation* setActionAnimation(const std::string& action);
                UI::Animation* setWeaponAnimation(unsigned animationId);

                UI::Animation* animation();

                bool canTrade() const;
                void setCanTrade(bool canTrade);

                bool canStealFrom() const;
                void setCanStealFrom(bool canStealFrom);

                bool canDropItems() const;
                void setCanDropItems(bool canDropItems);

                bool canLoseLimbs() const;
                void setCanLoseLimbs(bool canLoseLimbs);

                bool canAge() const;
                void setCanAge(bool canAge);

                bool canHeal() const;
                void setCanHeal(bool canHeal);

                bool invulnerable() const;
                void setInvulnerable(bool invulnerable);

                bool leavesBody() const;
                void setLeavesBody(bool leavesBody);

                bool hasSpecialDeath() const;
                void setHasSpecialDeath(bool hasSpecialDeath);

                bool hasMeleeRange() const;
                void setHasMeleeRange(bool hasMeleeRange);

                bool canKnockdown() const;
                void setCanKnockdown(bool canKnockdown);

        protected:
                bool _moving  = false;
                bool _running = false;

                GENDER _gender = GENDER::MALE;
                int _poisonLevel = 0;
                int _radiationLevel = 0;
                int _hitPoints = 0;
                int _hitPointsMax = 0;
                int _healingRate = 0;
                int _armorClass = 0;
                int _actionPoints = 0;
                int _actionPointsMax = 0;
                int _meleeDamage = 0;
                int _sequence = 0;
                int _criticalChance = 0;

                bool _canTrade;
                bool _canStealFrom;
                bool _canDropItems;
                bool _canLoseLimbs;
                bool _canAge; // dead body does not disappear
                bool _canHeal; // damage is not healed over time
                bool _invulnerable;
                bool _leavesBody;
                bool _hasSpecialDeath;
                bool _hasMeleeRange; // melee attack is possible at a distance
                bool _canKnockdown; // can be knocked down

                unsigned int _nextIdleAnim = 0;
                unsigned _age = 0;

                HAND _currentHand = HAND::RIGHT;
                unsigned int _carryWeightMax = 0;

                std::vector<int> _stats = {0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _statsBonus = {0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _skillsTagged = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _skillsGainedValue = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _traitsTagged = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
                std::vector<std::shared_ptr<ItemObject>> _inventory;
                std::vector<std::shared_ptr<Hexagon>> _movementQueue;

                std::shared_ptr<ArmorItemObject> _armorSlot;
                std::shared_ptr<ItemObject> _leftHandSlot;
                std::shared_ptr<ItemObject> _rightHandSlot;

                virtual std::unique_ptr<UI::Animation> _generateMovementAnimation();
                void _setupNextIdleAnim();
                void _generateUi() override;
        };
    }
}
