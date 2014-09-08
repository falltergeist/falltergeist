/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include <fstream>
#include <iostream>

// Falltergeist includes
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Font.h"

// Third party includes

namespace Falltergeist
{

std::vector<libfalltergeist::DatFile*> ResourceManager::_datFiles;
std::map<std::string, libfalltergeist::DatFileItem*> ResourceManager::_datFilesItems;
std::map<std::string, Surface*> ResourceManager::_surfaces;
std::map<std::string, Texture*> ResourceManager::_textures;
std::map<std::string, Font*> ResourceManager::_fonts;

ResourceManager::ResourceManager()
{
    std::vector<std::string> * files = CrossPlatform::findFalloutDataFiles();
    for (auto it = files->begin(); it != files->end(); ++it)
    {
        std::string path = CrossPlatform::findFalloutDataPath() + "/" + (*it);
        _datFiles.push_back(new libfalltergeist::DatFile(path));
    }
}

void ResourceManager::extract(std::string path)
{
    std::vector<libfalltergeist::DatFile *>::iterator it;
    for (it = _datFiles.begin(); it != _datFiles.end(); ++it)
    {
        std::vector<libfalltergeist::DatFileItem *>::iterator itt;
        for (itt = (*it)->items()->begin(); itt != (*it)->items()->end(); ++itt)
        {
            std::string file = path + (*itt)->filename();
            std::fstream stream;
            stream.open(file, std::ios_base::out);

            if (stream.is_open())
            {
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
    while (!_datFiles.empty())
    {
        delete _datFiles.back();
        _datFiles.pop_back();
    }
    
    for (auto it = _datFilesItems.begin(); it != _datFilesItems.end(); ++it)
    {
        delete it->second;
    }
    
    for (auto it = _surfaces.begin(); it != _surfaces.end(); ++it)
    {
        delete it->second;
    }
}

libfalltergeist::DatFileItem * ResourceManager::datFileItem(std::string filename)
{    
    // Return item from cache
    if (_datFilesItems.find(filename) != _datFilesItems.end())
    {
        //debug("[RESOURCE MANAGER] - Loading file: " + filename + " [FROM CACHE]", DEBUG_INFO);
        return _datFilesItems.at(filename);
    }

    // Searching file in Fallout data directory
    {
        std::string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
        std::ifstream* stream = new std::ifstream();
        stream->open(path, std::ios_base::binary);
        if (stream->is_open())
        {
            debug("[RESOURCE MANAGER] - Loading file: " + filename + " [FROM FALLOUT DATA DIR]", DEBUG_INFO);
        }
        else
        {
            path = CrossPlatform::findFalltergeistDataPath() + "/" + filename;
            stream->open(path, std::ios_base::binary);
            if (stream->is_open())
            {
                debug("[RESOURCE MANAGER] - Loading file: " + filename + " [FROM FALLTERGEIST DATA DIR]", DEBUG_INFO);
            }
        }

        if (stream->is_open())
        {

            std::string extension = filename.substr(filename.length() - 3, 3);
            libfalltergeist::DatFileItem* item;
                 if (extension == "aaf") item = new libfalltergeist::AafFileType(stream);
            else if (extension == "acm") item = new libfalltergeist::AcmFileType(stream);
            else if (extension == "bio") item = new libfalltergeist::BioFileType(stream);
            else if (extension == "fon") item = new libfalltergeist::FonFileType(stream);
            else if (extension == "frm") item = new libfalltergeist::FrmFileType(stream);
            else if (extension == "gam") item = new libfalltergeist::GamFileType(stream);
            else if (extension == "gcd") item = new libfalltergeist::GcdFileType(stream);
            else if (extension == "int") item = new libfalltergeist::IntFileType(stream);
            else if (extension == "lst") item = new libfalltergeist::LstFileType(stream);
            else if (extension == "map") item = new libfalltergeist::MapFileType(stream);
            else if (extension == "msg") item = new libfalltergeist::MsgFileType(stream);
            else if (extension == "mve") item = new libfalltergeist::MveFileType(stream);
            else if (extension == "pal") item = new libfalltergeist::PalFileType(stream);
            else if (extension == "pro") item = new libfalltergeist::ProFileType(stream);
            else if (extension == "rix") item = new libfalltergeist::RixFileType(stream);
            else
            {
                item = new libfalltergeist::DatFileItem(stream);
            }

            item->setFilename(filename);
            _datFilesItems.insert(std::make_pair(filename, item));
            return item;
        }
        delete stream;
    }

    // Search in DAT files
    std::vector<libfalltergeist::DatFile*>::iterator it;
    for (it = _datFiles.begin(); it != _datFiles.end(); ++it)
    {
        libfalltergeist::DatFileItem* item = (*it)->item(filename.c_str());
        if (item)
        {
            _datFilesItems.insert(std::make_pair(filename, item));
            debug("[RESOURCE MANAGER] - Loading file: " + filename + " [FROM "+ (*it)->filename() + "]", DEBUG_INFO);
            return item;
        }
    }
    debug("[RESOURCE MANAGER] - Loading file: " + filename + " [ NOT FOUND]", DEBUG_ERROR);
    return 0;
}

libfalltergeist::FrmFileType* ResourceManager::frmFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::FrmFileType*>(datFileItem(filename));
}

libfalltergeist::PalFileType* ResourceManager::palFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::PalFileType*>(datFileItem(filename));
}

libfalltergeist::LstFileType* ResourceManager::lstFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::LstFileType*>(datFileItem(filename));
}

libfalltergeist::AafFileType* ResourceManager::aafFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::AafFileType*>(datFileItem(filename));
}

