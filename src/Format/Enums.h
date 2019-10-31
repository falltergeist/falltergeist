/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2018 Falltergeist Developers
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

#ifndef FALLTERGEIST_FORMAT_ENUMS_H
#define FALLTERGEIST_FORMAT_ENUMS_H

// C++ standard includes
#include <stdint.h>

// Falltergeist includes

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

enum class PERK : int32_t
{
    AWARENESS = 1,
    BONUS_HTH_ATTACKS,
    BONUS_HTH_DAMAGE,
    BONUS_MOVE,
    BONUS_RANGED_DAMAGE,
    BONUS_RATE_OF_FIRE,
    EARLIER_SEQUENCE,
    FASTER_HEALING,
    MORE_CRITICALS,
    NIGHT_VISION,
    PRESENCE,
    RAD_RESISTANCE,
    TOUGHNESS,
    STRONG_BACK,
    SHARPSHOOTER,
    SILENT_RUNNING,
    SURVIVALIST,
    MASTER_TRADER,
    EDUCATED,
    HEALER,
    FORTUNE_FINDER,
    BETTER_CRITICALS,
    EMPATHY,
    SLAYER,
    SNIPER,
    SILENT_DEATH,
    ACTION_BOY,
    MENTAL_BLOCK,   /// \b unimplemented in the vanilla F2 engine
    LIFEGIVER,
    DODGER,
    SNAKEATER,
    MR_FIXIT,
    MEDIC,
    MASTER_THIEF,
    SPEAKER,
    HEAVE_HO,
    FRIENDLY_FOE,   /// \b unimplemented in the vanilla F2 engine
    PICKPOCKET = 38,
    GHOST,
    CULT_OF_PERSONALITY,
    SCROUNGER,
    EXPLORER,
    FLOWER_CHILD,   /// \b unimplemented in the vanilla F2 engine
    PATHFINDER,
    ANIMAL_FRIEND,  /// \b unimplemented in the vanilla F2 engine
    SCOUT,
    MYSTERIOUS_STRANGER,
    RANGER,
    QUICK_POCKETS,
    SMOOTH_TALKER,
    SWIFT_LEARNER,
    TAG,
    MUTATE,
    NUKA_COLA_ADDICTION,            /// \b addiction perk
    BUFFOUT_ADDICTION,              /// \b addiction perk
    MENTATS_ADDICTION,              /// \b addiction perk
    PSYCHO_ADDICTION,               /// \b addiction perk
    RADAWAY_ADDICTION,              /// \b addiction perk
    WEAPON_LONG_RANGE,              /// \b weapon perk
    WEAPON_ACCURATE,                /// \b weapon perk
    WEAPON_PENETRATE,               /// \b weapon perk
    WEAPON_KNOCKBACK,               /// \b weapon perk
    POWERED_ARMOR,                  /// \b armor perk
    COMBAT_ARMOR,                   /// \b armor perk
    WEAPON_SCOPE_RANGE,             /// \b weapon perk
    WEAPON_FAST_RELOAD,             /// \b weapon perk
    WEAPON_NIGHT_SIGHT,             /// \b weapon perk
    WEAPON_FLAMEBOY,                /// \b weapon perk
    ARMOR_ADVANCED_I,               /// \b armor perk
    ARMOR_ADVANCED_II,              /// \b armor perk
    JET_ADDICTION,                  /// \b addiction perk
    TRAGIC_ADDICTION,               /// \b unimplemented in the vanilla F2 engine
    ARMOR_CHARISMA,                 /// \b armor perk
    GECKO_SKINNING,                 /// \b special perk
    DERMAL_IMPACT_ARMOR,            /// \b special perk
    DERMAL_IMPACT_ASSLT_ENHANCED,   /// \b special perk
    PHOENIX_ARMOR_IMPLANTS,         /// \b special perk
    PHOENIX_ASSAULT_ENHANCEMENT,    /// \b special perk
    VAULT_CITY_INOCULATIONS,        /// \b special perk
    ADRENALINE_RUSH,
    CAUTIOUS_NATURE,
    COMPREHENSION,
    DEMOLITION_EXPERT,
    GAMBLER,
    GAIN_STRENGTH,
    GAIN_PERCEPTION,
    GAIN_ENDURANCE,
    GAIN_CHARISMA,
    GAIN_INTELLIGENCE,
    GAIN_AGILITY,
    GAIN_LUCK,
    HARMLESS,
    HERE_AND_NOW,
    HTH_EVADE,
    KAMA_SUTRA_MASTER,
    KARMA_BEACON,
    LIGHT_STEP,
    LIVING_ANATOMY,
    MAGNETIC_PERSONALITY,
    NEGOTIATOR,
    PACK_RAT,
    PYROMANIAC,
    QUICK_RECOVERY,
    SALESMAN,
    STONEWALL,
    THIEF,
    WEAPON_HANDLING,
    VAULT_CITY_TRAINING,            /// \b special perk
    ALCOHOL_RAISED_HIT_POINTS,      /// \b special perk
    ALCOHOL_RAISED_HIT_POINTS_II,   /// \b special perk
    ALCOHOL_LOWERED_HIT_POINTS,     /// \b special perk
    ALCOHOL_LOWERED_HIT_POINTS_II,  /// \b special perk
    AUTODOC_RAISED_HIT_POINTS,      /// \b special perk
    AUTODOC_RAISED_HIT_POINTS_II,   /// \b special perk
    AUTODOC_LOWERED_HIT_POINTS,     /// \b special perk
    AUTODOC_LOWERED_HIT_POINTS_II,  /// \b special perk
    EXPERT_EXCREMENT_EXPEDITOR,     /// \b special perk
    WEAPON_ENHANCED_KNOCKOUT,       /// \b special perk
    // JINXED - a TRAIT, but is listed in PERKS.MSG as the last perk

    // Should be last entry.
    PERK_COUNT
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

#endif // FALLTERGEIST_FORMAT_ENUMS_H
