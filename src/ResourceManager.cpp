/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <memory>

// Falltergeist includes
#include "CrossPlatform.h"
#include "Exception.h"
#include "Format/Acm/File.h"
#include "Format/Bio/File.h"
#include "Format/Dat/File.h"
#include "Format/Dat/Item.h"
#include "Format/Fon/File.h"
#include "Format/Frm/File.h"
#include "Format/Gam/File.h"
#include "Format/Gcd/File.h"
#include "Format/Int/File.h"
#include "Format/Lip/File.h"
#include "Format/Lst/File.h"
#include "Format/Map/File.h"
#include "Format/Msg/File.h"
#include "Format/Mve/File.h"
#include "Format/Pal/File.h"
#include "Format/Pro/File.h"
#include "Format/Rix/File.h"
#include "Format/Sve/File.h"
#include "Format/Txt/CityFile.h"
#include "Format/Txt/CSVBasedFile.h"
#include "Format/Txt/MapsFile.h"
#include "Format/Txt/WorldmapFile.h"
#include "Game/Location.h"
#include "Graphics/Font.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Ini/File.h"

// Third party includes
#include <SDL_image.h>
#include <Graphics/Font/AAF.h>
#include <Graphics/Font/FON.h>

namespace Falltergeist
{

using namespace std;

namespace
{
Format::Pro::File* fetchProFileType(unsigned int PID)
{
    return ResourceManager::getInstance()->proFileType(PID);
}
}

ResourceManager::ResourceManager()
{
    for (auto filename : CrossPlatform::findFalloutDataFiles())
    {
        string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
        _datFiles.push_back(std::make_unique<Format::Dat::File>(path));
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

Format::Dat::Item* ResourceManager::datFileItem(string filename)
{
    std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

    // Return item from cache
    auto itemIt = _datItemMap.find(filename);
    if (itemIt != _datItemMap.end())
    {
        return itemIt->second;
    }

    // Searching file in Fallout data directory
    {
        string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
        ifstream stream;
        stream.open(path, ios_base::binary);
        if (stream.is_open())
        {
            Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLOUT DATA DIR]" << endl;
        }
        else
        {
            path = CrossPlatform::findFalltergeistDataPath() + "/" + filename;
            stream.open(path, ios_base::binary);
            if (stream.is_open())
            {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLTERGEIST DATA DIR]" << endl;
            }
        }

        if (stream.is_open())
        {
            Format::Dat::Item* item = _createItemByName(filename, &stream);
            item->setFilename(filename);
            _datItems.push_back(unique_ptr<Format::Dat::Item>(item));
            _datItemMap.insert(make_pair(filename, item));
            return item;
        }
    }

    // Search in DAT files
    for (auto& datfile : _datFiles)
    {
        auto item = datfile->item(filename.c_str());
        if (item)
        {
            Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM " << datfile->filename() << "]" << endl;
            _datItemMap.insert(make_pair(filename, item));
            return item;
        }
    }
    Logger::error("RESOURCE MANAGER") << "Loading file: " << filename << " [ NOT FOUND]" << endl;
    return 0;
}

Format::Dat::Item* ResourceManager::_createItemByName(const string& filename, ifstream* stream)
{
    string extension = filename.substr(filename.length() - 3, 3);
    if      (extension == "aaf") return new Format::Aaf::File(stream);
    else if (extension == "acm") return new Format::Acm::File(stream);
    else if (extension == "bio") return new Format::Bio::File(stream);
    else if (extension == "fon") return new Format::Fon::File(stream);
    else if (extension == "frm") return new Format::Frm::File(stream);
    else if (extension == "gam") return new Format::Gam::File(stream);
    else if (extension == "gcd") return new Format::Gcd::File(stream);
    else if (extension == "int") return new Format::Int::File(stream);
    else if (extension == "lip") return new Format::Lip::File(stream);
    else if (extension == "lst") return new Format::Lst::File(stream);
    else if (extension == "map") return new Format::Map::File(stream);
    else if (extension == "msg") return new Format::Msg::File(stream);
    else if (extension == "mve") return new Format::Mve::File(stream);
    else if (extension == "pal") return new Format::Pal::File(stream);
    else if (extension == "pro") return new Format::Pro::File(stream);
    else if (extension == "rix") return new Format::Rix::File(stream);
    else if (filename == "data/city.txt")       return new Format::Txt::CityFile(stream);
    else if (filename == "data/enddeath.txt")   return new Format::Txt::EndDeathFile(stream);
    else if (filename == "data/endgame.txt")    return new Format::Txt::EndGameFile(stream);
    else if (filename == "data/genrep.txt")     return new Format::Txt::GenRepFile(stream);
    else if (filename == "data/holodisk.txt")   return new Format::Txt::HolodiskFile(stream);
    else if (filename == "data/karmavar.txt")   return new Format::Txt::KarmaVarFile(stream);
    else if (filename == "data/maps.txt")       return new Format::Txt::MapsFile(stream);
    else if (filename == "data/quests.txt")     return new Format::Txt::QuestsFile(stream);
    else if (filename == "data/worldmap.txt")   return new Format::Txt::WorldmapFile(stream);
    else
    {
        return new Format::Dat::Item(stream);
    }
}

