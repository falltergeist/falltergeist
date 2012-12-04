#include "src/Engine/Game.h"
#include "src/Engine/Exception.h"
#include "src/Engine/Surface.h"
#include "src/Engine/ResourceManager.h"
#include "src/Engine/File.h"
#include "src/Fallout/DatFile.h"
#include "src/Fallout/DatFileItem.h"
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

using namespace Falltergeist;

int main()
{
    try
    {
        DatFile * dat = new DatFile("/home/alexeevdv/.fallout/master.dat");
        std::cout << dat->getItems()->front()->getFilename() << std::endl;
        //ResourceManager * rm = new ResourceManager();
        //std::cout << rm->getPalFileType("color.pal")->getColor(2) << std::endl;
        return 0;
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

