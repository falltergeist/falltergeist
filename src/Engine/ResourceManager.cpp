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

// C++ standard includes
#include <string>
#include <iostream>
#include <fstream>

// Falltergeist includes
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

std::vector<libfalltergeist::DatFile *> * ResourceManager::_datFiles = new std::vector<libfalltergeist::DatFile *>;
std::map<std::string, libfalltergeist::DatFileItem *> * ResourceManager::_datFilesItems = new std::map<std::string, libfalltergeist::DatFileItem *>;
std::map<std::string, Surface *> * ResourceManager::_surfaces = new std::map<std::string, Surface *>;
std::string ResourceManager::_dataPath = "";

std::string _t(unsigned int number, std::string filename)
{
    libfalltergeist::MsgFileType * msg = ResourceManager::msgFileType(filename);
    if (!msg) throw Exception("Cant find msg file");
    return msg->message(number)->text();
}


ResourceManager::ResourceManager()
{
    _dataPath.clear();
    _dataPath.append(CrossPlatform::findDataPath());
    //std::cout << "Datapath: " << _dataPath << std::endl;
    std::vector<std::string> * files = findDataFiles();
    std::vector<std::string>::iterator it;
    for (it = files->begin(); it != files->end(); ++it)
    {
        std::string path(_dataPath);
        path.append("/").append(*it);
        _datFiles->push_back(new libfalltergeist::DatFile(path));
    }
}

void ResourceManager::extract(std::string path)
{
    std::vector<libfalltergeist::DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        std::vector<libfalltergeist::DatFileItem *>::iterator itt;
        for (itt = (*it)->items()->begin(); itt != (*it)->items()->end(); ++itt)
        {
            std::string file = path + (*itt)->filename();
            std::fstream stream;
            stream.open(file.c_str(), std::ios_base::out);

            if (stream.is_open())
            {
                //stream.write((*itt)->getData(), (*itt)->size());
                stream.close();
            }
            else
            {
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
        std::string alias = findFileAlias(_dataPath, filename);
        if (alias.length())
        {
            std::string path = _dataPath + "/" + alias;
            std::ifstream * stream = new std::ifstream();
            stream->open(path.c_str(), std::ios_base::binary);
            if (stream->is_open())
            {
                std::string extension = filename.substr(filename.length() - 3, 3);

                libfalltergeist::DatFileItem * item;
                     if (extension == "aaf") item = new libfalltergeist::AafFileType(stream);
                else if (extension == "bio") item = new libfalltergeist::BioFileType(stream);
                else if (extension == "frm") item = new libfalltergeist::FrmFileType(stream);
                else if (extension == "gcd") item = new libfalltergeist::GcdFileType(stream);
                else if (extension == "lst") item = new libfalltergeist::LstFileType(stream);
                else if (extension == "msg") item = new libfalltergeist::MsgFileType(stream);
                else if (extension == "pal") item = new libfalltergeist::PalFileType(stream);
                else if (extension == "pro") item = new libfalltergeist::ProFileType(stream);
                else
                {
                    item = new libfalltergeist::DatFileItem(stream);
                }

                item->setFilename((char *) filename.c_str());
                _datFilesItems->insert(std::make_pair(filename, item));
                std::cout << " [FROM DATA DIR]" << std::endl;
                return item;
            }
            delete stream;
        }
    }

    // Search in DAT files
    std::vector<libfalltergeist::DatFile *>::iterator it;
    for (it = _datFiles->begin(); it != _datFiles->end(); ++it)
    {
        libfalltergeist::DatFileItem * item = (*it)->item(filename.c_str());
        if (item)
        {
            _datFilesItems->insert(std::make_pair(filename, item));
            std::cout << " [FROM DAT FILE]" << std::endl;
            return item;
        }
    }
    std::cout << " [NOT FOUND]" << std::endl;
    return 0;
}

libfalltergeist::FrmFileType * ResourceManager::frmFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::FrmFileType *>(datFileItem(filename));
}

libfalltergeist::PalFileType * ResourceManager::palFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::PalFileType *>(datFileItem(filename));
}

libfalltergeist::LstFileType * ResourceManager::lstFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::LstFileType *>(datFileItem(filename));
}

libfalltergeist::AafFileType * ResourceManager::aafFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::AafFileType *>(datFileItem(filename));
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
    return dynamic_cast<libfalltergeist::GcdFileType *>(datFileItem(filename));
}

libfalltergeist::MsgFileType * ResourceManager::msgFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::MsgFileType *>(datFileItem(filename));
}

libfalltergeist::BioFileType * ResourceManager::bioFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::BioFileType *>(datFileItem(filename));
}

libfalltergeist::MapFileType * ResourceManager::mapFileType(std::string filename)
{
    libfalltergeist::DatFileItem * item = datFileItem(filename);
    if (item)
    {
        return item->asMapFileType(&ResourceManager::proFileType);
    }
    return 0;
}

libfalltergeist::ProFileType * ResourceManager::proFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::ProFileType *>(datFileItem(filename));
}