libfalltergeist::AcmFileType* ResourceManager::acmFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::AcmFileType*>(datFileItem(filename));
}

libfalltergeist::FonFileType* ResourceManager::fonFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::FonFileType*>(datFileItem(filename));
}

libfalltergeist::GamFileType* ResourceManager::gamFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::GamFileType*>(datFileItem(filename));
}

libfalltergeist::GcdFileType* ResourceManager::gcdFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::GcdFileType*>(datFileItem(filename));
}

libfalltergeist::IntFileType* ResourceManager::intFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::IntFileType*>(datFileItem(filename));
}

libfalltergeist::MsgFileType* ResourceManager::msgFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::MsgFileType*>(datFileItem(filename));
}

libfalltergeist::MveFileType* ResourceManager::mveFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::MveFileType*>(datFileItem(filename));
}

libfalltergeist::BioFileType* ResourceManager::bioFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::BioFileType*>(datFileItem(filename));
}

libfalltergeist::MapFileType* ResourceManager::mapFileType(std::string filename)
{
    auto item = dynamic_cast<libfalltergeist::MapFileType*>(datFileItem(filename));
    if (item)
    {
        item->setCallback(&ResourceManager::proFileType);
    }
    return item;
}

libfalltergeist::ProFileType* ResourceManager::proFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::ProFileType*>(datFileItem(filename));
}

libfalltergeist::RixFileType* ResourceManager::rixFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::RixFileType*>(datFileItem(filename));
}

Surface * ResourceManager::surface(std::string filename, int posX, int posY, unsigned int direction, unsigned int frame)
{
    if (_surfaces.find(filename) != _surfaces.end())
    {
        return _surfaces.at(filename);
    }
    
    std::string ext = filename.substr(filename.length() - 4);

    Surface * surface;
    
    if (ext == ".rix")
    {
        libfalltergeist::RixFileType* rix = rixFileType(filename);
        if (!rix) return 0;
        surface = new Surface(rix);
    }
    else if (ext == ".frm")
    {
        libfalltergeist::FrmFileType* frm = frmFileType(filename);
        if (!frm) return 0;
        surface = new Surface(frm, direction, frame);        
    }
    else
    {
        throw Exception("ResourceManager::surface() - unknow image type:" + filename);
    }
    
    surface->setX(posX);
    surface->setY(posY);

    _surfaces.insert(std::pair<std::string, Surface*>(filename, surface));
    return surface;
}

Texture* ResourceManager::texture(std::string filename)
{
    if (_textures.find(filename) != _textures.end())
    {
        return _textures.at(filename);
    }

    std::string ext = filename.substr(filename.length() - 4);

    Texture* texture = 0;

    if (ext == ".rix")
    {
        auto rix = rixFileType(filename);
        if (!rix) return 0;
        texture = new Texture(rix->width(), rix->height());
        texture->loadFromRGBA(rix->rgba());
    }
    else if (ext == ".frm")
    {
        auto frm = frmFileType(filename);
        if (!frm) return 0;
        texture = new Texture(frm->width(), frm->height());
        texture->loadFromRGBA(frm->rgba(palFileType("color.pal")));
    }
    else
    {
        throw Exception("ResourceManager::surface() - unknow image type:" + filename);
    }

    _textures.insert(std::pair<std::string, Texture*>(filename, texture));
    return texture;
}

Font* ResourceManager::font(std::string filename, unsigned int color)
{
    std::string fontname = filename + std::to_string(color);

    if (_fonts.find(fontname) != _fonts.end())
    {
        return _fonts.at(fontname);
    }

    auto font = new Font(filename, color);
    _fonts.insert(std::pair<std::string, Font*>(fontname, font));
    return font;
}



