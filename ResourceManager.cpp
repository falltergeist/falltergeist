#include "ResourceManager.h"
#include "Surface.h"
#include "Fallout/DatFile.h"
#include "Fallout/DatFileItem.h"
#include "Fallout/FrmFileType.h"
#include "Fallout/PalFileType.h"
#include "Fallout/LstFileType.h"
#include "CrossPlatform.h"

namespace Falltergeist
{

 std::list<DatFile *> * ResourceManager::_datFiles = new std::list<DatFile *>;

ResourceManager::ResourceManager()
{
    std::string homepath = CrossPlatform::getHomePath();
    _datFiles->push_back(new DatFile(homepath + "/.fallout/master.dat"));
    _datFiles->push_back(new DatFile(homepath + "/.fallout/critter.dat"));
}

DatFileItem * ResourceManager::getDatFileItem(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        DatFileItem * item = (*it)->getItem(filename);
        if (item)
        {
            return item;
        }
    }
    return 0;
}

FrmFileType * ResourceManager::getFrmFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        FrmFileType * frm = (*it)->getFrmFileType(filename);
        if (frm)
        {
            return frm;
        }
    }
    return 0;
}

PalFileType * ResourceManager::getPalFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        PalFileType * pal = (*it)->getPalFileType(filename);
        if (pal)
        {
            return pal;
        }
    }
    return 0;
}

LstFileType * ResourceManager::getLstFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        LstFileType * lst = (*it)->getLstFileType(filename);
        if (lst)
        {
            return lst;
        }
    }
    return 0;
}


Surface * ResourceManager::getSurface(std::string filename)
{
    FrmFileType * frm = getFrmFileType(filename);
    if (!frm) return 0;
    PalFileType * pal = getPalFileType("color.pal");
    if (!pal) return 0;

    int width = frm->getDirections()[0].frames->width;
    int height = frm->getDirections()[0].frames->height;
    Surface * surface = new Surface(width,height);
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // 12 - frame data offset
            unsigned int colorIndex = frm->getData()[i + 12];
            unsigned int color = *pal->getColor(colorIndex);
            if (colorIndex == 0) color = 0;
            surface->setPixel(x,y,color);
            i++;
        }
    }
    SDL_SetColorKey(surface->getSurface(),SDL_SRCCOLORKEY, 0);
    return surface;
}

}
