/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef FALLTERGEIST_FORMAT_GCD_FILE_H
#define FALLTERGEIST_FORMAT_GCD_FILE_H

// C++ standard includes
#include <string>
#include <vector>

// Falltergeist includes
#include "../../Format/Dat/Item.h"
#include "../../Format/Enums.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Gcd
{

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);

    void setStat(STAT number, uint32_t value);
    uint32_t stat(STAT number) const;

    void setStatBonus(STAT number, uint32_t value);
    uint32_t statBonus(STAT number) const;

    void setSkill(SKILL number, uint32_t value);
    uint32_t skill(SKILL number) const;

    void setDamage(DAMAGE type, uint32_t value);
    uint32_t damage(DAMAGE type) const;

    void setDamageBonus(DAMAGE type, uint32_t value);
    uint32_t damageBonus(DAMAGE type) const;

    void setResistance(DAMAGE type, uint32_t value);
    uint32_t resistance(DAMAGE type) const;

    void setResistanceBonus(DAMAGE type, uint32_t value);
    uint32_t resistanceBonus(DAMAGE type) const;

    void setHitPoints(uint32_t hitPoints);
    uint32_t hitPoints() const;

    void setActionPoints(uint32_t actionPoints);
    uint32_t actionPoints() const;

    void setArmorClass(uint32_t armorClass);
    uint32_t armorClass() const;

    void setMeleeDamage(uint32_t meleeDamage);
    uint32_t meleeDamage() const;

    void setCarryWeight(uint32_t carryWeight);
    uint32_t carryWeight() const;

    void setSequence(uint32_t sequence);
    uint32_t sequence() const;

    void setHealingRate(uint32_t healingRate);
    uint32_t healingRate() const;

    void setCriticalChance(uint32_t criticalChance);
    uint32_t criticalChance() const;

    void setCriticalHitModifier(uint32_t criticalHitModifier);
    uint32_t criticalHitModifier() const;

    void setRadiationResistance(uint32_t radiationResistance);
    uint32_t radiationResistance() const;

    void setPoisonResistance(uint32_t poisonResistance);
    uint32_t poisonResistance() const;

    void setAge(uint32_t age);
    uint32_t age() const;

    void setGender(GENDER gender);
    GENDER gender() const;

    // bonuses to secondaty stats
    void setHitPointsBonus(uint32_t hitPointsBonus);
    uint32_t hitPointsBonus() const;

    void setActionPointsBonus(uint32_t actionPointsBonus);
    uint32_t actionPointsBonus() const;

    void setArmorClassBonus(uint32_t armorClassBonus);
    uint32_t armorClassBonus() const;

    //uint32_t unknownBonus;

    void setMeleeDamageBonus(uint32_t meleeDamageBonus);
    uint32_t meleeDamageBonus() const;

    void setCarryWeightBonus(uint32_t carryWeightBonus);
    uint32_t carryWeightBonus() const;

    void setSequenceBonus(uint32_t sequenceBonus);
    uint32_t sequenceBonus() const;

    void setHealingRateBonus(uint32_t healingRateBonus);
    uint32_t healingRateBonus() const;

    void setCriticalChanceBonus(uint32_t criticalChanceBonus);
    uint32_t criticalChanceBonus() const;

    void setCriticalHitModifierBonus(uint32_t criticalHitModifierBonus);
    uint32_t criticalHitModifierBonus() const;

    void setRadiationResistanceBonus(uint32_t radiationResistanceBonus);
    uint32_t radiationResistanceBonus() const;

    void setPoisonResistanceBonus(uint32_t poisonResistanceBonus);
    uint32_t poisonResistanceBonus() const;

    void setAgeBonus(uint32_t ageBonus);
    uint32_t ageBonus() const;

    void setGenderBonus(uint32_t genderBonus);
    uint32_t genderBonus() const;

    void setName(std::string name);
    std::string name() const;

    void setFirstTaggedSkill(SKILL firstTaggedSkill);
    SKILL firstTaggedSkill() const;

    void setSecondTaggedSkill(SKILL secondTaggedSkill);
    SKILL secondTaggedSkill() const;

    void setThirdTaggedSkill(SKILL thirdTaggedSkill);
    SKILL thirdTaggedSkill() const;

    void setFourthTaggedSkill(SKILL fourthTaggedSkill);
    SKILL fourthTaggedSkill() const;

    void setFirstTrait(TRAIT firstTrait);
    TRAIT firstTrait() const;

    void setSecondTrait(TRAIT secondTrait);
    TRAIT secondTrait() const;

    void setCharacterPoints(uint32_t characterPoints);
    uint32_t characterPoints() const;

protected:
    // primary stats
    std::vector<uint32_t> _stats = {0, 0, 0, 0, 0, 0, 0};
    // bonuses to primary stats
    std::vector<uint32_t> _statsBonus = {0, 0, 0, 0, 0, 0, 0};
    // skills
    std::vector<uint32_t> _skills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // damage
    std::vector<uint32_t> _damage = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _damageBonus = {0, 0, 0, 0, 0, 0, 0};
    // resistance
    std::vector<uint32_t> _resistance = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _resistanceBonus = {0, 0, 0, 0, 0, 0, 0};

    // secondary stats
    uint32_t _hitPoints;
    uint32_t _actionPoints;
    uint32_t _armorClass;
    uint32_t _meleeDamage;
    uint32_t  _carryWeight;

    uint32_t _sequence;
    uint32_t _healingRate;
    uint32_t _criticalChance;
    uint32_t _criticalHitModifier;
    uint32_t _radiationResistance;
    uint32_t _poisonResistance;
    uint32_t _age;
    GENDER _gender;
    // bonuses to secondaty stats
    uint32_t _hitPointsBonus;
    uint32_t _actionPointsBonus;
    uint32_t _armorClassBonus;
    //uint32_t unknownBonus;
    uint32_t _meleeDamageBonus;
    uint32_t _carryWeightBonus;
    uint32_t _sequenceBonus;
    uint32_t _healingRateBonus;
    uint32_t _criticalChanceBonus;
    uint32_t _criticalHitModifierBonus;
    uint32_t _radiationResistanceBonus;
    uint32_t _poisonResistanceBonus;
    uint32_t _ageBonus;
    uint32_t _genderBonus;

    std::string _name;

    SKILL _firstTaggedSkill  = SKILL::NONE;
    SKILL _secondTaggedSkill = SKILL::NONE;
    SKILL _thirdTaggedSkill  = SKILL::NONE;
    SKILL _fourthTaggedSkill = SKILL::NONE;
    TRAIT _firstTrait  = TRAIT::NONE;
    TRAIT _secondTrait = TRAIT::NONE;

    uint32_t _characterPoints;
};

}
}
}
#endif // FALLTERGEIST_FORMAT_GCD_FILE_H
