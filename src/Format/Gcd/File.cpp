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

// C++ standard includes

// Falltergeist includes
#include "../../Exception.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Gcd/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Gcd
{

File::File(Dat::Stream&& stream)
{
    stream.setPosition(0);

    stream.uint32(); // unknown 1

    // primary stats
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        setStat((STAT)i, stream.uint32());
    }

    // secondary stats
    _hitPoints = stream.uint32();
    _actionPoints = stream.uint32();
    _armorClass = stream.uint32();

    stream.uint32(); // unknown 2

    _meleeDamage = stream.uint32();
    _carryWeight = stream.uint32();
    _sequence    = stream.uint32();
    _healingRate = stream.uint32();
    _criticalChance      = stream.uint32();
    _criticalHitModifier = stream.uint32();

    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setDamage((DAMAGE)i, stream.uint32());
    }
    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setResistance((DAMAGE)i, stream.uint32());
    }

    _radiationResistance = stream.uint32();
    _poisonResistance    = stream.uint32();
    _age    = stream.uint32();
    _gender = (GENDER)stream.uint32();

    // bonuses to primary stats
    for (unsigned i = (unsigned)STAT::STRENGTH; i <= (unsigned)STAT::LUCK; i++)
    {
        setStatBonus((STAT)i, stream.uint32());
    }

    // bonuses to secondary stats
    _hitPointsBonus    = stream.uint32();
    _actionPointsBonus = stream.uint32();
    _armorClassBonus   = stream.uint32();

    stream.uint32(); // unknown 3

    _meleeDamageBonus = stream.uint32();
    _carryWeightBonus = stream.uint32();
    _sequenceBonus    = stream.uint32();
    _healingRateBonus = stream.uint32();
    _criticalChanceBonus      = stream.uint32();
    _criticalHitModifierBonus = stream.uint32();

    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setDamageBonus((DAMAGE)i, stream.uint32());
    }
    for (unsigned i = (unsigned)DAMAGE::NORMAL; i <= (unsigned)DAMAGE::EXPLOSIVE; i++)
    {
        setResistanceBonus((DAMAGE)i, stream.uint32());
    }

    _radiationResistanceBonus = stream.uint32();
    _poisonResistanceBonus    = stream.uint32();
    _ageBonus    = stream.uint32();
    _genderBonus = stream.uint32();

    //skills
    for (unsigned i = (unsigned)SKILL::SMALL_GUNS; i <= (unsigned)SKILL::OUTDOORSMAN; i++)
    {
        setSkill((SKILL)i, stream.uint32());
    }

    // unknown
    stream.uint32(); // unknown 4
    stream.uint32(); // unknown 5
    stream.uint32(); // unknown 6
    stream.uint32(); // unknown 7

    // name
    uint8_t name[32];
    stream.readBytes(name, 32);
    setName((char*)name);

    _firstTaggedSkill  = (SKILL)stream.int32();
    _secondTaggedSkill = (SKILL)stream.int32();
    _thirdTaggedSkill  = (SKILL)stream.int32();
    _fourthTaggedSkill = (SKILL)stream.int32();
    _firstTrait  = (TRAIT)stream.int32();
    _secondTrait = (TRAIT)stream.int32();
    _characterPoints = stream.uint32();
}

uint32_t File::stat(STAT number) const
{
    if (number > STAT::LUCK) throw Exception("File::stat() - number out of range: " + std::to_string((unsigned)number));
    return _stats.at((unsigned)number);
}

void File::setStat(STAT number, uint32_t value)
{
    if (number > STAT::LUCK) throw Exception("File::setStat() - number out of range: " + std::to_string((unsigned)number));
    _stats.at((unsigned)number) = value;
}

uint32_t File::statBonus(STAT number) const
{
    if (number > STAT::LUCK) throw Exception("File::statBonus() - number out of range: " + std::to_string((unsigned)number));
    return _statsBonus.at((unsigned)number);
}

void File::setStatBonus(STAT number, uint32_t value)
{
    if (number > STAT::LUCK) throw Exception("File::setStatBonus() - number out of range: " + std::to_string((unsigned)number));
    _statsBonus.at((unsigned)number) = value;
}

