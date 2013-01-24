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

#include "src/Engine/Game.h"
#include "src/Engine/Exception.h"
#include "src/Engine/Surface.h"
#include "src/Engine/ResourceManager.h"
#include "src/Engine/File.h"
#include "src/Engine/VirtualFile.h"
#include "src/Fallout/DatFile.h"
#include "src/Fallout/FrmFileType.h"
#include "src/Fallout/PalFileType.h"
#include "src/Fallout/LstFileType.h"
#include "src/Fallout/FonFileType.h"
#include "src/Fallout/AafFileType.h"
#include "src/Fallout/GcdFileType.h"
#include "src/Fallout/MsgFileType.h"
#include "src/States/StartState.h"
#include <SDL/SDL.h>
#include <algorithm>
#include "lib/libfalltergeist/libfalltergeist.h"

using namespace Falltergeist;


int main(int argc, char *argv[])
{
    try
    {
        ResourceManager * rm = new ResourceManager();
        Surface * surface = rm->getSurface("art/intrface/mainmenu.frm");
        SDL_SaveBMP(surface->getSurface(), "test.bmp");

        //Game * game = new Game(640,480,32);
        //game->setState(new StartState(game));
        //game->run();
        return 0;
    }
    catch(Exception &e)
    {
        std::cout << e.getMessage() << std::endl;
        return 1;
    }
}

