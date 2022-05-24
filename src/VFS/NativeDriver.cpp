// Project includes
#include "../VFS/NativeDriver.h"
#include "../VFS/NativeFile.h"
#include "../Utils/FormattedString.h"

// Third-party includes

// stdlib
#include <filesystem>

namespace Falltergeist {
    namespace VFS {
        using Utils::FormattedString;

        NativeDriver::NativeDriver(const std::filesystem::path& basePath, std::shared_ptr<ILogger>(logger))
            : _name("NativeDriver"), _basePath(basePath), _logger(logger) {
        }

        const std::string& NativeDriver::name() {
            return _name;
        }

        bool NativeDriver::exists(const std::string& path) {
            std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
            _logger->debug() << FormattedString("[%s] Looking for native file '%s'", name().c_str(), path.c_str()) << std::endl;
            return std::filesystem::exists(fsPath);
        }

        std::shared_ptr<IFile> NativeDriver::open(const std::string& path, IFile::OpenMode mode) {
            _logger->debug() << FormattedString("[%s] Opening native file '%s'", name().c_str(), path.c_str()) << std::endl;
            std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
            auto file = std::make_shared<NativeFile>(fsPath);
            file->_open(mode);
            return file;
        }
    }
}
