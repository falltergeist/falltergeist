#include "Game.h"
#include "Exception.h"
#include "States/StartState.h"
#include "Fallout/DatFile.h"
#include "Fallout/DatFileItem.h"
#include "Fallout/FrmFileType.h"
#include "Fallout/PalFileType.h"
#include "Fallout/LstFileType.h"
#include "Fallout/FonFileType.h"
#include "Fallout/AafFileType.h"
#include "Fallout/GcdFileType.h"
#include "Fallout/MsgFileType.h"
#include "Surface.h"
#include "ResourceManager.h"
#include "SDL/SDL.h"
#include <algorithm>

using namespace Falltergeist;

int main()
{
    try
    {
        Game * game = new Game(640,480,32);
        game->setState(new StartState(game));
        game->run();
        return 0;
    }
    catch(Exception &e)
    {
        std::cout << e.getMessage() << std::endl;
        return 1;
    }
}

