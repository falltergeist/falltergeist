// Project includes
#include "CrossPlatform.h"
#include "Exception.h"
#include "Format/Acm/File.h"
#include "Format/Bio/File.h"
#include "Format/Dat/Stream.h"
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
#include "Graphics/Font/AAF.h"
#include "Graphics/Font/FON.h"
#include "Graphics/Texture.h"
#include "Graphics/Shader.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "Ini/File.h"
#include "falltergeist/vfs/DatArchiveDriver.h"
#include "falltergeist/vfs/NativeDriver.h"
#include "falltergeist/vfs/MemoryDriver.h"

// Third-party includes
#include <SDL_image.h>

// stdlib
#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <memory>
#include <utility>

namespace Falltergeist {
    using Size = Graphics::Size;

    namespace {
        Format::Pro::File *fetchProFileType(unsigned int PID) {
            return ResourceManager::getInstance()->proFileType(PID);
        }
    }

    ResourceManager::ResourceManager() {
        _vfs = std::make_unique<VFS::VFS>();

        for (auto filename : CrossPlatform::findFalloutDataFiles()) {
            std::string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
            _datFiles.push_back(std::make_unique<Format::Dat::File>(path));
            _vfs->addMount("", std::make_unique<VFS::DatArchiveDriver>(path));
        }

        std::string falltergeistDataPath = CrossPlatform::findFalltergeistDataPath() + "/data";
        _vfs->addMount("data", std::make_unique<VFS::NativeDriver>(falltergeistDataPath));
        _vfs->addMount("cache", std::make_unique<VFS::MemoryDriver>());
    }

// static
    ResourceManager *ResourceManager::getInstance() {
        return Base::Singleton<ResourceManager>::get();
    }

    void ResourceManager::_loadStreamForFile(std::string filename, std::function<void(Format::Dat::Stream &&)> callback) {
        // Searching file in Fallout data directory
        {
            std::string path = CrossPlatform::findFalloutDataPath() + "/" + filename;

            std::ifstream stream;
            stream.open(path, std::ios_base::binary);
            if (stream.is_open()) {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLOUT DATA DIR]" << std::endl;
            } else {
                path = CrossPlatform::findFalltergeistDataPath() + "/" + filename;
                stream.open(path, std::ios_base::binary);
                if (stream.is_open()) {
                    Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLTERGEIST DATA DIR]"
                                                      << std::endl;
                }
            }

