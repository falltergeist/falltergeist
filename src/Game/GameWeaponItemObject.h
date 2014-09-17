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

#ifndef FALLTERGEIST_GAMEWEAPONITEMOBJECT_H
#define FALLTERGEIST_GAMEWEAPONITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/GameItemObject.h"

// Third party includes

namespace Falltergeist
{

class GameWeaponItemObject : public GameItemObject
{
protected:
    unsigned int _animationCode = 0;
    unsigned int _damageMin = 0;
    unsigned int _damageMax = 0;
    unsigned int _damageType = 0;
    unsigned int _rangePrimary = 0;
    unsigned int _rangeSecondary = 0;
    unsigned int _minimumStrenght = 0;
    unsigned int _actionCostPrimary = 0;
    unsigned int _actionCostSecondary = 0;
    unsigned int _burstRounds = 0;
    unsigned int _ammoType = 0;
    unsigned int _ammoPID = 0;
    unsigned int _ammoCapacity = 0;
    int _perk = -1;
public:
    GameWeaponItemObject();
    virtual ~GameWeaponItemObject();

    unsigned int animationCode();
    void setAnimationCode(unsigned int value);

    unsigned int damageMin();
    void setDamageMin(unsigned int value);

    unsigned int damageMax();
    void setDamageMax(unsigned int value);

    unsigned int damageType();
    void setDamageType(unsigned int value);

    unsigned int rangePrimary();
    void setRangePrimary(unsigned int value);

    unsigned int rangeSecondary();
    void setRangeSecondary(unsigned int value);

    unsigned int minimumStrenght();
    void setMinimumStrenght(unsigned int value);

    unsigned int actionCostPrimary();
    void setActionCostPrimary(unsigned int value);

    unsigned int actionCostSecondary();
    void setActionCostSecondary(unsigned int value);

    unsigned int burstRounds();
    void setBurstRounds(unsigned int value);

    unsigned int ammoType();
    void setAmmoType(unsigned int value);

    unsigned int ammoPID();
    void setAmmoPID(unsigned int value);

    unsigned int ammoCapacity();
    void setAmmoCapacity(unsigned int value);

    int perk();
    void setPerk(int value);

};

}
#endif // FALLTERGEIST_GAMEWEAPONITEMOBJECT_H
