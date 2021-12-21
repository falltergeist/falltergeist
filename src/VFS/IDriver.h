#pragma once

#include <string>
#include "../VFS/IFile.h"

namespace Falltergeist {
    namespace VFS {
        class IDriver {
        public:
            virtual ~IDriver() = default;

            virtual bool exists(const std::string& path) = 0;

            virtual std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) = 0;
        };
    }
}