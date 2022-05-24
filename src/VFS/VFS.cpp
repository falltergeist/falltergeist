// Project includes
#include "../VFS/VFS.h"
#include "../Utils/FormattedString.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace VFS {
        using Utils::FormattedString;

        VFS::VFS(std::shared_ptr<ILogger> logger) : _logger(logger) {
        }

        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>&& driver) {
            _logger->debug() << FormattedString("Mount point '%s' was added with driver '%s'", path.c_str(), driver->name().c_str()) << std::endl;
            _mounts.insert(std::make_pair(path, std::move(driver)));
        }

        void VFS::addMount(const std::string& path, std::unique_ptr<IDriver>& driver) {
            addMount(path, std::move(driver));
        }

        bool VFS::exists(const std::string& pathToFile) {
            for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
                if (it->first.size() && pathToFile.find(it->first) == std::string::npos) {
                    _logger->debug() << FormattedString(
                        "Path '%s' does not match mount point '%s'(%s)",
                        pathToFile.c_str(),
                        it->first.c_str(),
                        it->second->name().c_str()
                    ) << std::endl;
                    continue;
                }

                if (it->second->exists(it->first.size() ? pathToFile.substr(it->first.length()) : pathToFile)) {
                    _logger->debug() << FormattedString(
                        "Path '%s' was found in mount point '%s'(%s)",
                        pathToFile.c_str(),
                        it->first.c_str(),
                        it->second->name().c_str()
                    ) << std::endl;
                    return true;
                }
            }

            _logger->debug() << FormattedString(
                "Path '%s' was not found in any mount point",
                pathToFile.c_str()
            ) << std::endl;
            return false;
        }

        std::shared_ptr<IFile> VFS::open(const std::string& path, IFile::OpenMode mode) {
            if (_openedFiles.count(path) != 0) {
                return _openedFiles.at(path);
            }

            for (auto it = _mounts.begin(); it != _mounts.end(); ++it) {
                if (it->first.size() && path.find(it->first) == std::string::npos) {
                    _logger->debug() << FormattedString(
                        "Path '%s' does not match mount point '%s'(%s)",
                        path.c_str(),
                        it->first.c_str(),
                        it->second->name().c_str()
                    ) << std::endl;
                    continue;
                }

                if (mode == IFile::OpenMode::Read || mode == IFile::OpenMode::ReadWrite) {
                    // File should exist in these modes
                    if (!it->second->exists(it->first.size() ? path.substr(it->first.length() + 1) : path)) {
                        _logger->debug() << FormattedString(
                            "File '%s' was not found in mount point '%s'(%s)",
                            path.c_str(),
                            it->first.c_str(),
                            it->second->name().c_str()
                        ) << std::endl;
                        continue;
                    }
                }

                _logger->debug() << FormattedString(
                    "Opening '%s' in mount point '%s'(%s)",
                    path.c_str(),
                    it->first.c_str(),
                    it->second->name().c_str()
                ) << std::endl;
                auto file = it->second->open(it->first.size() ? path.substr(it->first.length() + 1) : path, mode);
                if (file) {
                    _openedFiles.emplace(std::make_pair(path, file));
                    return file;
                }

                _logger->debug() << FormattedString(
                    "Could not open file '%s' in mount point '%s'(%s)",
                    path.c_str(),
                    it->first.c_str(),
                    it->second->name().c_str()
                ) << std::endl;
            }

            _logger->debug() << FormattedString(
                "File '%s' not found in any mount point",
                path.c_str()
            ) << std::endl;
            return nullptr;
        }

        void VFS::close(std::shared_ptr<IFile>& file) {
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
