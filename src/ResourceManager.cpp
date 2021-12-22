#include <fstream>
#include <sstream>
#include <iomanip>
#include <locale>
#include <memory>
#include <utility>
#include <SDL_image.h>
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
#include "VFS/DatArchiveDriver.h"
#include "VFS/NativeDriver.h"
#include "VFS/MemoryDriver.h"

namespace Falltergeist {
    using namespace std;
    using namespace Format;

    namespace {
        Pro::File *fetchProFileType(unsigned int PID) {
            return ResourceManager::getInstance()->proFileType(PID);
        }
    }

    ResourceManager::ResourceManager() {
        _vfs = std::make_unique<VFS::VFS>();

        for (auto filename : CrossPlatform::findFalloutDataFiles()) {
            string path = CrossPlatform::findFalloutDataPath() + "/" + filename;
            _datFiles.push_back(std::make_unique<Dat::File>(path));
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

    void ResourceManager::_loadStreamForFile(string filename, std::function<void(Dat::Stream &&)> callback) {
        // Searching file in Fallout data directory
        {
            string path = CrossPlatform::findFalloutDataPath() + "/" + filename;

            ifstream stream;
            stream.open(path, ios_base::binary);
            if (stream.is_open()) {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLOUT DATA DIR]" << endl;
            } else {
                path = CrossPlatform::findFalltergeistDataPath() + "/" + filename;
                stream.open(path, ios_base::binary);
                if (stream.is_open()) {
                    Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM FALLTERGEIST DATA DIR]"
                                                      << endl;
                }
            }

            if (stream.is_open()) {
                callback(Dat::Stream(stream));
                stream.close();
                return;
            }
        }

        // Search in DAT files
        for (auto &datfile : _datFiles) {
            auto entry = datfile->entry(filename);
            if (entry != nullptr) {
                Logger::debug("RESOURCE MANAGER") << "Loading file: " << filename << " [FROM " << datfile->filename()
                                                  << "]" << endl;
                callback(Dat::Stream(*entry));
                return;
            }
        }
        Logger::error("RESOURCE MANAGER") << "Loading file: " << filename << " [ NOT FOUND]" << endl;
    }

    template<class T>
    T *ResourceManager::_datFileItem(string filename) {
        std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

        // Return item from cache
        auto itemIt = _datItems.find(filename);
        if (itemIt != _datItems.end()) {
            auto itemPtr = dynamic_cast<T *>(itemIt->second.get());
            if (itemPtr == nullptr) {
                Logger::error("RESOURCE MANAGER") << "Requested file type does not match type in the cache: "
                                                  << filename << endl;
            }
            return itemPtr;
        }

        T *itemPtr = nullptr;
        _loadStreamForFile(filename, [this, &filename, &itemPtr](Dat::Stream &&stream) {
            auto item = std::make_unique<T>(std::move(stream));
            itemPtr = item.get();
            item->setFilename(filename);
            _datItems.emplace(filename, std::move(item));
        });

        return itemPtr;
    }

    Frm::File *ResourceManager::frmFileType(const string &filename) {
        // TODO: Maybe get rid of all wrappers like this and call template function directly from outside.
        return _datFileItem<Frm::File>(filename);
    }

    Pal::File *ResourceManager::palFileType(const string &filename) {
        return _datFileItem<Pal::File>(filename);
    }

    Lip::File *ResourceManager::lipFileType(const string &filename) {
        return _datFileItem<Lip::File>(filename);
    }

    Lst::File *ResourceManager::lstFileType(const string &filename) {
        return _datFileItem<Lst::File>(filename);
    }

    Aaf::File *ResourceManager::aafFileType(const string &filename) {
        return _datFileItem<Aaf::File>(filename);
    }

    Acm::File *ResourceManager::acmFileType(const string &filename) {
        return _datFileItem<Acm::File>(filename);
    }

    Fon::File *ResourceManager::fonFileType(const string &filename) {
        return _datFileItem<Fon::File>(filename);
    }

    Gam::File *ResourceManager::gamFileType(const string &filename) {
        return _datFileItem<Gam::File>(filename);
    }

    Gcd::File *ResourceManager::gcdFileType(const string &filename) {
        return _datFileItem<Gcd::File>(filename);
    }

    Int::File *ResourceManager::intFileType(const string &filename) {
        return _datFileItem<Int::File>(filename);
    }

    Msg::File *ResourceManager::msgFileType(const string &filename) {
        return _datFileItem<Msg::File>(filename);
    }

    Mve::File *ResourceManager::mveFileType(const string &filename) {
        return _datFileItem<Mve::File>(filename);
    }

