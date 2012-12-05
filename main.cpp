#include "src/Engine/Game.h"
#include "src/Engine/Exception.h"
#include "src/Engine/Surface.h"
#include "src/Engine/ResourceManager.h"
#include "src/Engine/File.h"
#include "src/Engine/VirtualFile.h"
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
        //VirtualFile * virtualFile = new VirtualFile("test.bin");
        //virtualFile->setByteOrder(0);
        //(*virtualFile) << 1 << 2 << 3;
        //virtualFile->setByteOrder(1);
        File * file = new File("test.bin");
        //file->save();
        //unsigned char chr;
        std::cout << "Filesize: " << file->getSize() << std::endl;
        file->setPosition(file->getSize());
        (*file) << 1 << 2 << 3;
        //char * data = new char[3];
        //file->setPosition(0);
        //file->readBytes(data, 3);
        //delete [] data;

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

