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
#include <locale>

// Falltergeist includes
#include "CrossPlatform.h"
#include "Exception.h"
#include "Font.h"
#include "Game/Location.h"
#include "Graphics/Texture.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Ini/File.h"

// Third party includes
#include <libfalltergeist/Acm/File.h>
#include <libfalltergeist/Bio/File.h>
#include <libfalltergeist/Dat/File.h>
#include <libfalltergeist/Dat/Item.h>
#include <libfalltergeist/Fon/File.h>
#include <libfalltergeist/Frm/File.h>
#include <libfalltergeist/Gam/File.h>
#include <libfalltergeist/Gcd/File.h>
#include <libfalltergeist/Int/File.h>
#include <libfalltergeist/Map/File.h>
#include <libfalltergeist/Mve/File.h>
#include <libfalltergeist/Pal/File.h>
#include <libfalltergeist/Pro/File.h>
#include <libfalltergeist/Rix/File.h>
#include <libfalltergeist/Sve/File.h>
#include <libfalltergeist/Txt/CityFile.h>
#include <libfalltergeist/Txt/CSVBasedFile.h>
#include <libfalltergeist/Txt/MapsFile.h>
#include <libfalltergeist/Txt/WorldmapFile.h>
#include <SDL_image.h>

namespace Falltergeist
{

namespace
{
libfalltergeist::Pro::File* fetchProFileType(unsigned int PID)
{
    return ResourceManager::getInstance()->proFileType(PID);
}
}

ResourceManager::ResourceManager()
{
    std::vector<std::string> * files = CrossPlatform::findFalloutDataFiles();
    for (auto it = files->begin(); it != files->end(); ++it)
    {
        std::string path = CrossPlatform::findFalloutDataPath() + "/" + (*it);
        _datFiles.push_back(new libfalltergeist::Dat::File(path));
    }
}

ResourceManager::~ResourceManager()
{
}

// static
ResourceManager* ResourceManager::getInstance()
{
    return Base::Singleton<ResourceManager>::get();
}

libfalltergeist::Dat::Item* ResourceManager::datFileItem(std::string filename)
{
    std::locale loc;
    for (auto it = filename.begin(); it != filename.end(); it++)
    {
        *it = std::tolower(*it, loc);
    }
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
            libfalltergeist::Dat::Item* item = nullptr;
            if      (extension == "aaf") item = new libfalltergeist::Aaf::File(stream);
            else if (extension == "acm") item = new libfalltergeist::Acm::File(stream);
            else if (extension == "bio") item = new libfalltergeist::Bio::File(stream);
            else if (extension == "fon") item = new libfalltergeist::Fon::File(stream);
            else if (extension == "frm") item = new libfalltergeist::Frm::File(stream);
            else if (extension == "gam") item = new libfalltergeist::Gam::File(stream);
            else if (extension == "gcd") item = new libfalltergeist::Gcd::File(stream);
            else if (extension == "int") item = new libfalltergeist::Int::File(stream);
            else if (extension == "lst") item = new libfalltergeist::Lst::File(stream);
            else if (extension == "map") item = new libfalltergeist::Map::File(stream);
            else if (extension == "msg") item = new libfalltergeist::Msg::File(stream);
            else if (extension == "mve") item = new libfalltergeist::Mve::File(stream);
            else if (extension == "pal") item = new libfalltergeist::Pal::File(stream);
            else if (extension == "pro") item = new libfalltergeist::Pro::File(stream);
            else if (extension == "rix") item = new libfalltergeist::Rix::File(stream);
            else if (filename == "data/city.txt") item = new libfalltergeist::Txt::CityFile(stream);
            else if (filename == "data/enddeath.txt") item = new libfalltergeist::Txt::EndDeathFile(stream);
            else if (filename == "data/endgame.txt") item = new libfalltergeist::Txt::EndGameFile(stream);
            else if (filename == "data/genrep.txt") item = new libfalltergeist::Txt::GenRepFile(stream);
            else if (filename == "data/holodisk.txt") item = new libfalltergeist::Txt::HolodiskFile(stream);
            else if (filename == "data/karmavar.txt") item = new libfalltergeist::Txt::KarmaVarFile(stream);
            else if (filename == "data/maps.txt") item = new libfalltergeist::Txt::MapsFile(stream);
            else if (filename == "data/quests.txt") item = new libfalltergeist::Txt::QuestsFile(stream);
            else if (filename == "data/worldmap.txt") item = new libfalltergeist::Txt::WorldmapFile(stream);
            else
            {
                item = new libfalltergeist::Dat::Item(stream);
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
            Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM " << datfile->filename() << "]" << std::endl;
            return item;
        }
    }
    Logger::error("RESOURCE MANAGER") << "Loading file: " << filename << " [ NOT FOUND]" << std::endl;
    return 0;
}

