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

#ifndef FALLTERGEIST_GAME_WEAPONITEMOBJECT_H
#define FALLTERGEIST_GAME_WEAPONITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/ItemObject.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

/**
 * All items that can be used as a weapon.
 */
class WeaponItemObject : public ItemObject
{
public:
    WeaponItemObject();
    ~WeaponItemObject() override;

    unsigned int animationCode() const;
    void setAnimationCode(unsigned int value);

    unsigned int damageMin() const;
    void setDamageMin(unsigned int value);

    unsigned int damageMax() const;
    void setDamageMax(unsigned int value);

    unsigned int damageType() const;
    void setDamageType(unsigned int value);

    unsigned int rangePrimary() const;
    void setRangePrimary(unsigned int value);

    unsigned int rangeSecondary() const;
    void setRangeSecondary(unsigned int value);

    unsigned int minimumStrength() const;
    void setMinimumStrength(unsigned int value);

    unsigned int actionCostPrimary() const;
    void setActionCostPrimary(unsigned int value);

    unsigned int actionCostSecondary() const;
    void setActionCostSecondary(unsigned int value);

    unsigned int burstRounds() const;
    void setBurstRounds(unsigned int value);

    unsigned int ammoType() const;
    void setAmmoType(unsigned int value);

    unsigned int ammoPID() const;
    void setAmmoPID(unsigned int value);

    unsigned int ammoCapacity() const;
    void setAmmoCapacity(unsigned int value);

    int perk() const;
    void setPerk(int value);

protected:
    unsigned int _animationCode = 0;
    unsigned int _damageMin = 0;
    unsigned int _damageMax = 0;
    unsigned int _damageType = 0;
    unsigned int _rangePrimary = 0;
    unsigned int _rangeSecondary = 0;
    unsigned int _minimumStrength = 0;
    unsigned int _actionCostPrimary = 0;
    unsigned int _actionCostSecondary = 0;
    unsigned int _burstRounds = 0;
    unsigned int _ammoType = 0;
    unsigned int _ammoPID = 0;
    unsigned int _ammoCapacity = 0;
    int _perk = -1;
};

}
}
#endif // FALLTERGEIST_GAME_WEAPONITEMOBJECT_H
