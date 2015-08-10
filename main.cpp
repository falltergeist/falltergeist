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
#include "src/Exception.h"
#include "src/Game/Game.h"
#include "src/Logger.h"
#include "src/State/Start.h"
#include "src/Lua/Script.h"

// Third party includes
#include <libfalltergeist.h>

using namespace Falltergeist;

int main(int argc, char* argv[])
{
    try
    {

        // just for testing
        Lua::Script script("data/scripts/test.lua");
        script.run();

        auto game = Game::Game::getInstance();
        game->setState(new State::Start());
        game->run();
        game->shutdown();
        return 0;
    }
    catch(const libfalltergeist::Exception &e)
    {
        Logger::critical() << e.what() << std::endl;
    }
    catch(const Exception &e)
    {
        Logger::critical() << e.what() << std::endl;
    }
    /*
    catch (const std::exception &e)
    {
        Logger::critical() << e.what() << std::endl;
    }
    */
    return 1;
}

