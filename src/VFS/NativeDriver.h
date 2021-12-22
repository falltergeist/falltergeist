#pragma once

#include "../VFS/IDriver.h"
#include "../VFS/IFile.h"
#include "../ILogger.h"
#include <filesystem>

namespace Falltergeist {
    namespace VFS {
        /**
         * NativeDriver provides support for accessing real file system path
         * It will search files relative to given basePath
         */
        class NativeDriver final : public IDriver {
        public:
            NativeDriver(const std::filesystem::path& basePath, std::shared_ptr<ILogger> logger);

            ~NativeDriver() override = default;

            const std::string& name() override;

            bool exists(const std::string& path) override;

            std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) override;

        private:
            std::string _name;

            std::filesystem::path _basePath;

            std::shared_ptr<ILogger> _logger;
        };
    }
}
