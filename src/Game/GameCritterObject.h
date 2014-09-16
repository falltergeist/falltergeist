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
 *
 */

#ifndef FALLTERGEIST_GAMECRITTEROBJECT_H
#define FALLTERGEIST_GAMECRITTEROBJECT_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Game/GameObject.h"
#include "../Game/GameArmorItemObject.h"

// Third party includes

namespace Falltergeist
{
class GameItemObject;

class GameCritterObject : public GameObject
{
protected:
    int _gender;
    int _hitPoints = 0;
    int _hitPointsMax = 0;
    int _healingRate = 0;
    int _armorClass = 0;
    int _actionPoints = 0;
    int _carryWeight = 0;
    int _meleeDamage = 0;
    int _sequence = 0;
    int _criticalChance = 0;

    std::vector<int> _stats = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _statsBonus = {0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _skills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _traits = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<std::shared_ptr<GameItemObject>> _inventory;
    std::shared_ptr<GameArmorItemObject> _armorSlot;
    std::shared_ptr<GameItemObject> _leftHandSlot;
    std::shared_ptr<GameItemObject> _rightHandSlot;
public:
    enum { GENDER_MALE = 0, GENDER_FEMALE = 1 };
    enum { STATS_STRENGTH = 0, STATS_PERCEPTION, STATS_ENDURANCE, STATS_CHARISMA, STATS_INTELLIGENCE, STATS_AGILITY, STATS_LUCK };
    enum { DAMAGE_NORMAL = 0, DAMAGE_LASER, DAMAGE_FIRE, DAMAGE_PLASMA, DAMAGE_ELECTRICAL, DAMAGE_EMP, DAMAGE_EXPLOSION, DAMAGE_RADIATION, DAMAGE_POISON };
    enum { TRAITS_1 = 0, // Fast Metabolism
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
    enum { TRAITS_FAST_METABOLISM = 0,
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
    enum { SKILLS_1 = 0, // Small Guns
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
    enum { SKILLS_SMALL_GUNS = 0,
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

    std::vector<std::shared_ptr<GameItemObject>>* inventory();
    virtual void setOrientation(int value);

    std::shared_ptr<GameArmorItemObject> armorSlot();
    void setArmorSlot(std::shared_ptr<GameArmorItemObject> object);

    std::shared_ptr<GameItemObject> leftHandSlot();
    void setLeftHandSlot(std::shared_ptr<GameItemObject> object);

    std::shared_ptr<GameItemObject> rightHandSlot();
    void setRightHandSlot(std::shared_ptr<GameItemObject> object);

    int gender();
    void setGender(unsigned int value);

    int stat(unsigned int num);
    void setStat(unsigned int num, int value);

    int statBonus(unsigned int num);
    void setStatBonus(unsigned int num, int value);

    int statTotal(unsigned int num);

    int skill(unsigned int num);
    void setSkill(unsigned int num, int value);   

    int skillValue(unsigned int num);

    int trait(unsigned int num);
    void setTrait(unsigned int num, int value);

    int hitPoints();
    void setHitPoints(int value);

    virtual int hitPointsMax();
    void setHitPointsMax(int value);

    virtual int armorClass();
    void setArmorClass(int value);

    virtual int actionPoints();
    void setActionPoints(int value);

    virtual int carryWeight();
    void setCarryWeight(int value);

    virtual int meleeDamage();
    void setMeleeDamage(int value);

    virtual int sequence();
    void setSequence(int value);

    virtual int criticalChance();
    void setCriticalChance(int value);

    virtual int healingRate();
    void setHealingRate(int value);

    virtual int damageResist(unsigned int type);
    void setDamageResist(unsigned int type, int value);

    virtual int damageThreshold(unsigned int type);
    void setDamageThreshold(unsigned int type, int value);

};

}
#endif // FALLTERGEIST_GAMECRITTEROBJECT_H
