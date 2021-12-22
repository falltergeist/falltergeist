#pragma once

#include <map>
#include <memory>
#include "../VFS/IDriver.h"
#include "../VFS/MemoryFile.h"

namespace Falltergeist {
    namespace VFS {
        class MemoryDriver final : public IDriver {
        public:
            ~MemoryDriver() override = default;

            bool exists(const std::string &path) override;

            std::shared_ptr<IFile> open(const std::string &path, IFile::OpenMode mode) override;
        private:
            std::map<std::string, std::shared_ptr<MemoryFile>> _files;
        };
    }
}
