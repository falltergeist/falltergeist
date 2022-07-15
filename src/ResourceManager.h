#pragma once

// Project includes
#include "Base/Singleton.h"
#include "Format/Int/File.h"

// Third-party includes
#include "falltergeist/vfs/VFS.h"

// stdlib
#include <fstream>
#include <functional>
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

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
            class Stream;
        }
        namespace Frm { class File; }
        namespace Fon { class File; }
        namespace Gam { class File; }
        namespace Gcd { class File; }
        namespace Pal { class File; }
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

    class ResourceManager final
    {
        public:
            static ResourceManager* getInstance();

            Format::Aaf::File* aafFileType(const std::string& filename);
            Format::Acm::File* acmFileType(const std::string& filename);
            Format::Bio::File* bioFileType(const std::string& filename);
            Format::Dat::Item* datFileItem(const std::string& filename);
            Format::Frm::File* frmFileType(const std::string& filename);
            Format::Frm::File* frmFileType(unsigned int FID);
            Format::Fon::File* fonFileType(const std::string& filename);
            Format::Gam::File* gamFileType(const std::string& filename);
            Format::Gcd::File* gcdFileType(const std::string& filename);
            Format::Pal::File* palFileType(const std::string& filename);

            template<class T>
            std::unique_ptr<T> get(std::string filename);

            std::unique_ptr<Format::Int::File> intFileType(unsigned int SID);
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

            std::shared_ptr<Graphics::Shader>& shader(const std::string& filename);

            void unloadResources();
            std::string FIDtoFrmName(unsigned int FID);
            Game::Location* gameLocation(unsigned int number);

            void shutdown();

            std::unique_ptr<VFS::VFS>& vfs();

        private:
            friend class Base::Singleton<ResourceManager>;

            std::vector<std::unique_ptr<Format::Dat::File>> _datFiles;

            std::unordered_map<std::string, std::unique_ptr<Format::Dat::Item>> _datItems;

            std::unordered_map<std::string, std::unique_ptr<Graphics::Texture>> _textures;

            std::unordered_map<std::string, std::unique_ptr<Graphics::Font>> _fonts;

            std::unordered_map<std::string, std::shared_ptr<Graphics::Shader>> _shaders;

            std::unique_ptr<VFS::VFS> _vfs;

            ResourceManager();

            ResourceManager(const ResourceManager&) = delete;

            ResourceManager& operator=(const ResourceManager&) = delete;

            // Retrieves given file item from "virtual file system".
            // All items are cached after being requested for the first time.
            template <class T>
            T* _datFileItem(std::string filename);

            template<class T, typename... Args>
            std::unique_ptr<T> _datFileItemUniquePtr(std::string filename, Args...);

            // Searches for a given file within virtual "file system" and calls the given callback with Dat::Stream created from that file.
            std::unique_ptr<Format::Dat::Stream> _loadStreamForFile(std::string filename);
    };

    template<>
    std::unique_ptr<Format::Map::File> ResourceManager::get<Format::Map::File>(std::string filename);
}
