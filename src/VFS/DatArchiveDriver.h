#pragma once

// Project includes
#include "../VFS/IDriver.h"
#include "../VFS/DatArchiveEntry.h"
#include "../VFS/DatArchiveStreamWrapper.h"

// Third-party includes

// stdlib
#include <map>
#include <memory>

namespace Falltergeist {
    namespace VFS {
        /**
         * DatArchiveDriver provides support for vanilla DAT archives
         * It supports only read operations
         */
        class DatArchiveDriver final : public IDriver {
        public:
            DatArchiveDriver(const std::string& path);

            ~DatArchiveDriver() override = default;

            const std::string& name() override;

            bool exists(const std::string& path) override;

            std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) override;

        private:
            std::string _name;

            DatArchiveStreamWrapper _streamWrapper;
        };
    }
}
