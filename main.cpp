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

using namespace Falltergeist;

int main()
{
    try
    {
        //DatFile * master = new DatFile("/home/alexeevdv/.fallout/master.dat");
        //std::cout << master->getFrmFileType("art/intrface/mainmenu.frm")->getDirections()[0].frames[0].width;
        //for (std::list<VirtualFile *>::iterator it = master->getItems()->begin(); it != master->getItems()->end(); ++it)
        //{
        //    std::cout << (*it)->getFilename() << " : " << (*it)->getSize() << std::endl;
        //}
        //return 0;
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

