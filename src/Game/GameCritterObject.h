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

#ifndef FALLTERGEIST_GAMECRITTEROBJECT_H
#define FALLTERGEIST_GAMECRITTEROBJECT_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Game/GameObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Engine/PathFinding/Hexagon.h"

// Third party includes

namespace Falltergeist
{
class Animation;
class GameItemObject;

class GameCritterObject : public GameObject
{
protected:
    bool _moving  = false;
    bool _running = false;

    int _gender = GENDER_MALE;
    int _poisonLevel = 0;
    int _hitPoints = 0;
    int _hitPointsMax = 0;
    int _healingRate = 0;
    int _armorClass = 0;
    int _actionPoints = 0;
    int _actionPointsMax = 0;
    int _meleeDamage = 0;
    int _sequence = 0;
    int _criticalChance = 0;

    unsigned int _currentHand = HAND_RIGHT;
    unsigned int _carryWeightMax = 0;

    std::vector<int> _stats = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _statsBonus = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _skillsTagged = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _skillsGainedValue = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _traitsTagged = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<GameItemObject*> _inventory;
    std::vector<Hexagon*> _movementQueue;
    GameArmorItemObject* _armorSlot = 0;
    GameItemObject* _leftHandSlot = 0;
    GameItemObject* _rightHandSlot = 0;

    virtual Animation* _generateMovementAnimation();
    virtual std::string _generateArmorFrmString();
    virtual std::string _generateWeaponFrmString();
public:
    enum { HAND_RIGHT = 0, HAND_LEFT };
    enum { GENDER_MALE = 0, GENDER_FEMALE };
    enum { STATS_STRENGTH = 0, STATS_PERCEPTION, STATS_ENDURANCE, STATS_CHARISMA, STATS_INTELLIGENCE, STATS_AGILITY, STATS_LUCK };
    enum { DAMAGE_NORMAL = 0, DAMAGE_LASER, DAMAGE_FIRE, DAMAGE_PLASMA, DAMAGE_ELECTRICAL, DAMAGE_EMP, DAMAGE_EXPLOSION, DAMAGE_RADIATION, DAMAGE_POISON };
    enum {
            TRAITS_1 = 0, // Fast Metabolism
            TRAITS_2, // Bruiser
            TRAITS_3, // Small Frame
            TRAITS_4, // One Handed
            TRAITS_5, // Finesse
            TRAITS_6, // Kamikaze
            TRAITS_7, // Heavy Handed
            TRAITS_8, // Fast Shot
            TRAITS_9, // Bloody Mess
            TRAITS_10, // Jinxed
            TRAITS_11, // Good Natured
            TRAITS_12, // Chem Reliant
            TRAITS_13, // Chem Resistant
            TRAITS_14, // Sex Appeal
            TRAITS_15, // Skilled
            TRAITS_16  // Gifted
        };
    enum {
            TRAITS_FAST_METABOLISM = 0,
            TRAITS_BRUISER,
            TRAITS_SMALL_FRAME,
            TRAITS_ONE_HANDED,
            TRAITS_FINESSE,
            TRAITS_KAMIKAZE,
            TRAITS_HEAVY_HANDED,
            TRAITS_FAST_SHOT,
            TRAITS_BLOODY_MESS,
            TRAITS_JINXED,
            TRAITS_GOOD_NATURED,
            TRAITS_CHEM_RELIANT,
            TRAITS_CHEM_RESISTANT,
            TRAITS_SEX_APPEAL,
            TRAITS_SKILLED,
            TRAITS_GIFTED
        };
    enum
    {
            SKILLS_1 = 0, // Small Guns
            SKILLS_2, // Big Guns
            SKILLS_3, // Energy Weapons
            SKILLS_4, // Unarmed
            SKILLS_5, // Melee Weapons
            SKILLS_6, // Throwing
            SKILLS_7, // First Aid
            SKILLS_8, // Doctor
            SKILLS_9, // Sneak
            SKILLS_10, // Lockpick
            SKILLS_11, // Steal
            SKILLS_12, // Traps
            SKILLS_13, // Science
            SKILLS_14, // Repair
            SKILLS_15, // Speech
            SKILLS_16, // Barter
            SKILLS_17, // Gambling
            SKILLS_18  // Outdoorsman
        };
    enum
    {
            SKILLS_SMALL_GUNS = 0,
            SKILLS_BIG_GUNS,
            SKILLS_ENERGY_WEAPONS,
            SKILLS_UNARMED,
            SKILLS_MELEE_WEAPONS,
            SKILLS_THROWING,
            SKILLS_FIRST_AID,
            SKILLS_DOCTOR,
            SKILLS_SNEAK,
            SKILLS_LOCKPICK,
            SKILLS_STEAL,
            SKILLS_TRAPS,
            SKILLS_SCIENCE,
            SKILLS_REPAIR,
            SKILLS_SPEECH,
            SKILLS_BARTER,
            SKILLS_GAMBLING,
            SKILLS_OUTDOORSMAN
    };