uint32_t File::skill(SKILL number) const
{
    if (number > SKILL::OUTDOORSMAN) throw Exception("File::skill() - number out of range: " + std::to_string((unsigned)number));
    return _skills.at((unsigned)number);
}

void File::setSkill(SKILL number, uint32_t value)
{
    if (number > SKILL::OUTDOORSMAN) throw Exception("File::setSkill() - number out of range: " + std::to_string((unsigned)number));
    _skills.at((unsigned)number) = value;
}

uint32_t File::damage(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::damage() - type out of range: " + std::to_string((unsigned)type));
    return _damage.at((unsigned)type);
}

void File::setDamage(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setDamage() - type out of range: " + std::to_string((unsigned)type));
    _damage.at((unsigned)type) = value;
}

uint32_t File::damageBonus(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::damageBonus() - type out of range: " + std::to_string((unsigned)type));
    return _damageBonus.at((unsigned)type);
}

void File::setDamageBonus(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setDamageBonus() - type out of range: " + std::to_string((unsigned)type));
    _damageBonus.at((unsigned)type) = value;
}

uint32_t File::resistance(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::resistance() - type out of range: " + std::to_string((unsigned)type));
    return _resistance.at((unsigned)type);
}

void File::setResistance(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setResistance() - type out of range: " + std::to_string((unsigned)type));
    _resistance.at((unsigned)type) = value;
}

uint32_t File::resistanceBonus(DAMAGE type) const
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::resistanceBonus() - type out of range: " + std::to_string((unsigned)type));
    return _resistanceBonus.at((unsigned)type);
}

void File::setResistanceBonus(DAMAGE type, uint32_t value)
{
    if (type > DAMAGE::EXPLOSIVE) throw Exception("File::setResistanceBonus() - type out of range: " + std::to_string((unsigned)type));
    _resistanceBonus.at((unsigned)type) = value;
}

void File::setHitPoints(uint32_t hitPoints)
{
    _hitPoints = hitPoints;
}

uint32_t File::hitPoints() const
{
    return _hitPoints;
}

void File::setActionPoints(uint32_t actionPoints)
{
    _actionPoints = actionPoints;
}

uint32_t File::actionPoints() const
{
    return _actionPoints;
}

void File::setArmorClass(uint32_t armorClass)
{
    _armorClass = armorClass;
}

uint32_t File::armorClass() const
{
    return _armorClass;
}

void File::setMeleeDamage(uint32_t meleeDamage)
{
    _meleeDamage = meleeDamage;
}

uint32_t File::meleeDamage() const
{
    return _meleeDamage;
}

void File::setCarryWeight(uint32_t carryWeight)
{
    _carryWeight = carryWeight;
}

uint32_t File::carryWeight() const
{
    return _carryWeight;
}

void File::setSequence(uint32_t sequence)
{
    _sequence = sequence;
}

uint32_t File::sequence() const
{
    return _sequence;
}

void File::setHealingRate(uint32_t healingRate)
{
    _healingRate = healingRate;
}

uint32_t File::healingRate() const
{
    return _healingRate;
}

void File::setCriticalChance(uint32_t criticalChance)
{
    _criticalChance = criticalChance;
}

uint32_t File::criticalChance() const
{
    return _criticalChance;
}

void File::setCriticalHitModifier(uint32_t criticalHitModifier)
{
    _criticalHitModifier = criticalHitModifier;
}

uint32_t File::criticalHitModifier() const
{
    return _criticalHitModifier;
}

void File::setRadiationResistance(uint32_t radiationResistance)
{
    _radiationResistance = radiationResistance;
}

uint32_t File::radiationResistance() const
{
    return _radiationResistance;
}

void File::setPoisonResistance(uint32_t poisonResistance)
{
    _poisonResistance = poisonResistance;
}

uint32_t File::poisonResistance() const
{
    return _poisonResistance;
}

void File::setAge(uint32_t age)
{
    _age = age;
}

uint32_t File::age() const
{
    return _age;
}

void File::setGender(GENDER gender)
{
    _gender = gender;
}

GENDER File::gender() const
{
    return _gender;
}

void File::setHitPointsBonus(uint32_t hitPointsBonus)
{
    _hitPointsBonus = hitPointsBonus;
}

uint32_t File::hitPointsBonus() const
{
    return _hitPointsBonus;
}

