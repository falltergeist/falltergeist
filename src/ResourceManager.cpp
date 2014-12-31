/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include <sstream>
#include <iomanip>

// Falltergeist includes
#include "CrossPlatform.h"
#include "Exception.h"
#include "Font.h"
#include "Graphics/Texture.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Ini/File.h"
#include "Ini/Parser.h"
#include "Game/Location.h"

// Third party includes

namespace Falltergeist
{

std::vector<std::shared_ptr<libfalltergeist::DatFile>> ResourceManager::_datFiles;
std::map<std::string, std::shared_ptr<libfalltergeist::DatFileItem>> ResourceManager::_datFilesItems;
std::map<std::string, Texture*> ResourceManager::_textures;
std::map<std::string, std::shared_ptr<Font>> ResourceManager::_fonts;
std::map<unsigned int, Game::GameLocation*> ResourceManager::_gameLocations;

ResourceManager::ResourceManager()
{
    std::vector<std::string> * files = CrossPlatform::findFalloutDataFiles();
    for (auto it = files->begin(); it != files->end(); ++it)
    {
        std::string path = CrossPlatform::findFalloutDataPath() + "/" + (*it);
        _datFiles.push_back(std::shared_ptr<libfalltergeist::DatFile>(new libfalltergeist::DatFile(path)));
    }
}

ResourceManager::~ResourceManager()
{
    for (auto it = _textures.begin(); it != _textures.end(); ++it)
    {
        delete it->second;
    }

    for (auto it = _gameLocations.begin(); it != _gameLocations.end(); ++it)
    {
        delete it->second;
    }
}



std::shared_ptr<libfalltergeist::DatFileItem> ResourceManager::datFileItem(std::string filename)
{
    // Return item from cache
    if (_datFilesItems.find(filename) != _datFilesItems.end())
    {
        return _datFilesItems.at(filename);
    }

    // Searching file in Fallout data directory
    {
        std::string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
        std::ifstream* stream = new std::ifstream();
        stream->open(path, std::ios_base::binary);
        if (stream->is_open())
        {
            Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLOUT DATA DIR]" << std::endl;
        }
        else
        {
            path = CrossPlatform::findFalltergeistDataPath() + "/" + filename;
            stream->open(path, std::ios_base::binary);
            if (stream->is_open())
            {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLTERGEIST DATA DIR]" << std::endl;
            }
        }

        if (stream->is_open())
        {

            std::string extension = filename.substr(filename.length() - 3, 3);
            std::shared_ptr<libfalltergeist::DatFileItem> item;
            if      (extension == "aaf") item = std::shared_ptr<libfalltergeist::AafFileType>(new libfalltergeist::AafFileType(stream));
            else if (extension == "acm") item = std::shared_ptr<libfalltergeist::AcmFileType>(new libfalltergeist::AcmFileType(stream));
            else if (extension == "bio") item = std::shared_ptr<libfalltergeist::BioFileType>(new libfalltergeist::BioFileType(stream));
            else if (extension == "fon") item = std::shared_ptr<libfalltergeist::FonFileType>(new libfalltergeist::FonFileType(stream));
            else if (extension == "frm") item = std::shared_ptr<libfalltergeist::FrmFileType>(new libfalltergeist::FrmFileType(stream));
            else if (extension == "gam") item = std::shared_ptr<libfalltergeist::GamFileType>(new libfalltergeist::GamFileType(stream));
            else if (extension == "gcd") item = std::shared_ptr<libfalltergeist::GcdFileType>(new libfalltergeist::GcdFileType(stream));
            else if (extension == "int") item = std::shared_ptr<libfalltergeist::IntFileType>(new libfalltergeist::IntFileType(stream));
            else if (extension == "lst") item = std::shared_ptr<libfalltergeist::LstFileType>(new libfalltergeist::LstFileType(stream));
            else if (extension == "map") item = std::shared_ptr<libfalltergeist::MapFileType>(new libfalltergeist::MapFileType(stream));
            else if (extension == "msg") item = std::shared_ptr<libfalltergeist::MsgFileType>(new libfalltergeist::MsgFileType(stream));
            else if (extension == "mve") item = std::shared_ptr<libfalltergeist::MveFileType>(new libfalltergeist::MveFileType(stream));
            else if (extension == "pal") item = std::shared_ptr<libfalltergeist::PalFileType>(new libfalltergeist::PalFileType(stream));
            else if (extension == "pro") item = std::shared_ptr<libfalltergeist::ProFileType>(new libfalltergeist::ProFileType(stream));
            else if (extension == "rix") item = std::shared_ptr<libfalltergeist::RixFileType>(new libfalltergeist::RixFileType(stream));
            else
            {
                item = std::shared_ptr<libfalltergeist::DatFileItem>(new libfalltergeist::DatFileItem(stream));
            }

            item->setFilename(filename);
            _datFilesItems.insert(std::make_pair(filename, item));
            return item;
        }
        delete stream;
    }

    // Search in DAT files
    for (auto datfile : _datFiles)
    {
        auto item = datfile->item(filename.c_str());
        if (item)
        {
            _datFilesItems.insert(std::make_pair(filename, item));
            Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM " << datfile->filename() << "]" << std::endl;
            return item;
        }
    }
    Logger::error("RESOURCE MANAGER") << "Loading file: " << filename << " [ NOT FOUND]" << std::endl;
    return 0;
}

