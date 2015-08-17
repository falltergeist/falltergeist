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

#ifndef FALLTERGEIST_GAME_DEFINES_H
#define FALLTERGEIST_GAME_DEFINES_H

namespace Falltergeist
{
namespace Game
{

// Animations

// basic animations  0-19
#define ANIM_STAND                    0
#define ANIM_WALK                     1
#define ANIM_JUMP_BEGIN               2
#define ANIM_JUMP_END                 3
#define ANIM_CLIMB_LADDER             4
#define ANIM_FALLING                  5
#define ANIM_UP_STAIRS_RIGHT          6
#define ANIM_UP_STAIRS_LEFT           7
#define ANIM_DOWN_STAIRS_RIGHT        8
#define ANIM_DOWN_STAIRS_LEFT         9
#define ANIM_MAGIC_HANDS_GROUND       10
#define ANIM_MAGIC_HANDS_MIDDLE       11
#define ANIM_MAGIC_HANDS_UP           12
#define ANIM_DODGE_ANIM               13
#define ANIM_HIT_FROM_FRONT           14
#define ANIM_HIT_FROM_BACK            15
#define ANIM_THROW_PUNCH              16
#define ANIM_KICK_LEG                 17
#define ANIM_THROW_ANIM               18
#define ANIM_RUNNING                  19
// knockdown and death   20-35
#define ANIM_FALL_BACK                20
#define ANIM_FALL_FRONT               21
#define ANIM_BAD_LANDING              22
#define ANIM_BIG_HOLE                 23
#define ANIM_CHARRED_BODY             24
#define ANIM_chunks_of_flesh          25
#define ANIM_dancing_autofire         26
#define ANIM_electrify                27
#define ANIM_sliced_in_half           28
#define ANIM_burned_to_nothing        29
#define ANIM_electrified_to_nothing   30
#define ANIM_exploded_to_nothing      31
#define ANIM_melted_to_nothing        32
#define ANIM_fire_dance               33
#define ANIM_fall_back_blood          34
#define ANIM_fall_front_blood         35
// change positions  36-37
#define ANIM_prone_to_standing        36
#define ANIM_back_to_standing         37
// weapon 38-47
#define ANIM_take_out                 38
#define ANIM_put_away                 39
#define ANIM_parry_anim               40
#define ANIM_thrust_anim              41
#define ANIM_swing_anim               42
#define ANIM_point                    43
#define ANIM_unpoint                  44
#define ANIM_fire_single              45
#define ANIM_fire_burst               46
#define ANIM_fire_continuous          47
// single-frame death animations (the last frame of knockdown and death animations)   48-63
#define ANIM_fall_back_sf             48
#define ANIM_fall_front_sf            49
#define ANIM_bad_landing_sf           50
#define ANIM_big_hole_sf              51
#define ANIM_charred_body_sf          52
#define ANIM_chunks_of_flesh_sf       53
#define ANIM_dancing_autofire_sf      54
#define ANIM_electrify_sf             55
#define ANIM_sliced_in_half_sf        56
#define ANIM_burned_to_nothing_sf     57
#define ANIM_electrified_to_nothing_sf  58
#define ANIM_exploded_to_nothing_sf   59
#define ANIM_melted_to_nothing_sf     60
//#define ANIM_fire_dance_sf          61 // doesn't exist, but keeps the enums ordered
#define ANIM_fall_back_blood_sf       61
#define ANIM_fall_front_blood_sf      62
// called shot interface picture	  64
#define ANIM_called_shot_pic          63
#define ANIM_max_anim                 65 // 65


// Critters FID

#define FID_HMJMPS      0x0100000B   // vault13 jumpsuit male
#define FID_HFJMPS      0x01000004   // vault13 jumpsuit female
#define FID_HERO_MALE   0x0100003E
#define FID_HERO_FEMALE 0x0100003D

}
}
#endif // FALLTERGEIST_GAME_DEFINES_H