Surface * ResourceManager::surface(std::string filename, int posX, int posY, unsigned int direction, unsigned int frame)
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
    Surface * surface = new Surface(frm, direction, frame);

    surface->setX(posX);
    surface->setY(posY);


    _surfaces->insert(std::pair<std::string, Surface *>(filename, surface));
    return surface;
}

libfalltergeist::ProFileType * ResourceManager::proFileType(unsigned int PID)
{
    unsigned int typeId = PID >> 24;
    std::string listFile;
    switch (typeId)
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
            listFile += "proto/items/items.lst";
            break;
        case libfalltergeist::ProFileType::TYPE_CRITTER:
            listFile += "proto/critters/critters.lst";
            break;
        case libfalltergeist::ProFileType::TYPE_SCENERY:
            listFile += "proto/scenery/scenery.lst";
            break;
        case libfalltergeist::ProFileType::TYPE_WALL:
            listFile += "proto/walls/walls.lst";
            break;
        case libfalltergeist::ProFileType::TYPE_TILE:
            listFile += "proto/tiles/tiles.lst";
            break;
        case libfalltergeist::ProFileType::TYPE_MISC:
            listFile += "proto/misc/misc.lst";
            break;
        default:
            std::cout << "Wrong PID: " << std::dec << PID << std::endl;
            return 0;
    }

    libfalltergeist::LstFileType * lst = lstFileType(listFile);

    unsigned int index = 0x00000FFF & PID;

    if (index > lst->strings()->size())
    {
        std::cout << listFile << std::endl;
        std::cout << "Lst size: " << std::dec << lst->strings()->size() << std::endl;
        std::cout << "Wrong PID: " << std::dec << index << std::endl;
        return 0;
    }

    std::string protoName = lst->strings()->at(index-1);

    switch (typeId)
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
            return proFileType("proto/items/" + protoName);
        case libfalltergeist::ProFileType::TYPE_CRITTER:
            return proFileType("proto/critters/" + protoName);
        case libfalltergeist::ProFileType::TYPE_SCENERY:
            return proFileType("proto/scenery/" + protoName);
        case libfalltergeist::ProFileType::TYPE_WALL:
            return proFileType("proto/walls/" + protoName);
        case libfalltergeist::ProFileType::TYPE_TILE:
            return proFileType("proto/tiles/" + protoName);
        case libfalltergeist::ProFileType::TYPE_MISC:
            return proFileType("proto/misc/" + protoName);
    }
    return 0;
}

void ResourceManager::unloadResources()
{
    _surfaces->clear();
    _datFilesItems->clear();
}

libfalltergeist::FrmFileType * ResourceManager::frmFileType(unsigned int FID)
{
    std::string prefix;
    std::string lstFile;
    switch(FID >> 24)
    {
        case libfalltergeist::FrmFileType::TYPE_ITEM:
            prefix = "art/items/";
            lstFile = "items.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_CRITTER:
            prefix = "art/critters/";
            lstFile = "critters.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_SCENERY:
            prefix = "art/scenery/";
            lstFile = "scenery.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_WALL:
            prefix = "art/walls/";
            lstFile = "walls.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_TILE:
            prefix = "art/tiles/";
            lstFile = "tiles.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_BACKGROUND:
            prefix = "art/backgrnd/";
            lstFile = "backgrnd.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_INTERFACE:
            prefix = "art/intrface/";
            lstFile = "intrface.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_INVENTORY:
            prefix = "art/inven/";
            lstFile = "inven.lst";
            break;
    }
    libfalltergeist::LstFileType * lst = lstFileType(prefix + lstFile);
    unsigned int frmId = 0x0000FFFF & FID;

    if (frmId >= lst->strings()->size())
    {
        //std::cout << "Size: " << lst->strings()->size() << " frmId: " << frmId << std::endl;
        return 0;
    }

    //std::cout << std::hex << FID << std::endl;
    return frmFileType(prefix + lst->strings()->at(frmId));
}



Surface * ResourceManager::surface(unsigned int FID, unsigned int direction, unsigned int frame)
{
    std::string prefix;
    std::string lstFile;
    switch(FID >> 24)
    {
        case libfalltergeist::FrmFileType::TYPE_ITEM:
            prefix = "art/items/";
            lstFile = "items.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_CRITTER:
            prefix = "art/critters/";
            lstFile = "critters.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_SCENERY:
            prefix = "art/scenery/";
            lstFile = "scenery.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_WALL:
            prefix = "art/walls/";
            lstFile = "walls.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_TILE:
            prefix = "art/tiles/";
            lstFile = "tiles.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_BACKGROUND:
            prefix = "art/backgrnd/";
            lstFile = "backgrnd.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_INTERFACE:
            prefix = "art/intrface/";
            lstFile = "intrface.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_INVENTORY:
            prefix = "art/inven/";
            lstFile = "inven.lst";
            break;
    }
    libfalltergeist::LstFileType * lst = lstFileType(prefix + lstFile);
    unsigned int frmId = 0x0000FFFF & FID;

    if (frmId >= lst->strings()->size())
    {
        std::cout << "Size: " << lst->strings()->size() << " frmId: " << frmId << std::endl;
        return 0;
    }

    //std::cout << std::hex << FID << std::endl;
    return surface(prefix + lst->strings()->at(frmId), direction, frame);
}

}
