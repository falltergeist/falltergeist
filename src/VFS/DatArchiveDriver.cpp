#include "../VFS/DatArchiveDriver.h"

namespace Falltergeist {
    namespace VFS {
        DatArchiveDriver::DatArchiveDriver(const std::string& path) {
        }

        bool DatArchiveDriver::exists(const std::string& path) {
            return false;
        }

        std::shared_ptr<IFile> DatArchiveDriver::open(const std::string& path, IFile::OpenMode mode) {
            return nullptr;
        }
    }
}
