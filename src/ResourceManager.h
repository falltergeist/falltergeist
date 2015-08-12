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
#include <list>
#include <string>
#include <map>
#include <memory>

// Falltergeist includes

// Third party includes
#include <libfalltergeist.h>

using namespace libfalltergeist;

namespace Falltergeist
{
namespace Game
{
    class GameLocation;
}

class Surface;
class Texture;
class Font;

class ResourceManager
{
protected:
    static std::vector<libfalltergeist::Dat::File*> _datFiles;
    static std::map<std::string, libfalltergeist::Dat::Item*> _datFilesItems;
    static std::map<std::string, Texture*> _textures;
    static std::map<std::string, std::shared_ptr<Font>> _fonts;
    static std::map<unsigned int, Game::GameLocation*> _gameLocations;

public:
    ResourceManager();
    ~ResourceManager();
    static libfalltergeist::Aaf::File* aafFileType(const std::string& filename);
    static libfalltergeist::Acm::File* acmFileType(const std::string& filename);
    static libfalltergeist::Bio::File* bioFileType(const std::string& filename);
    static libfalltergeist::Dat::Item* datFileItem(std::string filename);
    static libfalltergeist::Frm::File* frmFileType(const std::string& filename);
    static libfalltergeist::Frm::File* frmFileType(unsigned int FID);
    static libfalltergeist::Fon::File* fonFileType(const std::string& filename);
    static libfalltergeist::Gam::File* gamFileType(const std::string& filename);
    static libfalltergeist::Gcd::File* gcdFileType(const std::string& filename);
    static libfalltergeist::Pal::File* palFileType(const std::string& filename);
    static libfalltergeist::Int::File* intFileType(const std::string& filename);
    static libfalltergeist::Int::File* intFileType(unsigned int SID);
    static libfalltergeist::Lst::File* lstFileType(const std::string& filename);
    static libfalltergeist::Map::File* mapFileType(const std::string& filename);
    static libfalltergeist::Msg::File* msgFileType(const std::string& filename);
    static libfalltergeist::Mve::File* mveFileType(const std::string& filename);
    static libfalltergeist::Pro::File* proFileType(const std::string& filename);
    static libfalltergeist::Pro::File* proFileType(unsigned int PID);
    static libfalltergeist::Rix::File* rixFileType(const std::string& filename);
    static libfalltergeist::Sve::File* sveFileType(const std::string& filename);
    static Texture* texture(const std::string& filename);
    static std::map<std::string, Texture*>* textures();
    static std::shared_ptr<Font> font(const std::string& filename = "font1.aaf", unsigned int color = 0x3ff800ff);
    static void unloadResources();
    static std::string FIDtoFrmName(unsigned int FID);
    static Game::GameLocation* gameLocation(unsigned int number);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