    GameCritterObject();
    virtual ~GameCritterObject();

    std::vector<GameItemObject*>* inventory();
    virtual void setOrientation(int value);

    std::vector<Hexagon*>* movementQueue();

    GameArmorItemObject* armorSlot();
    void setArmorSlot(GameArmorItemObject* object);

    GameItemObject* leftHandSlot();
    void setLeftHandSlot(GameItemObject* object);

    GameItemObject* rightHandSlot();
    void setRightHandSlot(GameItemObject* object);

    GameItemObject* currentHandSlot();

    int gender();
    void setGender(unsigned int value);

    int stat(unsigned int stat);
    void setStat(unsigned int stat, int value);

    int statBonus(unsigned int stat);
    void setStatBonus(unsigned int stat, int value);

    int statTotal(unsigned int num);

    int skillTagged(unsigned int skill);
    void setSkillTagged(unsigned int skill, int value);

    int skillBaseValue(unsigned int skill);
    int skillGainedValue(unsigned int skill);
    void setSkillGainedValue(unsigned int skill, int value);
    int skillValue(unsigned int skill);

    int traitTagged(unsigned int num);
    void setTraitTagged(unsigned int num, int value);

    int hitPoints();
    void setHitPoints(int value);

    virtual int hitPointsMax();
    void setHitPointsMax(int value);

    virtual int armorClass();
    void setArmorClass(int value);

    virtual int actionPoints();
    void setActionPoints(int value);

    virtual int actionPointsMax();
    void setActionPointsMax(int value);

    virtual unsigned int carryWeight();
    virtual unsigned int carryWeightMax();
    void setCarryWeightMax(unsigned int value);

    virtual int meleeDamage();
    void setMeleeDamage(int value);

    virtual int sequence();
    void setSequence(int value);

    virtual int criticalChance();
    void setCriticalChance(int value);

    virtual int healingRate();
    void setHealingRate(int value);

    int poisonLevel();
    void setPoisonLevel(int value);

    virtual int damageResist(unsigned int type);
    void setDamageResist(unsigned int type, int value);

    virtual int damageThreshold(unsigned int type);
    void setDamageThreshold(unsigned int type, int value);

    unsigned int currentHand();
    void setCurrentHand(unsigned int value);

    virtual void damage_p_proc();
    virtual void combat_p_proc();
    virtual void critter_p_proc();
    virtual void talk_p_proc();
    virtual void use_skill_on_p_proc();
    virtual void is_dropping_p_proc();

    virtual void think();
    virtual void onMovementAnimationEnded(Event* event);

    virtual bool running();
    virtual void setRunning(bool value);

    virtual Animation* setActionAnimation(std::string action);
};

}
#endif // FALLTERGEIST_GAMECRITTEROBJECT_H
