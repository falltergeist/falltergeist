#pragma once

#include "../VFS/IDriver.h"
#include "../VFS/DatArchiveEntry.h"
#include "../VFS/DatArchiveStreamWrapper.h"
#include <map>
#include <memory>

namespace Falltergeist {
    namespace VFS {
        class DatArchiveDriver final : public IDriver {
        public:
            DatArchiveDriver(const std::string& path);

            ~DatArchiveDriver() override = default;

            bool exists(const std::string& path) override;

            std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) override;

        private:
            DatArchiveStreamWrapper _streamWrapper;
        };
    }
}