Format::Frm::File* ResourceManager::frmFileType(const string& filename)
{
    return dynamic_cast<Format::Frm::File*>(datFileItem(filename));
}

Format::Pal::File* ResourceManager::palFileType(const string& filename)
{
    return dynamic_cast<Format::Pal::File*>(datFileItem(filename));
}

Format::Lip::File* ResourceManager::lipFileType(const string& filename)
{
    return dynamic_cast<Format::Lip::File*>(datFileItem(filename));
}

Format::Lst::File* ResourceManager::lstFileType(const string& filename)
{
    return dynamic_cast<Format::Lst::File*>(datFileItem(filename));
}

Format::Aaf::File* ResourceManager::aafFileType(const string& filename)
{
    return dynamic_cast<Format::Aaf::File*>(datFileItem(filename));
}

Format::Acm::File* ResourceManager::acmFileType(const string& filename)
{
    return dynamic_cast<Format::Acm::File*>(datFileItem(filename));
}

Format::Fon::File* ResourceManager::fonFileType(const string& filename)
{
    return dynamic_cast<Format::Fon::File*>(datFileItem(filename));
}

Format::Gam::File* ResourceManager::gamFileType(const string& filename)
{
    return dynamic_cast<Format::Gam::File*>(datFileItem(filename));
}

Format::Gcd::File* ResourceManager::gcdFileType(const string& filename)
{
    return dynamic_cast<Format::Gcd::File*>(datFileItem(filename));
}

Format::Int::File* ResourceManager::intFileType(const string& filename)
{
    return dynamic_cast<Format::Int::File*>(datFileItem(filename));
}

Format::Msg::File* ResourceManager::msgFileType(const string& filename)
{
    return dynamic_cast<Format::Msg::File*>(datFileItem(filename));
}

Format::Mve::File* ResourceManager::mveFileType(const string& filename)
{
    return dynamic_cast<Format::Mve::File*>(datFileItem(filename));
}

Format::Bio::File* ResourceManager::bioFileType(const string& filename)
{
    return dynamic_cast<Format::Bio::File*>(datFileItem(filename));
}

Format::Map::File* ResourceManager::mapFileType(const string& filename)
{
    auto item = dynamic_cast<Format::Map::File*>(datFileItem(filename));
    if (item)
    {
        item->setCallback(&fetchProFileType);
    }
    return item;
}

Format::Pro::File* ResourceManager::proFileType(const string& filename)
{
    return dynamic_cast<Format::Pro::File*>(datFileItem(filename));
}

Format::Rix::File* ResourceManager::rixFileType(const string& filename)
{
    return dynamic_cast<Format::Rix::File*>(datFileItem(filename));
}

Format::Sve::File* ResourceManager::sveFileType(const string& filename)
{
    return dynamic_cast<Format::Sve::File*>(datFileItem(filename));
}

Format::Txt::CityFile* ResourceManager::cityTxt()
{
    return dynamic_cast<Format::Txt::CityFile*>(datFileItem("data/city.txt"));
}

Format::Txt::MapsFile* ResourceManager::mapsTxt()
{
    return dynamic_cast<Format::Txt::MapsFile*>(datFileItem("data/maps.txt"));
}

Format::Txt::WorldmapFile* ResourceManager::worldmapTxt()
{
    return dynamic_cast<Format::Txt::WorldmapFile*>(datFileItem("data/worldmap.txt"));
}

Format::Txt::EndDeathFile* ResourceManager::endDeathTxt()
{
    return dynamic_cast<Format::Txt::EndDeathFile*>(datFileItem("data/enddeath.txt"));
}

Format::Txt::EndGameFile* ResourceManager::endGameTxt()
{
    return dynamic_cast<Format::Txt::EndGameFile*>(datFileItem("data/endgame.txt"));
}

Format::Txt::GenRepFile* ResourceManager::genRepTxt()
{
    return dynamic_cast<Format::Txt::GenRepFile*>(datFileItem("data/genrep.txt"));
}

Format::Txt::HolodiskFile* ResourceManager::holodiskTxt()
{
    return dynamic_cast<Format::Txt::HolodiskFile*>(datFileItem("data/holodisk.txt"));
}

Format::Txt::KarmaVarFile* ResourceManager::karmaVarTxt()
{
    return dynamic_cast<Format::Txt::KarmaVarFile*>(datFileItem("data/karmavar.txt"));
}

