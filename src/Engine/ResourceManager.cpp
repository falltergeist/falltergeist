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
#include <string>
#include <iostream>
#include <fstream>

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

std::vector<libfalltergeist::DatFile *> * ResourceManager::_datFiles = new std::vector<libfalltergeist::DatFile *>;
std::map<std::string, libfalltergeist::DatFileItem *> * ResourceManager::_datFilesItems = new std::map<std::string, libfalltergeist::DatFileItem *>;
std::map<std::string, Surface *> * ResourceManager::_surfaces = new std::map<std::string, Surface *>;

const char * _t(unsigned int number, const char * filename)
{
    libfalltergeist::MsgFileType * msg = ResourceManager::msgFileType(filename);
    if (!msg) throw Exception("Cant find msg file");
    return msg->message(number)->text();
}


ResourceManager::ResourceManager()
{
    std::vector<std::string> * files = findDataFiles();
    std::vector<std::string>::iterator it;
    for (it = files->begin(); it != files->end(); ++it)
    {
        std::string path(CrossPlatform::findDataPath());
        path.append("/");
        path.append((*it));
        _datFiles->push_back(new libfalltergeist::DatFile(path.c_str()));
    }
}

void ResourceManager::extract(const char * path)
{
    std::vector<libfalltergeist::DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        std::vector<libfalltergeist::DatFileItem *>::iterator itt;
        for (itt = (*it)->items()->begin(); itt != (*it)->items()->end(); ++itt)
        {
            std::string file(path);
            file.append((*itt)->filename());
            std::fstream stream;
            stream.open(file.c_str(), std::ios_base::out);

            if (stream.is_open())
            {
                //std::cout << file.c_str() << " [OK]" << std::endl;
                stream.write((*itt)->getData(), (*itt)->size());
                stream.close();
            }
            else
            {
                std::cout << file.c_str() << " [FAIL]" << std::endl;
            }
        }
    }
}

ResourceManager::~ResourceManager()
{
    while (!_datFiles->empty())
    {
        delete _datFiles->back();
        _datFiles->pop_back();
    }

    // @TODO
    //while (!_datFilesItems->empty())
    //{
    //    delete _datFilesItems->back();
    //    _datFilesItems->pop_back();
    //}

}

libfalltergeist::DatFileItem * ResourceManager::datFileItem(std::string filename)
{
    std::cout << "[RESOURCE MANAGER] - Loading file: " << filename;
    // Return item from cache
    if (_datFilesItems->find(filename) != _datFilesItems->end())
    {
        std::cout << " - [FROM CACHE]" << std::endl;
        return _datFilesItems->at(filename);
    }


    // Searching file in Data directory
    {
        const char * alias = findFileAlias((char *) findDataPath(), (char *) filename.c_str());
        if (alias)
        {
            std::string path(findDataPath());
            path.append("/").append(alias);
            std::ifstream stream(path.c_str());
            if (stream.is_open())
            {
                libfalltergeist::DatFileItem * item = new libfalltergeist::DatFileItem(0);
                item->isOpened(true);
                item->setFilename((char *) filename.c_str());
                item->setCompressed(false);
                stream.seekg(0,std::ios::end);
                item->setUnpackedSize(stream.tellg());
                item->setPackedSize(stream.tellg());
                stream.seekg(0, std::ios::beg);
                char * data = new char[item->unpackedSize()];
                stream.read(data, item->unpackedSize());
                item->setData(data);
                _datFilesItems->insert(std::make_pair(filename, item));
                std::cout << " - [FROM DATA DIR]" << std::endl;
                return item;
            }
        }
    }

    std::vector<libfalltergeist::DatFile *>::reverse_iterator it;
    for (it = _datFiles->rbegin(); it != _datFiles->rend(); ++it)
    {
        libfalltergeist::DatFileItem * item = (*it)->item(filename.c_str());
        if (item)
        {
            _datFilesItems->insert(std::make_pair(filename, item));
            std::cout << " - [FROM DAT FILE " <<  (*it)->pathToFile() << "]" << std::endl;
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
        return item->asGcdFileType();
    }
    return 0;
}

libfalltergeist::MsgFileType * ResourceManager::msgFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asMsgFileType();
    }
    return 0;
}

libfalltergeist::BioFileType * ResourceManager::bioFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asBioFileType();
    }
    return 0;
}


Surface * ResourceManager::surface(std::string filename, int posX, int posY)
{
    if (_surfaces->find(filename) != _surfaces->end())
    {
        return _surfaces->at(filename);
    }

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
            surface->pixel(x, y, color);
            i++;
        }
    }
    surface->x(posX);
    surface->y(posY);
    SDL_SetColorKey(surface->sdl_surface(), SDL_SRCCOLORKEY, 0);
    _surfaces->insert(std::pair<std::string, Surface *>(filename, surface));
    return surface;
}


}
