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
#include "../Dat/Stream.h"
#include "../Pro/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Pro
{

File::File(Dat::Stream&& stream)
{
    stream.setPosition(0);

    _PID            = stream.int32();
    _messageId      = stream.uint32();
    _FID            = stream.int32();
    _lightDistance  = stream.uint32();
    _lightIntencity = stream.uint32();
    _flags          = stream.uint32();

    switch ((OBJECT_TYPE)typeId())
    {
        case OBJECT_TYPE::TILE:
        case OBJECT_TYPE::MISC:
            break;
        default:
            _flagsExt = stream.uint32();
            break;
    }

    switch ((OBJECT_TYPE)typeId())
    {
        case OBJECT_TYPE::ITEM:
        case OBJECT_TYPE::CRITTER:
        case OBJECT_TYPE::SCENERY:
        case OBJECT_TYPE::WALL:
            _SID = stream.int32();
            break;
        case OBJECT_TYPE::TILE:
        case OBJECT_TYPE::MISC:
            break;
    }

    switch ((OBJECT_TYPE)typeId())
    {
        case OBJECT_TYPE::ITEM:
        {
            _subtypeId     = stream.uint32();
            _materialId    = stream.uint32();
            _containerSize = stream.uint32();
            _weight        = stream.uint32();
            _basePrice     = stream.uint32();
            _inventoryFID  = stream.int32();
            _soundId       = stream.uint8();

            switch ((ITEM_TYPE)subtypeId())
            {
                case ITEM_TYPE::ARMOR:
                {
                    _armorClass = stream.uint32();
                    // Damage resist
                    for (unsigned int i = 0; i != 7; ++i)
                    {
                        _damageResist.at(i) = stream.uint32();
                    }
                    // Damage threshold
                    for (unsigned int i = 0; i != 7; ++i)
                    {
                        _damageThreshold.at(i) = stream.uint32();
                    }
                    _perk           = stream.int32();
                    _armorMaleFID   = stream.int32();
                    _armorFemaleFID = stream.int32();
                    break;
                }
                case ITEM_TYPE::CONTAINER:
                {
                    stream.uint32(); // max size
                    stream.uint32(); // containter flags
                    break;
                }
                case ITEM_TYPE::DRUG:
                {
                    stream.uint32(); // Stat0
                    stream.uint32(); // Stat1
                    stream.uint32(); // Stat2
                    stream.uint32(); // Stat0 ammount
                    stream.uint32(); // Stat1 ammount
                    stream.uint32(); // Stat2 ammount
                    // first delayed effect
                    stream.uint32(); // delay in game minutes
                    stream.uint32(); // Stat0 ammount
                    stream.uint32(); // Stat1 ammount
                    stream.uint32(); // Stat2 ammount
                    // second delayed effect
                    stream.uint32(); // delay in game minutes
                    stream.uint32(); // Stat0 ammount
                    stream.uint32(); // Stat1 ammount
                    stream.uint32(); // Stat2 ammount
                    stream.uint32(); // addiction chance
                    stream.uint32(); // addiction perk
                    stream.uint32(); // addiction delay
                    break;
                }
                case ITEM_TYPE::WEAPON:
                    _weaponAnimationCode  = stream.uint32();
                    _weaponDamageMin      = stream.uint32();
                    _weaponDamageMax      = stream.uint32();
                    _weaponDamageType     = stream.uint32();
                    _weaponRangePrimary   = stream.uint32();
                    _weaponRangeSecondary = stream.uint32();
                    stream.uint32(); // Proj PID
                    _weaponMinimumStrenght     = stream.uint32();
                    _weaponActionCostPrimary   = stream.uint32();
                    _weaponActionCostSecondary = stream.uint32();
                    stream.uint32(); // Crit Fail
                    _perk = stream.int32();
                    _weaponBurstRounds  = stream.uint32();
                    _weaponAmmoType     = stream.uint32();
                    _weaponAmmoPID      = stream.uint32();
                    _weaponAmmoCapacity = stream.uint32();
                    _soundId = stream.uint8();
                    break;
                case ITEM_TYPE::AMMO:
                    break;
                case ITEM_TYPE::MISC:
                    break;
                case ITEM_TYPE::KEY:
                    break;
            }
            break;
        }
        case OBJECT_TYPE::CRITTER:
        {
            _critterHeadFID = stream.int32();

            stream.uint32(); // ai packet number
            stream.uint32(); // team number
            stream.uint32(); // flags

            for (unsigned int i = 0; i != 7; ++i)
            {
                _critterStats.at(i) = stream.uint32();
            }
            _critterHitPointsMax = stream.uint32();
            _critterActionPoints = stream.uint32();
            _critterArmorClass   = stream.uint32();
            stream.uint32(); // Unused
            _critterMeleeDamage    = stream.uint32();
            _critterCarryWeightMax = stream.uint32();
            _critterSequence       = stream.uint32();
            _critterHealingRate    = stream.uint32();
            _critterCriticalChance = stream.uint32();
            stream.uint32(); // Better criticals

            // Damage threshold
            for (unsigned int i = 0; i != 7; ++i)
            {
                _damageThreshold.at(i) = stream.uint32();
            }
            // Damage resist
            for (unsigned int i = 0; i != 9; ++i)
            {
                _damageResist.at(i) = stream.uint32();
            }

            _critterAge = stream.uint32(); // age
            _critterGender = stream.uint32(); // sex

            for (unsigned int i = 0; i != 7; ++i)
            {
                _critterStatsBonus.at(i) = stream.uint32();
            }

            stream.uint32(); // Bonus Health points
            stream.uint32(); // Bonus Action points
            stream.uint32(); // Bonus Armor class
            stream.uint32(); // Bonus Unused
            stream.uint32(); // Bonus Melee damage
            stream.uint32(); // Bonus Carry weight
            stream.uint32(); // Bonus Sequence
            stream.uint32(); // Bonus Healing rate
            stream.uint32(); // Bonus Critical chance
            stream.uint32(); // Bonus Better criticals

            // Bonus Damage threshold
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();

            // Bonus Damage resistance
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();
            stream.uint32();

            stream.uint32(); // Bonus age
            stream.uint32(); // Bonus sex

            for (unsigned int i = 0; i != 18; ++i)
            {
                _critterSkills.at(i) = stream.uint32();
            }

            stream.uint32(); // body type
            stream.uint32(); // experience for kill
            stream.uint32(); // kill type
            stream.uint32(); // damage type
            break;
        }
        case OBJECT_TYPE::SCENERY:
        {
            _subtypeId  = stream.uint32();
            _materialId = stream.uint32();
            _soundId    = stream.uint8();
            switch((SCENERY_TYPE)subtypeId())
            {
                case SCENERY_TYPE::DOOR:
                {
                    stream.uint32(); // walk thru flag
                    stream.uint32(); // unknown
                    break;
                }
                case SCENERY_TYPE::STAIRS:
                {
                    stream.uint32(); // DestTile && DestElevation
                    stream.uint32(); // DestElevation
                    break;
                }
                case SCENERY_TYPE::ELEVATOR:
                {
                    stream.uint32(); // Elevator type
                    stream.uint32(); // Elevator level
                    break;
                }
                case SCENERY_TYPE::LADDER_BOTTOM:
                case SCENERY_TYPE::LADDER_TOP:
                {
                    stream.uint32(); // DestTile && DestElevation
                    break;
                }
                case SCENERY_TYPE::GENERIC:
                {
                    stream.uint32(); // unknown
                }
            }

            break;
        }
        case OBJECT_TYPE::WALL:
        {
            _materialId = stream.uint32();
            break;
        }
        case OBJECT_TYPE::TILE:
        {
            _materialId = stream.uint32();
            break;
        }
        case OBJECT_TYPE::MISC:
        {
            stream.uint32(); // unknown
            break;
        }
    }
}

int32_t File::PID() const
{
    return _PID;
}

int32_t File::FID() const
{
    return _FID;
}

uint32_t File::typeId() const
{
    return (_PID & 0x0F000000) >> 24;
}

uint32_t File::subtypeId() const
{
    return _subtypeId;
}

uint32_t File::messageId() const
{
    return _messageId;
}

uint32_t File::flags() const
{
    return _flags;
}

uint32_t File::flagsExt() const
{
    return _flagsExt;
}

int32_t File::scriptId() const
{
    if (_SID == -1)
    {
        return -1;
    }
    return _SID & 0x0000FFFF;
}

std::vector<uint32_t>* File::critterStats()
{
    return &_critterStats;
}

std::vector<uint32_t>* File::critterStatsBonus()
{
    return &_critterStatsBonus;
}

std::vector<uint32_t>* File::critterSkills()
{
    return &_critterSkills;
}

std::vector<uint32_t>* File::damageResist()
{
    return &_damageResist;
}

std::vector<uint32_t>* File::damageThreshold()
{
    return &_damageThreshold;
}

uint32_t File::critterHitPointsMax() const
{
    return _critterHitPointsMax;
}

uint32_t File::critterActionPoints() const
{
    return _critterActionPoints;
}

uint32_t File::critterArmorClass() const
{
    return _critterArmorClass;
}

uint32_t File::critterMeleeDamage() const
{
    return _critterMeleeDamage;
}

uint32_t File::critterCarryWeightMax() const
{
    return _critterCarryWeightMax;
}

uint32_t File::critterSequence() const
{
    return _critterSequence;
}

uint32_t File::critterCriticalChance() const
{
    return _critterCriticalChance;
}

uint32_t File::critterHealingRate() const
{
    return _critterHealingRate;
}


uint32_t File::critterAge() const
{
    return _critterAge;
}

uint32_t File::critterGender() const
{
    return _critterGender;
}


uint32_t File::weight() const
{
    return _weight;
}

int32_t File::perk() const
{
    return _perk;
}

int32_t File::armorFemaleFID() const
{
    return _armorFemaleFID;
}

int32_t File::armorMaleFID() const
{
    return _armorMaleFID;
}

uint32_t File::armorClass() const
{
    return _armorClass;
}

uint32_t File::weaponAnimationCode() const
{
    return _weaponAnimationCode;
}

uint32_t File::weaponDamageMin() const
{
    return _weaponDamageMin;
}

uint32_t File::weaponDamageMax() const
{
    return _weaponDamageMax;
}

uint32_t File::weaponDamageType() const
{
    return _weaponDamageType;
}

uint32_t File::weaponRangePrimary() const
{
    return _weaponRangePrimary;
}

uint32_t File::weaponRangeSecondary() const
{
    return _weaponRangeSecondary;
}

uint32_t File::weaponMinimumStrenght() const
{
    return _weaponMinimumStrenght;
}

uint32_t File::weaponActionCostPrimary() const
{
    return _weaponActionCostPrimary;
}

uint32_t File::weaponActionCostSecondary() const
{
    return _weaponActionCostSecondary;
}

uint32_t File::weaponBurstRounds() const
{
    return _weaponBurstRounds;
}

uint32_t File::weaponAmmoType() const
{
    return _weaponAmmoType;
}

uint32_t File::weaponAmmoPID() const
{
    return _weaponAmmoPID;
}

uint32_t File::weaponAmmoCapacity() const
{
    return _weaponAmmoCapacity;
}

uint8_t File::soundId() const
{
    return _soundId;
}

int32_t File::inventoryFID() const
{
    return _inventoryFID;
}

}
}
}
