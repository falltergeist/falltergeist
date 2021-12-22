#include "../VFS/DatArchiveDriver.h"
#include "../VFS/DatArchiveFile.h"
#include "../Exception.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace Falltergeist {
    namespace VFS {
        struct DatArchiveReader {

        };

        DatArchiveDriver::DatArchiveDriver(const std::string& path) : _streamWrapper(DatArchiveStreamWrapper(path)) {
        }

        bool DatArchiveDriver::exists(const std::string& path) {
            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');
            return _streamWrapper.entries().count(path) != 0;
        }

        std::shared_ptr<IFile> DatArchiveDriver::open(const std::string& path, IFile::OpenMode mode) {
            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');

            const DatArchiveEntry& entry = _streamWrapper.entries().at(path);
            if (entry.isCompressed) {
                throw 1;
                // uncompress and create MemoryFile instance
            }

            auto file = std::make_shared<DatArchiveFile>(entry, [=](unsigned int seekPosition, unsigned char* to, unsigned char size)-> unsigned int {
                _streamWrapper.seek(seekPosition);
                return _streamWrapper.readBytes(reinterpret_cast<char*>(to), size);
            });
            file->_open(mode);
            return file;
        }
    }
}
