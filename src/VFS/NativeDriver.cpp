#include "../VFS/NativeDriver.h"

#include <filesystem>
#include <iostream>

namespace Falltergeist {
    namespace VFS {
        NativeDriver::NativeDriver(const std::string& basePath)
            : _basePath(basePath) {
            // TODO rtrim trailing path separator
        }

        bool NativeDriver::exists(const std::string& path) {
            std::cout << "Looking for path '" << path << "' with basePath '" << _basePath + "'" << std::endl;
            std::cout << _basePath + "/" + path << std::endl;
            return std::filesystem::exists(_basePath + "/" + path);
        }
    }
}