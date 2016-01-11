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

#ifndef LIBFALLTERGEIST_ENUMS_H
#define LIBFALLTERGEIST_ENUMS_H

// C++ standard includes
#include <stdint.h>

// libfalltergeist includes

// Third party includes

enum class STAT : uint32_t
{
    STRENGTH = 0,
    PERCEPTION,
    ENDURANCE,
    CHARISMA,
    INTELLIGENCE,
    AGILITY,
    LUCK
};

enum class SKILL : int32_t
{
    NONE = -1,
    SMALL_GUNS = 0,
    BIG_GUNS,
    ENERGY_WEAPONS,
    UNARMED,
    MELEE_WEAPONS,
    THROWING,
    FIRST_AID,
    DOCTOR,
    SNEAK,
    LOCKPICK,
    STEAL,
    TRAPS,
    SCIENCE,
    REPAIR,
    SPEECH,
    BARTER,
    GAMBLING,
    OUTDOORSMAN
};

enum class DAMAGE : uint32_t
{
    NORMAL = 0,
    LASER,
    FIRE,
    PLASMA,
    ELECTRICAL,
    EMP,
    EXPLOSIVE,
    RADIATION,
    POISON
};

enum class TRAIT : int32_t
{
    NONE = -1,
    FAST_METABOLISM = 0,
    BRUISER,
    SMALL_FRAME,
    ONE_HANDED,
    FINESSE,
    KAMIKAZE,
    HEAVY_HANDED,
    FAST_SHOT,
    BLOODY_MESS,
    JINXED,
    GOOD_NATURED,
    CHEM_RELIANT,
    CHEM_RESISTANT,
    SEX_APPEAL,
    SKILLED,
    GIFTED
};

enum class ENDIANNESS : char
{
    BIG = 0,
    LITTLE
};

enum class FRM_TYPE : char
{
    ITEM = 0,
    CRITTER,
    SCENERY,
    WALL,
    TILE,
    MISC,
    INTERFACE,
    INVENTORY
};

enum class MASK
{
    SLIME = 0,
    FIRE_SLOW = 2,
    FIRE_FAST = 4,
    MONITOR = 8,
    REDDOT = 16,
    SHORE = 32
};

enum class PROCEDURE_FLAG
{
    TIMED       = 0x01,
    CONDITIONAL = 0x02,
    IMPORTED    = 0x04,
    EXPORTED    = 0x08,
    CRITICAL    = 0x10,
    PURE        = 0x20,
    INLINE      = 0x40
};

enum class OBJECT_TYPE
{
    ITEM = 0,
    CRITTER,
    SCENERY,
    WALL,
    TILE,
    MISC
};

enum class ITEM_TYPE
{
    ARMOR = 0,
    CONTAINER,
    DRUG,
    WEAPON,
    AMMO,
    MISC,
    KEY
};

enum class SCENERY_TYPE
{
    DOOR = 0,
    STAIRS,
    ELEVATOR,
    LADDER_BOTTOM,
    LADDER_TOP,
    GENERIC
};

enum class HAND : char
{
    RIGHT = 0,
    LEFT
};

enum class GENDER : char
{
    MALE = 0,
    FEMALE
};

#endif // LIBFALLTERGEIST_ENUMS_H
