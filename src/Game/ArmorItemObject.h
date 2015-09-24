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

#ifndef FALLTERGEIST_GAME_ARMORITEMOBJECT_H
#define FALLTERGEIST_GAME_ARMORITEMOBJECT_H

// C++ standard includes

// Falltergeist includes
#include "../Game/ItemObject.h"

// Third party includes
#include <libfalltergeist/Enums.h>

namespace Falltergeist
{
namespace Game
{

/*
 * Items wearable in "armor" slot.
 */
class ArmorItemObject : public ItemObject
{
public:

    ArmorItemObject();
    ~ArmorItemObject() override;

    int damageResist(DAMAGE type) const; // damage resistance bonus of the armor
    void setDamageResist(DAMAGE type, int value);

    int damageThreshold(DAMAGE type) const; // damage threshold bonus of the armor
    void setDamageThreshold(DAMAGE type, int value);

    int perk() const; // special perk given to player when wearing armor
    void setPerk(int value);

    unsigned int maleFID() const; // base frame ID used when wearing this type of armor by male critter
    void setMaleFID(unsigned int value);

    unsigned int femaleFID() const; // base frame ID used when wearing this type of armor by female critter
    void setFemaleFID(unsigned int value);

    unsigned int armorClass() const; // armor class (%)
    void setArmorClass(unsigned int value);

protected:
    std::vector<int> _damageResist = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<int> _damageThreshold = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int _perk = -1;
    unsigned int _maleFID = 0;
    unsigned int _femaleFID = 0;
    unsigned int _armorClass = 0;
};

}
}
#endif // FALLTERGEIST_GAME_ARMORITEMOBJECT_H