void File::setActionPointsBonus(uint32_t actionPointsBonus)
{
    _actionPointsBonus = actionPointsBonus;
}

uint32_t File::actionPointsBonus() const
{
    return _actionPointsBonus;
}

void File::setArmorClassBonus(uint32_t armorClassBonus)
{
    _armorClassBonus = armorClassBonus;
}

uint32_t File::armorClassBonus() const
{
    return _armorClassBonus;
}

void File::setMeleeDamageBonus(uint32_t meleeDamageBonus)
{
    _meleeDamageBonus = meleeDamageBonus;
}

uint32_t File::meleeDamageBonus() const
{
    return _meleeDamageBonus;
}

void File::setCarryWeightBonus(uint32_t carryWeightBonus)
{
    _carryWeightBonus = carryWeightBonus;
}

uint32_t File::carryWeightBonus() const
{
    return _carryWeightBonus;
}

void File::setSequenceBonus(uint32_t sequenceBonus)
{
    _sequenceBonus = sequenceBonus;
}

uint32_t File::sequenceBonus() const
{
    return _sequenceBonus;
}

void File::setHealingRateBonus(uint32_t healingRateBonus)
{
    _healingRateBonus = healingRateBonus;
}

uint32_t File::healingRateBonus() const
{
    return _healingRateBonus;
}

void File::setCriticalChanceBonus(uint32_t criticalChanceBonus)
{
    _criticalChanceBonus = criticalChanceBonus;
}

uint32_t File::criticalChanceBonus() const
{
    return _criticalChanceBonus;
}

void File::setCriticalHitModifierBonus(uint32_t criticalHitModifierBonus)
{
    _criticalHitModifierBonus = criticalHitModifierBonus;
}

uint32_t File::criticalHitModifierBonus() const
{
    return _criticalHitModifierBonus;
}

void File::setRadiationResistanceBonus(uint32_t radiationResistanceBonus)
{
    _radiationResistanceBonus = radiationResistanceBonus;
}

uint32_t File::radiationResistanceBonus() const
{
    return _radiationResistanceBonus;
}

void File::setPoisonResistanceBonus(uint32_t poisonResistanceBonus)
{
    _poisonResistanceBonus = poisonResistanceBonus;
}

uint32_t File::poisonResistanceBonus() const
{
    return _poisonResistanceBonus;
}

void File::setAgeBonus(uint32_t ageBonus)
{
    _ageBonus = ageBonus;
}

uint32_t File::ageBonus() const
{
    return _ageBonus;
}

void File::setGenderBonus(uint32_t genderBonus)
{
    _genderBonus = genderBonus;
}

uint32_t File::genderBonus() const
{
    return _genderBonus;
}

void File::setName(std::string name)
{
    _name = name;
}

std::string File::name() const
{
    return _name;
}

void File::setFirstTaggedSkill(SKILL firstTaggedSkill)
{
    _firstTaggedSkill = firstTaggedSkill;
}

SKILL File::firstTaggedSkill() const
{
    return _firstTaggedSkill;
}

void File::setSecondTaggedSkill(SKILL secondTaggedSkill)
{
    _secondTaggedSkill = secondTaggedSkill;
}

SKILL File::secondTaggedSkill() const
{
    return _secondTaggedSkill;
}

void File::setThirdTaggedSkill(SKILL thirdTaggedSkill)
{
    _thirdTaggedSkill = thirdTaggedSkill;
}

SKILL File::thirdTaggedSkill() const
{
    return _thirdTaggedSkill;
}

void File::setFourthTaggedSkill(SKILL fourthTaggedSkill)
{
    _fourthTaggedSkill = fourthTaggedSkill;
}

SKILL File::fourthTaggedSkill() const
{
    return _fourthTaggedSkill;
}

void File::setFirstTrait(TRAIT firstTrait)
{
    _firstTrait = firstTrait;
}

TRAIT File::firstTrait() const
{
    return _firstTrait;
}

void File::setSecondTrait(TRAIT secondTrait)
{
    _secondTrait = secondTrait;
}

TRAIT File::secondTrait() const
{
    return _secondTrait;
}

void File::setCharacterPoints(uint32_t characterPoints)
{
    _characterPoints = characterPoints;
}

uint32_t File::characterPoints() const
{
    return _characterPoints;
}

}
}
}
