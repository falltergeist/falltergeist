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

#ifndef FALLTERGEIST_FORMAT_PRO_FILE_H
#define FALLTERGEIST_FORMAT_PRO_FILE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Pro
{

class File : public Dat::Item
{
public:
    File(Dat::Stream&& stream);

    uint8_t soundId() const;

    int32_t PID() const;
    int32_t FID() const;
    int32_t scriptId() const;
    int32_t perk() const;
    int32_t inventoryFID() const;
    int32_t armorMaleFID() const;
    int32_t armorFemaleFID() const;

    uint32_t weaponAnimationCode() const;
    uint32_t weaponDamageMin() const;
    uint32_t weaponDamageMax() const;
    uint32_t weaponDamageType() const;
    uint32_t weaponRangePrimary() const;
    uint32_t weaponRangeSecondary() const;
    uint32_t weaponMinimumStrenght() const;
    uint32_t weaponActionCostPrimary() const;
    uint32_t weaponActionCostSecondary() const;
    uint32_t weaponBurstRounds() const;
    uint32_t weaponAmmoType() const;
    uint32_t weaponAmmoPID() const;
    uint32_t weaponAmmoCapacity() const;
    uint32_t armorClass() const;
    uint32_t typeId() const;
    uint32_t subtypeId() const;
    uint32_t messageId() const;
    uint32_t flags() const;
    uint32_t flagsExt() const;
    uint32_t weight() const;
    uint32_t critterHitPointsMax() const;
    uint32_t critterActionPoints() const;
    uint32_t critterArmorClass() const;
    uint32_t critterMeleeDamage() const;
    uint32_t critterCarryWeightMax() const;
    uint32_t critterSequence() const;
    uint32_t critterHealingRate() const;
    uint32_t critterCriticalChance() const;
    uint32_t critterAge() const;
    uint32_t critterGender() const;

    std::vector<uint32_t>* critterStats();
    std::vector<uint32_t>* critterStatsBonus();
    std::vector<uint32_t>* critterSkills();
    std::vector<uint32_t>* damageResist();
    std::vector<uint32_t>* damageThreshold();

protected:
    uint8_t _soundId = 0;

    int32_t _PID = -1;
    int32_t _FID = -1;
    int32_t _critterHeadFID = -1;
    int32_t _perk = -1;
    int32_t _SID = -1;
    int32_t _inventoryFID = -1;

    uint32_t _armorMaleFID = 0;
    uint32_t _armorFemaleFID = 0;
    uint32_t _armorClass = 0;
    uint32_t _weaponAnimationCode = 0;
    uint32_t _weaponDamageMin = 0;
    uint32_t _weaponDamageMax = 0;
    uint32_t _weaponDamageType = 0;
    uint32_t _weaponRangePrimary = 0;
    uint32_t _weaponRangeSecondary = 0;
    uint32_t _weaponMinimumStrenght = 0;
    uint32_t _weaponActionCostPrimary = 0;
    uint32_t _weaponActionCostSecondary = 0;
    uint32_t _weaponBurstRounds = 0;
    uint32_t _weaponAmmoType = 0;
    uint32_t _weaponAmmoPID = 0;
    uint32_t _weaponAmmoCapacity = 0;
    uint32_t _subtypeId = 0;
    uint32_t _messageId = 0;
    uint32_t _critterHitPointsMax = 0;
    uint32_t _critterActionPoints = 0;
    uint32_t _critterArmorClass = 0;
    uint32_t _critterMeleeDamage = 0;
    uint32_t _critterCarryWeightMax = 0;
    uint32_t _critterSequence = 0;
    uint32_t _critterHealingRate = 0;
    uint32_t _critterCriticalChance = 0;
    uint32_t _critterAge;
    uint32_t _critterGender;
    uint32_t _lightDistance = 0;
    uint32_t _lightIntencity = 0;
    uint32_t _flags = 0;
    uint32_t _flagsExt = 0;
    uint32_t _materialId = 0;
    uint32_t _containerSize = 0;
    uint32_t _weight = 0;
    uint32_t _basePrice = 0;

    std::vector<uint32_t> _critterStats = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _critterStatsBonus = {0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _critterSkills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<uint32_t> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
};

}
}
}
#endif // FALLTERGEIST_FORMAT_PRO_FILE_H