std::shared_ptr<libfalltergeist::FrmFileType> ResourceManager::frmFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::FrmFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::PalFileType> ResourceManager::palFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::PalFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::LstFileType> ResourceManager::lstFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::LstFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::AafFileType> ResourceManager::aafFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::AafFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::AcmFileType> ResourceManager::acmFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::AcmFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::FonFileType> ResourceManager::fonFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::FonFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::GamFileType> ResourceManager::gamFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::GamFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::GcdFileType> ResourceManager::gcdFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::GcdFileType>(datFileItem(filename));
}

libfalltergeist::IntFileType* ResourceManager::intFileType(std::string filename)
{
    return dynamic_cast<libfalltergeist::IntFileType*>(datFileItem(filename).get());
}

std::shared_ptr<libfalltergeist::MsgFileType> ResourceManager::msgFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::MsgFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::MveFileType> ResourceManager::mveFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::MveFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::BioFileType> ResourceManager::bioFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::BioFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::MapFileType> ResourceManager::mapFileType(std::string filename)
{
    auto item = std::dynamic_pointer_cast<libfalltergeist::MapFileType>(datFileItem(filename));
    if (item)
    {
        item->setCallback(&ResourceManager::proFileType);
    }
    return item;
}

std::shared_ptr<libfalltergeist::ProFileType> ResourceManager::proFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::ProFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::RixFileType> ResourceManager::rixFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::RixFileType>(datFileItem(filename));
}

std::shared_ptr<libfalltergeist::SveFileType> ResourceManager::sveFileType(std::string filename)
{
    return std::dynamic_pointer_cast<libfalltergeist::SveFileType>(datFileItem(filename));
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
        throw Exception("ResourceManager::surface() - unknown image type:" + filename);
    }

    _textures.insert(std::pair<std::string, Texture*>(filename, texture));
    return texture;
}

std::shared_ptr<Font> ResourceManager::font(std::string filename, unsigned int color)
{
    std::string fontname = filename + std::to_string(color);

    if (_fonts.find(fontname) != _fonts.end())
    {
        return _fonts.at(fontname);
    }

    auto font = std::shared_ptr<Font>(new Font(filename, color));
    _fonts.insert(std::pair<std::string, std::shared_ptr<Font>>(fontname, font));
    return font;
}



std::shared_ptr<libfalltergeist::ProFileType> ResourceManager::proFileType(unsigned int PID)
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
            Logger::error() << "ResourceManager::proFileType(unsigned int) - wrong PID: " << PID << std::endl;
            return 0;
    }

    auto lst = lstFileType(listFile);

    unsigned int index = 0x00000FFF & PID;

    if (index > lst->strings()->size())
    {
        Logger::error() << "ResourceManager::proFileType(unsigned int) - LST size < PID: " << PID << std::endl;
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
    _datFilesItems.clear();
}

std::shared_ptr<libfalltergeist::FrmFileType> ResourceManager::frmFileType(unsigned int FID)
{
    if (FIDtoFrmName(FID) == "") return 0;
    return frmFileType(FIDtoFrmName(FID));
}

libfalltergeist::IntFileType* ResourceManager::intFileType(unsigned int SID)
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
        default:
            throw Exception("ResourceManager::FIDtoFrmName - wrong type");
            break;
    }
    auto lst = lstFileType(prefix + lstFile);
    if (id >= lst->strings()->size())
    {
        Logger::error() << "ResourceManager::FIDtoFrmName(unsigned int) - LST size " << lst->strings()->size() << " <= frmID: " << id << " frmType: " << type << std::endl;
        return "";
    }
    return prefix + lst->strings()->at(id);
}

std::map<std::string, Texture*>* ResourceManager::textures()
{
    return &_textures;
}

Game::GameLocation* ResourceManager::gameLocation(unsigned int number)
{
    if (_gameLocations.find(number) != _gameLocations.end())
    {
        return _gameLocations.at(number);
    }

    std::istream stream(datFileItem("data/maps.txt").get());
    Ini::Parser iniParser(stream);
    auto ini = iniParser.parse();

    std::stringstream ss;
    ss << "map " << std::setw(3) << std::setfill('0') << number;

    auto section = ini->section(ss.str());
    if (!section) return 0;

    Game::GameLocation* location = new Game::GameLocation();

    for (auto property : *section.get())
    {
        std::string name = property.first;
        Logger::critical() << name << std::endl;
        if (name == "lookup_name")
        {
            location->setName(property.second.value());
        }
        else if (name == "map_name")
        {
            location->setFilename("maps/" + property.second.value()+ ".map");
        }
        else if (name == "music")
        {
            location->setMusic(property.second.value());
        }
        else if (name == "pipboy_active")
        {
            location->setPipboy(property.second.boolValue());
        }
        else if (name == "saved")
        {
            location->setSaveable(property.second.boolValue());
        }
    }

    _gameLocations.insert(std::make_pair(number, location));

    return _gameLocations.at(number);
}

}