    Bio::File *ResourceManager::bioFileType(const string &filename) {
        return _datFileItem<Bio::File>(filename);
    }

    Map::File *ResourceManager::mapFileType(const string &filename) {
        auto item = _datFileItem<Map::File>(filename);
        if (item) {
            item->init(&fetchProFileType);
        }
        return item;
    }

    Pro::File *ResourceManager::proFileType(const string &filename) {
        return _datFileItem<Pro::File>(filename);
    }

    Rix::File *ResourceManager::rixFileType(const string &filename) {
        return _datFileItem<Rix::File>(filename);
    }

    Sve::File *ResourceManager::sveFileType(const string &filename) {
        return _datFileItem<Sve::File>(filename);
    }

    Txt::CityFile *ResourceManager::cityTxt() {
        return _datFileItem<Txt::CityFile>("data/city.txt");
    }

    Txt::MapsFile *ResourceManager::mapsTxt() {
        return _datFileItem<Txt::MapsFile>("data/maps.txt");
    }

    Txt::WorldmapFile *ResourceManager::worldmapTxt() {
        return _datFileItem<Txt::WorldmapFile>("data/worldmap.txt");
    }

    Txt::EndDeathFile *ResourceManager::endDeathTxt() {
        return _datFileItem<Txt::EndDeathFile>("data/enddeath.txt");
    }

    Txt::EndGameFile *ResourceManager::endGameTxt() {
        return _datFileItem<Txt::EndGameFile>("data/endgame.txt");
    }

    Txt::GenRepFile *ResourceManager::genRepTxt() {
        return _datFileItem<Txt::GenRepFile>("data/genrep.txt");
    }

    Txt::HolodiskFile *ResourceManager::holodiskTxt() {
        return _datFileItem<Txt::HolodiskFile>("data/holodisk.txt");
    }

    Txt::KarmaVarFile *ResourceManager::karmaVarTxt() {
        return _datFileItem<Txt::KarmaVarFile>("data/karmavar.txt");
    }

    Txt::QuestsFile *ResourceManager::questsTxt() {
        return _datFileItem<Txt::QuestsFile>("data/quests.txt");
    }

    Graphics::Texture *ResourceManager::texture(const string &filename) {
        if (_textures.count(filename)) {
            return _textures.at(filename).get();
        }

        string ext = filename.substr(filename.length() - 4);

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

        _textures.insert(make_pair(filename, unique_ptr<Graphics::Texture>(texture)));
        return texture;
    }

    Graphics::Font *ResourceManager::font(const string &filename) {

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


    Graphics::Shader *ResourceManager::shader(const string &filename) {
        if (_shaders.count(filename)) {
            return _shaders.at(filename).get();
        }

        Graphics::Shader *shader = new Graphics::Shader(filename);

        _shaders.emplace(filename, unique_ptr<Graphics::Shader>(shader));
        return shader;
    }


    Pro::File *ResourceManager::proFileType(unsigned int PID) {
        unsigned int typeId = PID >> 24;
        string listFile;
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
                Logger::error("") << "ResourceManager::proFileType(unsigned int) - wrong PID: " << PID << endl;
                return nullptr;
        }

        auto lst = lstFileType(listFile);

        unsigned int index = 0x00000FFF & PID;

        if (index > lst->strings()->size()) {
            Logger::error("") << "ResourceManager::proFileType(unsigned int) - LST size < PID: " << PID << endl;
            return nullptr;
        }

        string protoName = lst->strings()->at(index - 1);

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

    Frm::File *ResourceManager::frmFileType(unsigned int FID) {
        const auto &frmName = FIDtoFrmName(FID);

        if (frmName.empty()) {
            return nullptr;
        }
        return frmFileType(frmName);
    }

    Int::File *ResourceManager::intFileType(unsigned int SID) {
        auto lst = lstFileType("scripts/scripts.lst");
        if (SID >= lst->strings()->size()) {
            throw Exception("ResourceManager::intFileType() - wrong SID: " + std::to_string(SID));
        }

        return intFileType("scripts/" + lst->strings()->at(SID));
    }

    string ResourceManager::FIDtoFrmName(unsigned int FID) {
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
                              << " <= frmID: " << baseId << " frmType: " << (unsigned) type << endl;
            return std::string();
        }

        string frmName = lst->strings()->at(baseId);
        return typeArtDescription.prefixPath + frmName;
    }

    void ResourceManager::shutdown() {
        unloadResources();
    }

    std::unique_ptr<VFS::VFS>& ResourceManager::vfs() {
        return _vfs;
    }
}