libfalltergeist::Frm::File* ResourceManager::frmFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Frm::File*>(datFileItem(filename));
}

libfalltergeist::Pal::File* ResourceManager::palFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Pal::File*>(datFileItem(filename));
}

libfalltergeist::Lst::File* ResourceManager::lstFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Lst::File*>(datFileItem(filename));
}

libfalltergeist::Aaf::File* ResourceManager::aafFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Aaf::File*>(datFileItem(filename));
}

libfalltergeist::Acm::File* ResourceManager::acmFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Acm::File*>(datFileItem(filename));
}

libfalltergeist::Fon::File* ResourceManager::fonFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Fon::File*>(datFileItem(filename));
}

libfalltergeist::Gam::File* ResourceManager::gamFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Gam::File*>(datFileItem(filename));
}

libfalltergeist::Gcd::File* ResourceManager::gcdFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Gcd::File*>(datFileItem(filename));
}

libfalltergeist::Int::File* ResourceManager::intFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Int::File*>(datFileItem(filename));
}

libfalltergeist::Msg::File* ResourceManager::msgFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Msg::File*>(datFileItem(filename));
}

libfalltergeist::Mve::File* ResourceManager::mveFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Mve::File*>(datFileItem(filename));
}

libfalltergeist::Bio::File* ResourceManager::bioFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Bio::File*>(datFileItem(filename));
}

libfalltergeist::Map::File* ResourceManager::mapFileType(const std::string& filename)
{
    auto item = dynamic_cast<libfalltergeist::Map::File*>(datFileItem(filename));
    if (item)
    {
        item->setCallback(&fetchProFileType);
    }
    return item;
}

libfalltergeist::Pro::File* ResourceManager::proFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Pro::File*>(datFileItem(filename));
}

libfalltergeist::Rix::File* ResourceManager::rixFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Rix::File*>(datFileItem(filename));
}

libfalltergeist::Sve::File* ResourceManager::sveFileType(const std::string& filename)
{
    return dynamic_cast<libfalltergeist::Sve::File*>(datFileItem(filename));
}

libfalltergeist::Txt::CityFile* ResourceManager::cityTxt()
{
    return dynamic_cast<libfalltergeist::Txt::CityFile*>(datFileItem("data/city.txt"));
}

libfalltergeist::Txt::MapsFile* ResourceManager::mapsTxt()
{
    return dynamic_cast<libfalltergeist::Txt::MapsFile*>(datFileItem("data/maps.txt"));
}

libfalltergeist::Txt::WorldmapFile* ResourceManager::worldmapTxt()
{
    return dynamic_cast<libfalltergeist::Txt::WorldmapFile*>(datFileItem("data/worldmap.txt"));
}

libfalltergeist::Txt::EndDeathFile* ResourceManager::endDeathTxt()
{
    return dynamic_cast<libfalltergeist::Txt::EndDeathFile*>(datFileItem("data/enddeath.txt"));
}

libfalltergeist::Txt::EndGameFile* ResourceManager::endGameTxt()
{
    return dynamic_cast<libfalltergeist::Txt::EndGameFile*>(datFileItem("data/endgame.txt"));
}

libfalltergeist::Txt::GenRepFile* ResourceManager::genRepTxt()
{
    return dynamic_cast<libfalltergeist::Txt::GenRepFile*>(datFileItem("data/genrep.txt"));
}

libfalltergeist::Txt::HolodiskFile* ResourceManager::holodiskTxt()
{
    return dynamic_cast<libfalltergeist::Txt::HolodiskFile*>(datFileItem("data/holodisk.txt"));
}

libfalltergeist::Txt::KarmaVarFile* ResourceManager::karmaVarTxt()
{
    return dynamic_cast<libfalltergeist::Txt::KarmaVarFile*>(datFileItem("data/karmavar.txt"));
}

libfalltergeist::Txt::QuestsFile* ResourceManager::questsTxt()
{
    return dynamic_cast<libfalltergeist::Txt::QuestsFile*>(datFileItem("data/quests.txt"));
}

