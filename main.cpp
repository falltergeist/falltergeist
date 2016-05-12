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
#include <memory>

// Falltergeist includes
#include "src/Exception.h"
#include "src/Game/Game.h"
#include "src/Logger.h"
#include "src/Settings.h"
#include "src/State/Start.h"

#include "src/ResourceManager.h"
#include <cassert>
#include <iostream>

// Third party includes

using namespace Falltergeist;

namespace
{
void FIDTest()
{
    std::cout << "start test\n";
    for (unsigned int fid = 0; fid < UINT_MAX; ++fid)
    {
        std::string old_frmName;
        std::string new_frmName;
        bool expectException = false;
        std::string exceptionMessage;
        try
        {
            old_frmName = ResourceManager::getInstance()->FIDtoFrmName_DEPRECATED(fid);
        }
        catch(const Exception& ex)
        {
            exceptionMessage = ex.what();
            expectException = true;
        }

        try
        {
            new_frmName = ResourceManager::getInstance()->FIDtoFrmName(fid);
            assert(old_frmName == new_frmName);
        }
        catch(const Exception& ex)
        {
            assert(expectException);
            assert(std::string(ex.what()) == exceptionMessage);
        }

        if (fid % 10000 == 0)
        {
            std::cout << "FID = " << fid << "\n";
        }
    }
    std::cout << "end test\n";
}
}

int main(int argc, char* argv[])
{
    try
    {
        auto game = Game::Game::getInstance();
        game->init(std::unique_ptr<Settings>(new Settings()));

        FIDTest();
        return 0;

        game->setState(new State::Start());
        game->run();
        game->shutdown();
        return 0;
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

