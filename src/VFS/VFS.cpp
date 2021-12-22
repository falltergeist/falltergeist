#include "../VFS/VFS.h"

#include <iostream>

namespace Falltergeist {
    namespace VFS {
        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>&& driver) {
            _mounts.insert(std::make_pair(path, std::move(driver)));
        }

        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>& driver) {
            _mounts.insert(std::make_pair(path, std::move(driver)));
        }

        bool VFS::exists(const std::string& pathToFile) {
            for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
                if (it->first.size() && pathToFile.find(it->first) == std::string::npos) {
                    std::cout << "Path '" << pathToFile << "' does not match mount point '" << it->first << "'" << std::endl;
                    continue;
                }

                if (it->second->exists(it->first.size() ? pathToFile.substr(it->first.length()) : pathToFile)) {
                    std::cout << "Mount point: '" << it->first << "' found file: '" << pathToFile << "'" << std::endl;
                    return true;
                }
            }
            std::cout << "file: '" << pathToFile << "' not found at any mount point" << std::endl;
            return false;
        }

        std::shared_ptr<IFile> VFS::open(const std::string& path, IFile::OpenMode mode) {
            if (_openedFiles.count(path) != 0) {
                return _openedFiles.at(path);
            }

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
                auto file = it->second->open(it->first.size() ? path.substr(it->first.length() + 1) : path, mode);
                if (file) {
                    _openedFiles.emplace(std::make_pair(path, file));
                    return file;
                }

                std::cout << "Could not open file" << std::endl;
            }
            std::cout << "file: '" << path << "' not found at any mount point" << std::endl;
            return nullptr;
        }

        void VFS::close(std::shared_ptr<IFile>& file)
        {
            file->_close();

            for (auto it = _openedFiles.begin(); it != _openedFiles.end(); ++it) {
                if (it->second == file) {
                    _openedFiles.erase(it->first);
                    break;
                }
            }
        }
    }
}