Graphics::Texture* ResourceManager::texture(const std::string& filename)
{
    if (_textures.find(filename) != _textures.end())
    {
        return _textures.at(filename);
    }

    std::string ext = filename.substr(filename.length() - 4);

    Graphics::Texture* texture = nullptr;

    if (ext == ".png")
    {
        // @fixme: this section looks quite ugly. we should try to do something with it someday
        SDL_Surface* tempSurface = IMG_Load(std::string(CrossPlatform::findFalltergeistDataPath() + "/" +filename).c_str());
        if (tempSurface == NULL)
        {
            throw Exception("ResourceManager::texture(name) - cannot load texture from file " + filename + ": " + IMG_GetError());
        }

        SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        SDL_Surface* tempSurface2 = SDL_ConvertSurface(tempSurface, pixelFormat, 0);
        texture = new Graphics::Texture(tempSurface2);

        SDL_FreeFormat(pixelFormat);
        SDL_FreeSurface(tempSurface);
        SDL_FreeSurface(tempSurface2);

    }
    else if (ext == ".rix")
    {
        auto rix = rixFileType(filename);
        if (!rix) return 0;
        texture = new Graphics::Texture(rix->width(), rix->height());
        texture->loadFromRGBA(rix->rgba());
    }
    else if (ext == ".frm")
    {
        auto frm = frmFileType(filename);
        if (!frm) return 0;
        texture = new Graphics::Texture(frm->width(), frm->height());
        texture->loadFromRGBA(frm->rgba(palFileType("color.pal")));
    }
    else
    {
        throw Exception("ResourceManager::surface() - unknown image type:" + filename);
    }

    _textures.insert(std::pair<std::string, Graphics::Texture*>(filename, texture));
    return texture;
}

std::shared_ptr<Font> ResourceManager::font(const std::string& filename, unsigned int color)
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

libfalltergeist::Pro::File* ResourceManager::proFileType(unsigned int PID)
{
    unsigned int typeId = PID >> 24;
    std::string listFile;
    switch ((OBJECT_TYPE)typeId)
    {
        case OBJECT_TYPE::ITEM:
            listFile += "proto/items/items.lst";
            break;
        case OBJECT_TYPE::CRITTER:
            listFile += "proto/critters/critters.lst";
            break;
        case OBJECT_TYPE::SCENERY:
            listFile += "proto/scenery/scenery.lst";
            break;
        case OBJECT_TYPE::WALL:
            listFile += "proto/walls/walls.lst";
            break;
        case OBJECT_TYPE::TILE:
            listFile += "proto/tiles/tiles.lst";
            break;
        case OBJECT_TYPE::MISC:
            listFile += "proto/misc/misc.lst";
            break;
        default:
            Logger::error() << "ResourceManager::proFileType(unsigned int) - wrong PID: " << PID << std::endl;
            return nullptr;
    }

    auto lst = lstFileType(listFile);

    unsigned int index = 0x00000FFF & PID;

    if (index > lst->strings()->size())
    {
        Logger::error() << "ResourceManager::proFileType(unsigned int) - LST size < PID: " << PID << std::endl;
        return nullptr;
    }

    std::string protoName = lst->strings()->at(index-1);

    switch ((OBJECT_TYPE)typeId)
    {
        case OBJECT_TYPE::ITEM:
            return proFileType("proto/items/" + protoName);
        case OBJECT_TYPE::CRITTER:
            return proFileType("proto/critters/" + protoName);
        case OBJECT_TYPE::SCENERY:
            return proFileType("proto/scenery/" + protoName);
        case OBJECT_TYPE::WALL:
            return proFileType("proto/walls/" + protoName);
        case OBJECT_TYPE::TILE:
            return proFileType("proto/tiles/" + protoName);
        case OBJECT_TYPE::MISC:
            return proFileType("proto/misc/" + protoName);
    }
    return nullptr;
}

void ResourceManager::unloadResources()
{
    _datFilesItems.clear();
}

libfalltergeist::Frm::File* ResourceManager::frmFileType(unsigned int FID)
{
    if (FIDtoFrmName(FID) == "") return 0;
    return frmFileType(FIDtoFrmName(FID));
}