Format::Txt::QuestsFile* ResourceManager::questsTxt()
{
    return dynamic_cast<Format::Txt::QuestsFile*>(datFileItem("data/quests.txt"));
}

Graphics::Texture* ResourceManager::texture(const string& filename)
{
    if (_textures.count(filename))
    {
        return _textures.at(filename).get();
    }

    string ext = filename.substr(filename.length() - 4);

    Graphics::Texture* texture = nullptr;

    if (ext == ".png")
    {
        // @fixme: this section looks quite ugly. we should try to do something with it someday
        SDL_Surface* tempSurface = IMG_Load(string(CrossPlatform::findFalltergeistDataPath() + "/" +filename).c_str());
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
        if (!rix) return nullptr;
        texture = new Graphics::Texture(rix->width(), rix->height());
        texture->loadFromRGBA(rix->rgba());
    }
    else if (ext == ".frm")
    {
        auto frm = frmFileType(filename);
        if (!frm) return nullptr;
        texture = new Graphics::Texture(frm->width(), frm->height());
        texture->loadFromRGBA(frm->rgba(palFileType("color.pal")));
        texture->setMask(*frm->mask(palFileType("color.pal")));
    }
    else
    {
        throw Exception("ResourceManager::surface() - unknown image type:" + filename);
    }

    _textures.insert(make_pair(filename, unique_ptr<Graphics::Texture>(texture)));
    return texture;
}

Graphics::Font* ResourceManager::font(const string& filename)
{

    if (_fonts.count(filename))
    {
        return _fonts.at(filename).get();
    }

    std::string ext = filename.substr(filename.length() - 4);
    Graphics::Font* fontPtr = nullptr;

    if (ext == ".aaf")
    {
        fontPtr = new Graphics::AAF(filename);
    }
    else if (ext == ".fon")
    {
        fontPtr = new Graphics::FON(filename);
    }
    _fonts.insert(make_pair(filename, unique_ptr<Graphics::Font>(fontPtr)));
    return fontPtr;
}


Graphics::Shader* ResourceManager::shader(const string& filename)
{
    if (_shaders.count(filename))
    {
        return _shaders.at(filename).get();
    }

    Graphics::Shader* shader = new Graphics::Shader(filename);

    _shaders.insert(make_pair(filename, unique_ptr<Graphics::Shader>(shader)));
    return shader;
}


Format::Pro::File* ResourceManager::proFileType(unsigned int PID)
{
    unsigned int typeId = PID >> 24;
    string listFile;
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
            Logger::error() << "ResourceManager::proFileType(unsigned int) - wrong PID: " << PID << endl;
            return nullptr;
    }

    auto lst = lstFileType(listFile);

    unsigned int index = 0x00000FFF & PID;

    if (index > lst->strings()->size())
    {
        Logger::error() << "ResourceManager::proFileType(unsigned int) - LST size < PID: " << PID << endl;
        return nullptr;
    }

    string protoName = lst->strings()->at(index-1);

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
    _datItems.clear();
    _datItemMap.clear();
}

Format::Frm::File* ResourceManager::frmFileType(unsigned int FID)
{
    if (FIDtoFrmName(FID) == "") return 0;
    return frmFileType(FIDtoFrmName(FID));
}

Format::Int::File* ResourceManager::intFileType(unsigned int SID)
{
    auto lst = lstFileType("scripts/scripts.lst");
    if (SID >= lst->strings()->size())
    {
        throw Exception("ResourceManager::intFileType() - wrong SID: " + std::to_string(SID));
    }

    return intFileType("scripts/" + lst->strings()->at(SID));
}

string ResourceManager::FIDtoFrmName(unsigned int FID)
{
    string prefix;
    string lstFile;

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
            string frmName = lst->strings()->at(baseId);
            string frmBase = frmName.substr(0, 6);

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

            string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
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
        Logger::error() << "ResourceManager::FIDtoFrmName(unsigned int) - LST size " << lst->strings()->size() << " <= frmID: " << baseId << " frmType: " << type << endl;
        return "";
    }
    return prefix + lst->strings()->at(baseId);
}

Game::Location* ResourceManager::gameLocation(unsigned int number)
{
    istream stream(datFileItem("data/maps.txt"));
    Ini::Parser iniParser(stream);
    auto ini = iniParser.parse();

    stringstream ss;
    ss << "map " << setw(3) << setfill('0') << number;

    auto section = ini->section(ss.str());
    if (!section)
    {
        return nullptr;
    }

    Game::Location* location = new Game::Location();

    for (auto property : *section.get())
    {
        string name = property.first;
        Logger::critical() << name << endl;
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
    unloadResources();
}

}
