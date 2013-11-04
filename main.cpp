/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <iostream>

// Falltergeist includes
#include "src/Engine/CrossPlatform.h"
#include "src/Engine/Game.h"
#include "src/Engine/Exception.h"
#include "src/States/StartState.h"
#include "src/Engine/ResourceManager.h"
#include "src/VM/VM.h"
#include "lib/libfalltergeist/libfalltergeist.h"

// Third party includes

using namespace Falltergeist;


int main(int argc, char *argv[])
{
    try
    {
        auto game = &Game::getInstance();

        /*
        auto script = new VM("scripts/rnslvr.int");
        script->initialize();
        script->call("map_enter_p_proc");
        script->call("map_update_p_proc");
        script->call("map_exit_p_proc");
        script->call("critter_p_proc");
        script->call("pickup_p_proc");
        script->call("talk_p_proc");
        script->call("destroy_p_proc");
        script->call("look_at_p_proc");
        script->call("description_p_proc");
        script->call("use_skill_on_p_proc");
        script->call("damage_p_proc");
        script->call("timed_event_p_proc");
        return 0;
        */

        game->setState(new StartState());
        game->run();
        return 0;

    }
    catch(libfalltergeist::Exception &e)
    {
        debug(e.message(), DEBUG_CRITICAL);
        return 1;
    }
    catch(Exception &e)
    {
        debug(e.message(), DEBUG_CRITICAL);
        return 1;
    }

}

