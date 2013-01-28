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

#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/CrossPlatform.h"
#include <iostream>

namespace Falltergeist
{

std::list<libfalltergeist::DatFile *> * ResourceManager::_datFiles = new std::list<libfalltergeist::DatFile *>;

const char * _t(unsigned int number, const char * filename)
{
    libfalltergeist::MsgFileType * msg = ResourceManager::msgFileType(filename);
    if (!msg) throw Exception("Cant find msg file");
    //return msg->getText(number);
}


ResourceManager::ResourceManager()
{
    std::string path = CrossPlatform::homePath();
    path += "/.fallout/master.dat";
    _datFiles->push_back(new libfalltergeist::DatFile((char *)path.c_str()));
    //_datFiles->push_back(new DatFile(homepath + "/.fallout/critter.dat"));
}

libfalltergeist::DatFileItem * ResourceManager::datFileItem(std::string filename)
{
    std::list<libfalltergeist::DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        libfalltergeist::DatFileItem * item = (*it)->item((char *)filename.c_str());
        if (item)
        {
            return item;
        }
    }
    return 0;
}

libfalltergeist::FrmFileType * ResourceManager::frmFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asFrmFileType();
    }
    return 0;
}

libfalltergeist::PalFileType * ResourceManager::palFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asPalFileType();
    }
    return 0;
}

libfalltergeist::LstFileType * ResourceManager::lstFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asLstFileType();
    }
    return 0;
}

libfalltergeist::AafFileType * ResourceManager::aafFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asAafFileType();
    }
    return 0;
}


libfalltergeist::FonFileType * ResourceManager::fonFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        //return item->asFonFileType();
    }
    return 0;
}

libfalltergeist::GcdFileType * ResourceManager::gcdFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        //return item->asGcdFileType();
    }
    return 0;
}

libfalltergeist::MsgFileType * ResourceManager::msgFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        //return item->asMsgFileType();
    }
    return 0;
}

libfalltergeist::BioFileType * ResourceManager::bioFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        //return item->asBioFileType();
    }
    return 0;
}


Surface * ResourceManager::surface(std::string filename, int posX, int posY)
{
    libfalltergeist::FrmFileType * frm = frmFileType(filename);
    if (!frm)
    {
        std::cout << "No FRM "<< filename << " found" << std::endl;
        return 0;
    }
    libfalltergeist::PalFileType * pal = palFileType("color.pal");
    if (!pal)
    {
        std::cout << "No PAL color.pal found" << std::endl;
        return 0;
    }

    int width = frm->directions()->at(0)->frames()->at(0)->width();
    int height = frm->directions()->at(0)->frames()->at(0)->height();
    Surface * surface = new Surface(width,height);

    int i = 0;
    for (int y = 0; y != height; ++y)
    {
        for (int x = 0; x != width; ++x)
        {
            unsigned int colorIndex = frm->directions()->at(0)->frames()->at(0)->colorIndexes()->at(i);
            unsigned int color = *pal->color(colorIndex);
            surface->setPixel(x, y, color);
            i++;
        }
    }
    surface->setX(posX);
    surface->setY(posY);
    SDL_SetColorKey(surface->surface(), SDL_SRCCOLORKEY, 0);
    return surface;
}

}
