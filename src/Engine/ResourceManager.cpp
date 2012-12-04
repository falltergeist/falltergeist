#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/CrossPlatform.h"
#include "../Fallout/DatFile.h"
#include "../Fallout/DatFileItem.h"
#include "../Fallout/FrmFileType.h"
#include "../Fallout/PalFileType.h"
#include "../Fallout/LstFileType.h"
#include "../Fallout/GcdFileType.h"
#include "../Fallout/MsgFileType.h"
#include "../Fallout/BioFileType.h"

namespace Falltergeist
{

std::list<DatFile *> * ResourceManager::_datFiles = new std::list<DatFile *>;

const char * _t(unsigned int number, const char * filename)
{
    MsgFileType * msg = ResourceManager::getMsgFileType(filename);
    if (!msg) throw Exception("Cant find msg file");
    return msg->getText(number);
}


ResourceManager::ResourceManager()
{
    std::string homepath = CrossPlatform::getHomePath();
    _datFiles->push_back(new DatFile(homepath + "/.fallout/master.dat"));
    //_datFiles->push_back(new DatFile(homepath + "/.fallout/critter.dat"));
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

AafFileType * ResourceManager::getAafFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        AafFileType * aaf = (*it)->getAafFileType(filename);
        if (aaf)
        {
            return aaf;
        }
    }
    return 0;
}


FonFileType * ResourceManager::getFonFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        FonFileType * fon = (*it)->getFonFileType(filename);
        if (fon)
        {
            return fon;
        }
    }
    return 0;
}

GcdFileType * ResourceManager::getGcdFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        GcdFileType * gcd = (*it)->getGcdFileType(filename);
        if (gcd)
        {
            return gcd;
        }
    }
    return 0;
}

MsgFileType * ResourceManager::getMsgFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        MsgFileType * msg = (*it)->getMsgFileType(filename);
        if (msg)
        {
            return msg;
        }
    }
    return 0;
}

BioFileType * ResourceManager::getBioFileType(std::string filename)
{
    std::list<DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        BioFileType * bio = (*it)->getBioFileType(filename);
        if (bio)
        {
            return bio;
        }
    }
    return 0;
}


Surface * ResourceManager::getSurface(std::string filename, int posX, int posY)
{
    FrmFileType * frm = getFrmFileType(filename);
    if (!frm)
    {
        std::cout << "No FRM "<< filename << " found" << std::endl;
        return 0;
    }
    PalFileType * pal = getPalFileType("color.pal");
    if (!pal)
    {
        std::cout << "No PAL color.pal found" << std::endl;
        return 0;
    }
    int width = frm->getDirections()[0].frames->width;
    int height = frm->getDirections()[0].frames->height;
    Surface * surface = new Surface(width,height);
    int i = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // 12 - frame data offset
            unsigned int colorIndex = frm->getDirections()[0].frames[0].data[i];
            unsigned int color = *pal->getColor(colorIndex);
            if (colorIndex == 0) color = 0;
            surface->setPixel(x,y,color);
            i++;
        }
    }
    surface->setX(posX);
    surface->setY(posY);
    SDL_SetColorKey(surface->getSurface(),SDL_SRCCOLORKEY, 0);
    return surface;
}

}
