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

// C++ standard includes

// Falltergeist includes
#include "../../Logger.h"
#include "../../VM/Handlers/Opcode80E1Handler.h"
#include "../../VM/VM.h"
#include "../../Game/Game.h"
#include "../../State/Location.h"

// Third party includes

namespace Falltergeist
{

Opcode80E1Handler::Opcode80E1Handler(VM* vm) : OpcodeHandler(vm)
{
}

void Opcode80E1Handler::_run()
{
    // @TODO: add implementation
    Logger::debug("SCRIPT") << "[80E1] [*] int metarule3(int meta, int p1, int p2, int p3)" << std::endl;
    auto arg3 = _vm->dataStack()->popInteger();
    auto arg2 = _vm->dataStack()->popInteger();
    auto arg1 = _vm->dataStack()->pop();
    auto meta = _vm->dataStack()->popInteger();
    int result = 0;
    switch(meta)
    {
        case 100: // rm_fixed_timer_event(object, fixed_param, 0) 
            break;
        case 101: // mark subtile visited on worldmap - mark_world_subtile_visited(x, y, radius)
            break;
        case 102: // METARULE3_SET_WM_MUSIC - (map index, ACM file name)
            break;
        case 103: // player_kill_count(critterType)
            break;
        case 104: // int mark_map_entrance_state(int map_idx, int state, int elev); elev -1 means for all elevations
            break;
        case 105: // int wm_get_subtile_state(int xPos, int yPos)  (0 - unknown, 1 - known, 2 - visited)
            break;
        case 106: // ObjectPtr tile_get_next_critter(int tile_num, int elev, ObjectPtr last_critter)
            break; 
        case 107: // int art_change_fid_num(ObjectPtr who, int fid) - change base FID num for object
            break;
        case 108: // void tile_set_center(int tileNum) - center camera on given tile
            Game::getInstance()->locationState()->centerCameraAtHexagon(arg1.integerValue());
            break;
        default:
            _error("metarule3 - unknown meta: " + std::to_string(meta));
            break;
    }
    _vm->dataStack()->push(result);
}

}
