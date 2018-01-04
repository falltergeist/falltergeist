/*
 * Copyright 2012-2018 Falltergeist Developers.
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

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"
#include "../Game/Defines.h"
#include "../Helpers/CritterAnimationHelper.h"

// Third party includes

namespace Falltergeist
{
    namespace Helpers
    {
        std::string CritterAnimationHelper::getSuffix(unsigned int animationId, unsigned int weaponId) const
        {
            const char weaponCode = 'c' + weaponId;
            if (animationId >= ANIM_TAKE_OUT && animationId <= ANIM_FIRE_CONTINUOUS) {
                if (weaponId > WEAPON_ROCKET_LAUNCHER || weaponId == 0) {
                    throw Exception("Critter weaponId unsupported value");
                }
                //[d-m][c-l]
                return { weaponCode, static_cast<char>(animationId + 0x3D) };
            }

            if (animationId == ANIM_PRONE_TO_STANDING) {
                return "ch";
            }

            if (animationId == ANIM_BACK_TO_STANDING) {
                return "cj";
            }

            // TODO: figure out what is 0x40
            if (animationId == 0x40) {
                return "na";
            }

            // single-frame death animations (the last frame of knockdown and death animations)
            if (animationId >= ANIM_FALL_BACK_SF) {
                // r[a-z]
                return { 'r', static_cast<char>(animationId + 0x31) };
            }

            if (animationId >= ANIM_FALL_BACK) {
                // b[a-p]
                return { 'b', static_cast<char>(animationId + 0x4d) };
            }

            if (animationId == ANIM_THROW_ANIM) {
                if (weaponId == WEAPON_KNIFE) {
                    return "dm";
                }

                if (weaponId == WEAPON_SPEAR) {
                    return "gm";
                }

                return "as";
            }

            if (animationId == ANIM_DODGE_ANIM) {
                if (weaponId > 0) {
                    // [d-m]e
                    return { weaponCode, 'e' };
                }

                return "an";
            }

            if (animationId <= ANIM_WALK && weaponId > 0) {
                return { weaponCode, static_cast<char>('a' + animationId) };
            }

            return { 'a', static_cast<char>('a' + animationId) };
        }
    }
}