libfalltergeist::Int::File* ResourceManager::intFileType(unsigned int SID)
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

    auto baseId = FID & 0x00000FFF;
    auto type = FID >> 24;

    switch ((FRM_TYPE)type)
    {
        case FRM_TYPE::ITEM:
            prefix = "art/items/";
            lstFile = "items.lst";
            break;
        case FRM_TYPE::CRITTER:
        {
            unsigned int weaponId = (FID & 0x0000F000) >> 12;
            unsigned int animId = (FID & 0x00FF0000) >> 16;
            unsigned int ID3 = (FID & 0xF0000000) >> 28;
            auto lst = ResourceManager::lstFileType("art/critters/critters.lst");
            std::string frmName = lst->strings()->at(baseId);
            std::string frmBase = frmName.substr(0, 6);

            if (animId >= 0x26 && animId <= 0x2F)
            {
                if (weaponId >= 0x0B || weaponId == 0) throw Exception("Critter weaponId unsupported value");
                frmBase += weaponId + 0x63;
                frmBase += animId + 0x3D;
            }
            else if (animId == 0x24)
            {
                frmBase += "ch";
            }
            else if (animId == 0x25)
            {
                frmBase += "cj";
            }
            else if (animId == 0x40)
            {
                frmBase += "na";
            }
            else if (animId >= 0x30)
            {
                frmBase += "r";
                frmBase += animId + 0x31;
            }
            else if (animId >= 0x14)
            {
                frmBase += "b";
                frmBase += animId + 0x4d;
            }
            else if (animId == 0x12)
            {
                if (weaponId == 0x01)
                {
                    frmBase += "dm";
                }
                else if (weaponId == 0x04)
                {
                    frmBase += "gm";
                }
                else
                {
                    frmBase += "as";
                }
            }
            else if (animId == 0x0D)
            {
                if (weaponId > 0)
                {
                    frmBase += weaponId + 0x63;
                    frmBase += "e";
                }
                else
                {
                    frmBase += "an";
                }
            }
            else if (animId <= 0x01 && weaponId > 0)
            {
                frmBase += weaponId + 0x63;
                frmBase += animId + 0x61;
            }
            else
            {
                frmBase += "a";
                frmBase += animId + 0x61;
            }

            std::string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
            frmBase += "." + extensions[ID3];

            return "art/critters/" + frmBase;
        }
        case FRM_TYPE::SCENERY:
            prefix = "art/scenery/";
            lstFile = "scenery.lst";
            break;
        case FRM_TYPE::WALL:
            prefix = "art/walls/";
            lstFile = "walls.lst";
            break;
        case FRM_TYPE::TILE:
            prefix = "art/tiles/";
            lstFile = "tiles.lst";
            break;
        case FRM_TYPE::MISC:
            prefix = "art/misc/";
            lstFile = "misc.lst";

            // Map scroll blockers
            if (baseId == 1) return "art/misc/scrblk.frm";
            break;
        case FRM_TYPE::INTERFACE:
            prefix = "art/intrface/";
            lstFile = "intrface.lst";
            break;
        case FRM_TYPE::INVENTORY:
            prefix = "art/inven/";
            lstFile = "inven.lst";
            break;
        default:
            throw Exception("ResourceManager::FIDtoFrmName - wrong type");
            break;
    }
    auto lst = lstFileType(prefix + lstFile);
    if (baseId >= lst->strings()->size())
    {
        Logger::error() << "ResourceManager::FIDtoFrmName(unsigned int) - LST size " << lst->strings()->size() << " <= frmID: " << baseId << " frmType: " << type << std::endl;
        return "";
    }
    return prefix + lst->strings()->at(baseId);
}

std::unordered_map<std::string, Graphics::Texture*>* ResourceManager::textures()
{
    return &_textures;
}

Game::Location* ResourceManager::gameLocation(unsigned int number)
{
    std::istream stream(datFileItem("data/maps.txt"));
    Ini::Parser iniParser(stream);
    auto ini = iniParser.parse();

    std::stringstream ss;
    ss << "map " << std::setw(3) << std::setfill('0') << number;

    auto section = ini->section(ss.str());
    if (!section)
    {
        return nullptr;
    }

    Game::Location* location = new Game::Location();

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
            location->setPipboyAllowed(property.second.boolValue());
        }
        else if (name == "saved")
        {
            location->setSaveable(property.second.boolValue());
        }
    }

    return location;
}

void ResourceManager::shutdown()
{
    for (auto texture : _textures)
    {
        delete texture.second;
    }

    for (auto item : _datFilesItems)
    {
        delete item.second;
    }

    for (auto dat : _datFiles)
    {
        delete dat;
    }

    unloadResources();
}

}
