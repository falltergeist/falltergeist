// Project includes
#include "../VFS/DatArchiveDriver.h"
#include "../VFS/DatArchiveFile.h"
#include "../VFS/MemoryFile.h"

// Third-party includes
#include "zlib.h"

// stdlib

namespace Falltergeist {
    namespace VFS {
        DatArchiveDriver::DatArchiveDriver(const std::string& path) : _name("DatArchiveDriver"), _streamWrapper(DatArchiveStreamWrapper(path)) {
        }

        const std::string& DatArchiveDriver::name() {
            return _name;
        }

        bool DatArchiveDriver::exists(const std::string& path) {
            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');
            return _streamWrapper.entries().count(path) != 0;
        }

        std::shared_ptr<IFile> DatArchiveDriver::open(const std::string& path, IFile::OpenMode mode) {
            if (mode != IFile::OpenMode::Read) {
                // Only read operations are supported
                return nullptr;
            }

            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');

            const DatArchiveEntry& entry = _streamWrapper.entries().at(path);
            if (entry.isCompressed) {
                unsigned char* packedData = new unsigned char[entry.packedSize];
                _streamWrapper.seek(entry.dataOffset);
                _streamWrapper.readBytes(reinterpret_cast<char*>(packedData), entry.packedSize);

                unsigned char* unpackedData = new unsigned char[entry.unpackedSize];

                // unpacking
                z_stream zStream;
                zStream.total_in = entry.packedSize;
                zStream.avail_in = entry.packedSize;
                zStream.next_in = packedData;
                zStream.total_out = zStream.avail_out = static_cast<uint32_t>(entry.unpackedSize);
                zStream.next_out = unpackedData;
                zStream.zalloc = Z_NULL;
                zStream.zfree = Z_NULL;
                zStream.opaque = Z_NULL;
                inflateInit(&zStream);
                inflate(&zStream, Z_FINISH);
                inflateEnd(&zStream);

                delete[] packedData;

                auto file = std::make_shared<MemoryFile>();
                file->_open(IFile::OpenMode::ReadWriteTruncate);
                file->write(reinterpret_cast<const char*>(unpackedData), entry.unpackedSize);

                delete[] unpackedData;

                file->_open(mode);
                return file;
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
