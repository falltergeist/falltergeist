#pragma once

#include "../VFS/IDriver.h"
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
            struct DatArchiveEntry {
                unsigned int packedSize = 0;
                unsigned int unpackedSize = 0;
                unsigned int dataOffset = 0;
                bool isCompressed = false;
            };

            std::map<std::string, DatArchiveEntry> _entries;
        };
    }
}
