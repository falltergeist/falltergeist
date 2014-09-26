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

// C++ standard includes

// Falltergeist includes
#include "src/Engine/Exception.h"
#include "src/Engine/Game.h"
#include "src/Engine/Logger.h"
#include "src/States/StartState.h"

// Third party includes
#include <libfalltergeist.h>

using namespace Falltergeist;


int main(int argc, char *argv[])
{
    try
    {
        auto game = Game::getInstance();
        game->setState(new StartState());
        game->run();
        return 0;

    }
    catch(libfalltergeist::Exception &e)
    {
        Logger::critical() << e.message() << std::endl;
        return 1;
    }
    catch(Exception &e)
    {
        Logger::critical() << e.message() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        Logger::critical() << e.what() << std::endl;
    }

}

