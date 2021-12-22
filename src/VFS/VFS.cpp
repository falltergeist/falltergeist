#include "../VFS/VFS.h"

#include <iostream>

namespace Falltergeist {
    namespace VFS {
        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>&& driver) {
            // TODO ensure trailing path separator
            _mounts.insert(std::make_pair(path, std::move(driver)));
        }

        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>& driver) {
            // TODO ensure trailing path separator
            _mounts.insert(std::make_pair(path, std::move(driver)));
        }

        bool VFS::exists(const std::string& pathToFile) {
            for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
                if (it->first.size() && pathToFile.find(it->first) == std::string::npos) {
                    std::cout << "Path '" << pathToFile << "' does not match mount point '" << it->first << "'" << std::endl;
                    continue;
                }

                // TODO ltrim mountPoint from pathToFile
                if (it->second->exists(it->first.size() ? pathToFile.substr(it->first.length()) : pathToFile)) {
                    std::cout << "Mount point: '" << it->first << "' found file: '" << pathToFile << "'" << std::endl;
                    return true;
                }
            }
            std::cout << "file: '" << pathToFile << "' not found at any mount point" << std::endl;
            return false;
        }

        std::shared_ptr<IFile> VFS::open(const std::string& path, IFile::OpenMode mode) {
            for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
                if (it->first.size() && path.find(it->first) == std::string::npos) {
                    std::cout << "Path '" << path << "' does not match mount point '" << it->first << "'" << std::endl;
                    continue;
                }

                if (mode == IFile::OpenMode::Read || mode == IFile::OpenMode::ReadWrite) {
                    // File should exist in these modes
                    if (!it->second->exists(it->first.size() ? path.substr(it->first.length() + 1) : path)) {
                        std::cout << "Mount point: '" << it->first << "' file not found: '" << path << "'" << std::endl;
                        continue;
                    }
                }

                std::cout << "Mount point: '" << it->first << "' opening file: '" << path << "'" << std::endl;

                // TODO save file to the list of opened files
                return it->second->open(it->first.size() ? path.substr(it->first.length() + 1) : path, mode);
            }
            std::cout << "file: '" << path << "' not found at any mount point" << std::endl;
            return nullptr;
        }
    }
}