            if (stream.is_open()) {
                callback(Format::Dat::Stream(stream));
                stream.close();
                return;
            }
        }

        // Search in DAT files
        for (auto &datfile : _datFiles) {
            auto entry = datfile->entry(filename);
            if (entry != nullptr) {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM " << datfile->filename()
                                                  << "]" << std::endl;
                callback(Format::Dat::Stream(*entry));
                return;
            }
        }
        Logger::error("RESOURCE MANAGER") << "Loading file: " << filename << " [ NOT FOUND]" << std::endl;
    }

    template<class T>
    T *ResourceManager::_datFileItem(std::string filename) {
        std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

        // Return item from cache
        auto itemIt = _datItems.find(filename);
        if (itemIt != _datItems.end()) {
            auto itemPtr = dynamic_cast<T *>(itemIt->second.get());
            if (itemPtr == nullptr) {
                Logger::error("RESOURCE MANAGER") << "Requested file type does not match type in the cache: "
                                                  << filename << std::endl;
            }
            return itemPtr;
        }

        T *itemPtr = nullptr;
        _loadStreamForFile(filename, [this, &filename, &itemPtr](Format::Dat::Stream &&stream) {
            auto item = std::make_unique<T>(std::move(stream));
            itemPtr = item.get();
            item->setFilename(filename);
            _datItems.emplace(filename, std::move(item));
        });

        return itemPtr;
    }

    Format::Frm::File *ResourceManager::frmFileType(const std::string &filename) {
        // TODO: Maybe get rid of all wrappers like this and call template function directly from outside.
        return _datFileItem<Format::Frm::File>(filename);
    }

    Format::Pal::File *ResourceManager::palFileType(const std::string &filename) {
        return _datFileItem<Format::Pal::File>(filename);
    }

    Format::Lip::File *ResourceManager::lipFileType(const std::string &filename) {
        return _datFileItem<Format::Lip::File>(filename);
    }

    Format::Lst::File *ResourceManager::lstFileType(const std::string &filename) {
        return _datFileItem<Format::Lst::File>(filename);
    }

    Format::Aaf::File *ResourceManager::aafFileType(const std::string &filename) {
        return _datFileItem<Format::Aaf::File>(filename);
    }

    Format::Acm::File *ResourceManager::acmFileType(const std::string &filename) {
        return _datFileItem<Format::Acm::File>(filename);
    }

    Format::Fon::File *ResourceManager::fonFileType(const std::string &filename) {
        return _datFileItem<Format::Fon::File>(filename);
    }

    Format::Gam::File *ResourceManager::gamFileType(const std::string &filename) {
        return _datFileItem<Format::Gam::File>(filename);
    }

    Format::Gcd::File *ResourceManager::gcdFileType(const std::string &filename) {
        return _datFileItem<Format::Gcd::File>(filename);
    }

    std::unique_ptr<Format::Int::File> ResourceManager::intFileType(const std::string &filename) {
        return nullptr;
        // TODO fix me
        //return _datFileItem<Format::Int::File>(filename);
    }

    Format::Msg::File *ResourceManager::msgFileType(const std::string &filename) {
        return _datFileItem<Format::Msg::File>(filename);
    }

    Format::Mve::File *ResourceManager::mveFileType(const std::string &filename) {
        return _datFileItem<Format::Mve::File>(filename);
    }

    Format::Bio::File *ResourceManager::bioFileType(const std::string &filename) {
        return _datFileItem<Format::Bio::File>(filename);
    }

    Format::Map::File *ResourceManager::mapFileType(const std::string &filename) {
        auto item = _datFileItem<Format::Map::File>(filename);
        if (item) {
            item->init(&fetchProFileType);
        }
        return item;
    }

    Format::Pro::File *ResourceManager::proFileType(const std::string &filename) {
        return _datFileItem<Format::Pro::File>(filename);
    }

    Format::Rix::File *ResourceManager::rixFileType(const std::string &filename) {
        return _datFileItem<Format::Rix::File>(filename);
    }

    Format::Sve::File *ResourceManager::sveFileType(const std::string &filename) {
        return _datFileItem<Format::Sve::File>(filename);
    }

    Format::Txt::CityFile *ResourceManager::cityTxt() {
        return _datFileItem<Format::Txt::CityFile>("data/city.txt");
    }

    Format::Txt::MapsFile *ResourceManager::mapsTxt() {
        return _datFileItem<Format::Txt::MapsFile>("data/maps.txt");
    }

    Format::Txt::WorldmapFile *ResourceManager::worldmapTxt() {
        return _datFileItem<Format::Txt::WorldmapFile>("data/worldmap.txt");
    }

    Format::Txt::EndDeathFile *ResourceManager::endDeathTxt() {
        return _datFileItem<Format::Txt::EndDeathFile>("data/enddeath.txt");
    }

    Format::Txt::EndGameFile *ResourceManager::endGameTxt() {
        return _datFileItem<Format::Txt::EndGameFile>("data/endgame.txt");
    }

    Format::Txt::GenRepFile *ResourceManager::genRepTxt() {
        return _datFileItem<Format::Txt::GenRepFile>("data/genrep.txt");
    }

    Format::Txt::HolodiskFile *ResourceManager::holodiskTxt() {
        return _datFileItem<Format::Txt::HolodiskFile>("data/holodisk.txt");
    }

    Format::Txt::KarmaVarFile *ResourceManager::karmaVarTxt() {
        return _datFileItem<Format::Txt::KarmaVarFile>("data/karmavar.txt");
    }

    Format::Txt::QuestsFile *ResourceManager::questsTxt() {
        return _datFileItem<Format::Txt::QuestsFile>("data/quests.txt");
    }

    Graphics::Texture *ResourceManager::texture(const std::string &filename) {
        if (_textures.count(filename)) {
            return _textures.at(filename).get();
        }

        std::string ext = filename.substr(filename.length() - 4);

        Graphics::Texture *texture = nullptr;

        if (ext == ".png") {
            auto file = vfs()->open(filename, VFS::IFile::OpenMode::Read);
            if (!file || !file->isOpened()) {
                return nullptr;
            }

            char* src = new char[file->size()];
            file->read(src, file->size());
            SDL_Surface* tempSurface = IMG_Load_RW(SDL_RWFromMem(src, file->size()), 1);
            vfs()->close(file);

            // @fixme: this section looks quite ugly. we should try to do something with it someday
            if (tempSurface == NULL) {
                throw Exception("ResourceManager::texture(name) - cannot load texture from file " + filename + ": " +
                                IMG_GetError());
            }

            SDL_PixelFormat* pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
            SDL_Surface* tempSurface2 = SDL_ConvertSurface(tempSurface, pixelFormat, 0);
            texture = new Graphics::Texture(
                Graphics::Pixels(
                    tempSurface2->pixels,
                    Size(tempSurface2->w, tempSurface2->h),
                    Graphics::Pixels::Format::RGBA
                )
            );

            SDL_FreeFormat(pixelFormat);
            SDL_FreeSurface(tempSurface);
            SDL_FreeSurface(tempSurface2);
        } else if (ext == ".rix") {
            auto rix = rixFileType(filename);
            if (!rix) {
                return nullptr;
            }
            texture = new Graphics::Texture(
                Graphics::Pixels(
                    rix->rgba(),
                    Size(rix->width(), rix->height()),
                    Graphics::Pixels::Format::RGBA
                )
            );
        } else if (ext == ".frm") {
            auto frm = frmFileType(filename);
            if (!frm) {
                return nullptr;
            }
            texture = new Graphics::Texture(
                Graphics::Pixels(
                    frm->rgba(palFileType("color.pal")),
                    Size(frm->width(), frm->height()),
                    Graphics::Pixels::Format::RGBA
                )
            );
            texture->setMask(frm->mask(palFileType("color.pal")));
        } else {
            throw Exception("ResourceManager::surface() - unknown image type:" + filename);
        }

        _textures.insert(make_pair(filename, std::unique_ptr<Graphics::Texture>(texture)));
        return texture;
    }

    Graphics::Font *ResourceManager::font(const std::string &filename) {

        if (_fonts.count(filename)) {
            return _fonts.at(filename).get();
        }

        std::string ext = filename.substr(filename.length() - 4);
        Graphics::Font *fontPtr = nullptr;

        if (ext == ".aaf") {
            fontPtr = new Graphics::AAF(filename);
        } else if (ext == ".fon") {
            fontPtr = new Graphics::FON(filename);
        }
        _fonts.emplace(filename, std::unique_ptr<Graphics::Font>(fontPtr));
        return fontPtr;
    }

    std::shared_ptr<Graphics::Shader>& ResourceManager::shader(const std::string &filename) {
        if (!_shaders.count(filename)) {
            auto shader = std::make_shared<Graphics::Shader>(filename);
            _shaders.emplace(filename, shader);
        }
        return _shaders.at(filename);
    }

    Format::Pro::File *ResourceManager::proFileType(unsigned int PID) {
        unsigned int typeId = PID >> 24;
        std::string listFile;
        switch ((OBJECT_TYPE) typeId) {
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
                Logger::error("") << "ResourceManager::proFileType(unsigned int) - wrong PID: " << PID << std::endl;
                return nullptr;
        }

        auto lst = lstFileType(listFile);

        unsigned int index = 0x00000FFF & PID;

        if (index > lst->strings()->size()) {
            Logger::error("") << "ResourceManager::proFileType(unsigned int) - LST size < PID: " << PID << std::endl;
            return nullptr;
        }

        std::string protoName = lst->strings()->at(index - 1);

        switch ((OBJECT_TYPE) typeId) {
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

    void ResourceManager::unloadResources() {
        _datItems.clear();
    }

    Format::Frm::File *ResourceManager::frmFileType(unsigned int FID) {
        const auto &frmName = FIDtoFrmName(FID);

        if (frmName.empty()) {
            return nullptr;
        }
        return frmFileType(frmName);
    }

    std::unique_ptr<Format::Int::File> ResourceManager::intFileType(unsigned int SID) {
        auto lst = lstFileType("scripts/scripts.lst");
        if (SID >= lst->strings()->size()) {
            throw Exception("ResourceManager::intFileType() - wrong SID: " + std::to_string(SID));
        }

        return intFileType("scripts/" + lst->strings()->at(SID));
    }

    std::string ResourceManager::FIDtoFrmName(unsigned int FID) {
        const auto baseId = FID & 0x00000FFF;
        const auto type = static_cast<FRM_TYPE>(FID >> 24);

        if (type == FRM_TYPE::CRITTER) {
            throw Exception("use CritterAnimationHelpers instead");
        }

        if (type == FRM_TYPE::MISC && baseId == 1) {
            static const std::string SCROLL_BLOCKERS_PATH("art/misc/scrblk.frm");
            // Map scroll blockers
            return SCROLL_BLOCKERS_PATH;
        }

        static struct TypeArtListDecription {
            const std::string prefixPath;
            const std::string lstFilePath;
        } const frmTypeDescription[] =
            {
                {"art/items/",    "art/items/items.lst"},
                {"art/critters/", "art/critters/critters.lst"},
                {"art/scenery/",  "art/scenery/scenery.lst"},
                {"art/walls/",    "art/walls/walls.lst"},
                {"art/tiles/",    "art/tiles/tiles.lst"},
                {"art/misc/",     "art/misc/misc.lst"},
                {"art/intrface/", "art/intrface/intrface.lst"},
                {"art/inven/",    "art/inven/inven.lst"},
            };

        if (type > FRM_TYPE::INVENTORY) {
            throw Exception("ResourceManager::FIDtoFrmName - wrong type");
        }

        const auto &typeArtDescription = frmTypeDescription[static_cast<size_t>(type)];
        auto lst = lstFileType(typeArtDescription.lstFilePath);
        if (baseId >= lst->strings()->size()) {
            Logger::error("") << "ResourceManager::FIDtoFrmName(unsigned int) - LST size " << lst->strings()->size()
                              << " <= frmID: " << baseId << " frmType: " << (unsigned) type << std::endl;
            return std::string();
        }

        std::string frmName = lst->strings()->at(baseId);
        return typeArtDescription.prefixPath + frmName;
    }

    void ResourceManager::shutdown() {
        unloadResources();
    }

    std::unique_ptr<VFS::VFS>& ResourceManager::vfs() {
        return _vfs;
    }
}
