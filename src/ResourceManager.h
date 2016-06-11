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

#ifndef FALLTERGEIST_RESOURCEMANAGER_H
#define FALLTERGEIST_RESOURCEMANAGER_H

// C++ standard includes
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>


// Falltergeist includes
#include "Base/Singleton.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Aaf { class File; }
namespace Fon { class File; }
namespace Acm { class File; }
namespace Bio { class File; }
namespace Dat
{
class File;
class Item;
}
namespace Frm { class File; }
namespace Fon { class File; }
namespace Gam { class File; }
namespace Gcd { class File; }
namespace Pal { class File; }
namespace Int { class File; }
namespace Lip { class File; }
namespace Lst { class File; }
namespace Map { class File; }
namespace Msg { class File; }
namespace Mve { class File; }
namespace Pro { class File; }
namespace Pro { class File; }
namespace Rix { class File; }
namespace Sve { class File; }
namespace Txt
{
class CityFile;
class MapsFile;
class WorldmapFile;

template <typename T>
class CSVBasedFile;

struct EndDeath;
struct EndGame;
struct GenRep;
struct Holodisk;
struct KarmaVar;
struct Quest;

typedef CSVBasedFile<EndDeath> EndDeathFile;
typedef CSVBasedFile<EndGame> EndGameFile;
typedef CSVBasedFile<GenRep> GenRepFile;
typedef CSVBasedFile<Holodisk> HolodiskFile;
typedef CSVBasedFile<KarmaVar> KarmaVarFile;
typedef CSVBasedFile<Quest> QuestsFile;
}
}
}

namespace Falltergeist
{
namespace Game
{
    class Location;
}
namespace Graphics
{
    class Texture;
    class Font;
    class Shader;
}


class ResourceManager
{

public:
    static ResourceManager* getInstance();

    Format::Aaf::File* aafFileType(const std::string& filename);
    Format::Acm::File* acmFileType(const std::string& filename);
    Format::Bio::File* bioFileType(const std::string& filename);
    Format::Dat::Item* datFileItem(std::string filename);
    Format::Frm::File* frmFileType(const std::string& filename);
    Format::Frm::File* frmFileType(unsigned int FID);
    Format::Fon::File* fonFileType(const std::string& filename);
    Format::Gam::File* gamFileType(const std::string& filename);
    Format::Gcd::File* gcdFileType(const std::string& filename);
    Format::Pal::File* palFileType(const std::string& filename);
    Format::Int::File* intFileType(const std::string& filename);
    Format::Int::File* intFileType(unsigned int SID);
    Format::Lip::File* lipFileType(const std::string& filename);
    Format::Lst::File* lstFileType(const std::string& filename);
    Format::Map::File* mapFileType(const std::string& filename);
    Format::Msg::File* msgFileType(const std::string& filename);
    Format::Mve::File* mveFileType(const std::string& filename);
    Format::Pro::File* proFileType(const std::string& filename);
    Format::Pro::File* proFileType(unsigned int PID);
    Format::Rix::File* rixFileType(const std::string& filename);
    Format::Sve::File* sveFileType(const std::string& filename);

    Format::Txt::CityFile* cityTxt();
    Format::Txt::MapsFile* mapsTxt();
    Format::Txt::WorldmapFile* worldmapTxt();
    Format::Txt::EndDeathFile* endDeathTxt();
    Format::Txt::EndGameFile* endGameTxt();
    Format::Txt::GenRepFile* genRepTxt();
    Format::Txt::HolodiskFile* holodiskTxt();
    Format::Txt::KarmaVarFile* karmaVarTxt();
    Format::Txt::QuestsFile* questsTxt();

    Graphics::Texture* texture(const std::string& filename);
    Graphics::Font* font(const std::string& filename = "font1.aaf");
    Graphics::Shader* shader(const std::string& filename);
    void unloadResources();
    std::string FIDtoFrmName(unsigned int FID);
    Game::Location* gameLocation(unsigned int number);
    void shutdown();

protected:
    friend class Base::Singleton<ResourceManager>;

    std::vector<std::unique_ptr<Format::Dat::File>> _datFiles;
    std::vector<std::unique_ptr<Format::Dat::Item>> _datItems;
    std::unordered_map<std::string, Format::Dat::Item*> _datItemMap;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Texture>> _textures;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Font>> _fonts;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Shader>> _shaders;

    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    Format::Dat::Item* _createItemByName(const std::string& filename, std::ifstream* stream);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
