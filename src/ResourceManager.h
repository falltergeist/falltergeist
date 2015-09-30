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
#include <libfalltergeist/Lst/File.h>
#include <libfalltergeist/Msg/File.h>
#include <libfalltergeist/Msg/Message.h>

namespace libfalltergeist
{
namespace Aaf { class File; }
namespace Acm { class File; }
namespace Bio { class File; }
namespace Dat
{
class File;
class Item;
}
namespace Frm { class File; }
namespace Frm { class File; }
namespace Fon { class File; }
namespace Gam { class File; }
namespace Gcd { class File; }
namespace Pal { class File; }
namespace Int { class File; }
namespace Int { class File; }
namespace Map { class File; }
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

namespace Falltergeist
{
namespace Game
{
    class Location;
}
namespace Graphics
{
    class Texture;
}

class Font;

class ResourceManager
{

public:
    static ResourceManager* getInstance();

    libfalltergeist::Aaf::File* aafFileType(const std::string& filename);
    libfalltergeist::Acm::File* acmFileType(const std::string& filename);
    libfalltergeist::Bio::File* bioFileType(const std::string& filename);
    libfalltergeist::Dat::Item* datFileItem(std::string filename);
    libfalltergeist::Frm::File* frmFileType(const std::string& filename);
    libfalltergeist::Frm::File* frmFileType(unsigned int FID);
    libfalltergeist::Fon::File* fonFileType(const std::string& filename);
    libfalltergeist::Gam::File* gamFileType(const std::string& filename);
    libfalltergeist::Gcd::File* gcdFileType(const std::string& filename);
    libfalltergeist::Pal::File* palFileType(const std::string& filename);
    libfalltergeist::Int::File* intFileType(const std::string& filename);
    libfalltergeist::Int::File* intFileType(unsigned int SID);
    libfalltergeist::Lst::File* lstFileType(const std::string& filename);
    libfalltergeist::Map::File* mapFileType(const std::string& filename);
    libfalltergeist::Msg::File* msgFileType(const std::string& filename);
    libfalltergeist::Mve::File* mveFileType(const std::string& filename);
    libfalltergeist::Pro::File* proFileType(const std::string& filename);
    libfalltergeist::Pro::File* proFileType(unsigned int PID);
    libfalltergeist::Rix::File* rixFileType(const std::string& filename);
    libfalltergeist::Sve::File* sveFileType(const std::string& filename);

    libfalltergeist::Txt::CityFile* cityTxt();
    libfalltergeist::Txt::MapsFile* mapsTxt();
    libfalltergeist::Txt::WorldmapFile* worldmapTxt();
    libfalltergeist::Txt::EndDeathFile* endDeathTxt();
    libfalltergeist::Txt::EndGameFile* endGameTxt();
    libfalltergeist::Txt::GenRepFile* genRepTxt();
    libfalltergeist::Txt::HolodiskFile* holodiskTxt();
    libfalltergeist::Txt::KarmaVarFile* karmaVarTxt();
    libfalltergeist::Txt::QuestsFile* questsTxt();

    Graphics::Texture* texture(const std::string& filename);
    Font* font(const std::string& filename = "font1.aaf", unsigned int color = 0x3ff800ff);
    void unloadResources();
    std::string FIDtoFrmName(unsigned int FID);
    Game::Location* gameLocation(unsigned int number);
    void shutdown();

protected:
    friend class Base::Singleton<ResourceManager>;

    std::vector<std::unique_ptr<libfalltergeist::Dat::File>> _datFiles;
    std::unordered_map<std::string, std::unique_ptr<libfalltergeist::Dat::Item>> _datFilesItems;
    std::unordered_map<std::string, std::unique_ptr<Graphics::Texture>> _textures;
    std::unordered_map<std::string, std::unique_ptr<Font>> _fonts;

    ResourceManager();
    ~ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    libfalltergeist::Dat::Item* _createItemByName(const std::string& filename, std::ifstream* stream);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
