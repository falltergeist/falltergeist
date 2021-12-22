#include "../VFS/NativeDriver.h"

#include <filesystem>
#include <iostream>
#include "../VFS/NativeFile.h"

namespace Falltergeist {
    namespace VFS {
        NativeDriver::NativeDriver(const std::filesystem::path& basePath)
            : _basePath(basePath) {
        }

        bool NativeDriver::exists(const std::string& path) {
            std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
            std::cout << "Looking for native file: '" << fsPath.native() << "'" << std::endl;
            return std::filesystem::exists(fsPath);
        }

        std::shared_ptr<IFile> NativeDriver::open(const std::string& path, IFile::OpenMode mode) {
            std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
            auto file = std::make_shared<NativeFile>(fsPath);
            file->_open(mode);
            return file;
        }
    }
}
