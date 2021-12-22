#pragma once

#include "../VFS/IDriver.h"
#include "../VFS/IFile.h"
#include "../ILogger.h"
#include <map>
#include <memory>
#include <string>

namespace Falltergeist {
    namespace VFS {
        class VFS final {
        public:
            VFS(std::shared_ptr<ILogger> logger);

            VFS(const VFS& other) = delete;

            VFS(VFS&& other) = delete;

            VFS& operator=(VFS other) = delete;

            void addMount(const std::string& mountPath, std::unique_ptr<IDriver>&& driver);

            void addMount(const std::string& mountPath, std::unique_ptr<IDriver>& driver);

            bool exists(const std::string& pathToFile);

            std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode = IFile::OpenMode::Read);

            void close(std::shared_ptr<IFile>& file);

        private:
            std::multimap<std::string, std::unique_ptr<IDriver>> _mounts;

            std::map<std::string, std::shared_ptr<IFile>> _openedFiles;

            std::shared_ptr<ILogger> _logger;
        };
    }
}
