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

#ifndef FALLTERGEIST_GAMEARMORITEMOBJECT_H
#define FALLTERGEIST_GAMEARMORITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "ItemObject.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

class GameArmorItemObject : public GameItemObject
{
protected:
    std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int _perk = -1;
    unsigned int _maleFID = 0;
    unsigned int _femaleFID = 0;
    unsigned int _armorClass = 0;
public:
    enum { DAMAGE_NORMAL = 0, DAMAGE_LASER, DAMAGE_FIRE, DAMAGE_PLASMA, DAMAGE_ELECTRICAL, DAMAGE_EMP, DAMAGE_EXPLOSION, DAMAGE_RADIATION, DAMAGE_POISON };

    GameArmorItemObject();
    virtual ~GameArmorItemObject();

    virtual int damageResist(unsigned int type);
    void setDamageResist(unsigned int type, int value);

    virtual int damageThreshold(unsigned int type);
    void setDamageThreshold(unsigned int type, int value);

    int perk();
    void setPerk(int value);

    unsigned int maleFID();
    void setMaleFID(unsigned int value);

    unsigned int femaleFID();
    void setFemaleFID(unsigned int value);

    unsigned int armorClass();
    void setArmorClass(unsigned int value);

};

}
}

#endif // FALLTERGEIST_GAMEARMORITEMOBJECT_H
