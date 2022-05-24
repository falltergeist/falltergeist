// Project includes
#include "../VFS/MemoryDriver.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace VFS {
        MemoryDriver::MemoryDriver() : _name("MemoryDriver") {
        }

        const std::string& MemoryDriver::name() {
            return _name;
        }

        bool MemoryDriver::exists(const std::string& path) {
            return _files.count(path) != 0;
        }

        std::shared_ptr<IFile> MemoryDriver::open(const std::string& path, IFile::OpenMode mode) {
            if (exists(path)) {
                auto file = _files.at(path);
                file->_open(mode);
                return file;
            }

            std::shared_ptr<MemoryFile> file = std::make_shared<MemoryFile>();
            file->_open(mode);
            _files.insert(std::make_pair(path, file));
            return file;
        }
    }
}