libfalltergeist::ProFileType* ResourceManager::proFileType(unsigned int PID)
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
            debug("ResourceManager::proFileType(unsigned int) - wrong PID: " + std::to_string(PID), DEBUG_ERROR);
            return 0;
    }

    libfalltergeist::LstFileType * lst = lstFileType(listFile);

    unsigned int index = 0x00000FFF & PID;

    if (index > lst->strings()->size())
    {
        debug("ResourceManager::proFileType(unsigned int) - LST size < PID: " + std::to_string(PID), DEBUG_ERROR);
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
    for (auto it = _datFilesItems.begin(); it != _datFilesItems.end(); ++it)
    {
        delete it->second;
    }
    _datFilesItems.clear();
    
    for (auto it = _surfaces.begin(); it != _surfaces.end(); ++it)
    {
        delete it->second;
    }
    _surfaces.clear();

}

libfalltergeist::FrmFileType * ResourceManager::frmFileType(unsigned int FID)
{
    if (FIDtoFrmName(FID) == "") return 0;
    return frmFileType(FIDtoFrmName(FID));
}



Surface * ResourceManager::surface(unsigned int FID, unsigned int direction, unsigned int frame)
{
    if (FIDtoFrmName(FID) == "") return 0;
    return surface(FIDtoFrmName(FID), direction, frame);
}

libfalltergeist::IntFileType * ResourceManager::intFileType(unsigned int SID)
{
    auto lst = lstFileType("scripts/scripts.lst");
    if (SID >= lst->strings()->size())
    {
        throw Exception("ResourceManager::intFileType() - wrong SID: " + std::to_string(SID));
    }

    return intFileType("scripts/" + lst->strings()->at(SID));
}

std::string ResourceManager::FIDtoFrmName(unsigned int FID)
{
    std::string prefix;
    std::string lstFile;

    auto id = FID & 0x00000FFF;
    auto type = FID >> 24;

    switch(type)
    {
        case libfalltergeist::FrmFileType::TYPE_ITEM:
            prefix = "art/items/";
            lstFile = "items.lst";
            break;
        case libfalltergeist::FrmFileType::TYPE_CRITTER:
        {
            unsigned int frmId = FID & 0x00000FFF;
            unsigned int ID1 = (FID & 0x0000F000) >> 12;
            unsigned int ID2 = (FID & 0x00FF0000) >> 16;
            unsigned int ID3 = (FID & 0xF0000000) >> 28;
            auto lst = ResourceManager::lstFileType("art/critters/critters.lst");
            std::string frmName = lst->strings()->at(frmId);
            std::string frmBase = frmName.substr(0, 6);

            if (ID2 >= 0x26 && ID2 <= 0x2F)
            {
                if (ID1 >= 0x0B || ID1 == 0) throw Exception("Critter ID1 unsupported value");
                frmBase += ID1 + 0x63;
                frmBase += ID2 + 0x3D;
            }
            else if (ID2 == 0x24)
            {
                frmBase += "ch";
            }
            else if (ID2 == 0x25)
            {
                frmBase += "cj";
            }
            else if (ID2 == 0x40)
            {
                frmBase += "na";
            }
            else if (ID2 >= 0x30)
            {
                frmBase += "r";
                frmBase += ID2 + 0x31;
            }
            else if (ID2 >= 0x14)
            {
                frmBase += "b";
                frmBase += ID2 + 0x4d;
            }
            else if (ID2 == 0x12)
            {
                if (ID1 == 0x01)
                {
                    frmBase += "dm";
                }
                else if (ID1 == 0x04)
                {
                    frmBase += "gm";
                }
                else
                {
                    frmBase += "as";
                }
            }
            else if (ID2 == 0x0D)
            {
                if (ID1 > 0)
                {
                    frmBase += ID1 + 0x63;
                    frmBase += "e";
                }
                else
                {
                    frmBase += "an";
                }
            }
            else if (ID2 <= 0x01 && ID1 > 0)
            {
                frmBase += ID1 + 0x63;
                frmBase += ID2 + 0x61;
            }
            else
            {
                frmBase += "a";
                frmBase += ID2 + 0x61;
            }

            std::string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
            frmBase += "." + extensions[ID3];

            return "art/critters/" + frmBase;
        }
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

            // ???
            if (id == 1) return "";
            // Map scroll blockers
            if (id == 12) return "art/intrface/msef001.frm";
            // Exit tiles
            if (id >= 16 && id <= 23) return "art/intrface/msef001.frm";
            // ???
            if (id == 24) return "art/intrface/msef001.frm";

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
    auto lst = lstFileType(prefix + lstFile);
    if (id >= lst->strings()->size())
    {
        debug("ResourceManager::FIDtoFrmName(unsigned int) - LST size " + std::to_string(lst->strings()->size()) + " <= frmID: " + std::to_string(id) + " frmType: " + std::to_string(type), DEBUG_ERROR);
        return "";
    }
    return prefix + lst->strings()->at(id);
}

}
