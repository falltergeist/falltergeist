#include "../VFS/DatArchiveDriver.h"
#include "../Exception.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace Falltergeist {
    namespace VFS {
        struct DatArchiveReader {
            std::fstream stream;

            DatArchiveReader(const std::string& path) {
                stream.open(path, std::ios_base::binary | std::ios_base::in);
                if (!stream.is_open()) {
                    throw Exception("DatArchiveDriver - can't open stream: " + path);
                }
            }

            unsigned int size() {
                unsigned int currentPosition = stream.tellg();
                stream.seekg(0, std::ios_base::end);
                unsigned int size = stream.tellg();
                std::cout << "Size: " << size << std::endl;
                stream.seekg(currentPosition, std::ios_base::beg);
                return size;
            }

            void seek(unsigned int position) {
                stream.seekg(position, std::ios::beg);
            }

            void readUint8(uint8_t& dest) {
                stream.read(reinterpret_cast<char*>(&dest), 1);
            }

            void readUint32(uint32_t& dest) {
                stream.read(reinterpret_cast<char*>(&dest), 4);
            }

            void readString(std::string& string) {
                stream.read(string.data(), string.size());
            }
        };

        DatArchiveDriver::DatArchiveDriver(const std::string& path) {
            DatArchiveReader archiveReader(path);

            uint32_t fileSize = 0;
            uint32_t filesTreeSize = 0;
            uint32_t filesTotalNumber = 0;

            // reading data size from dat file
            archiveReader.seek(archiveReader.size() - 4);
            archiveReader.readUint32(fileSize);
            if (fileSize != archiveReader.size()) {
                throw Exception("DatArchiveDriver - wrong file size: " + std::to_string(fileSize) + " should be: " + std::to_string(archiveReader.size()));
            }

            // reading size of files tree
            archiveReader.seek(archiveReader.size() - 8);
            archiveReader.readUint32(filesTreeSize);
            std::cout << "Tree size: " << filesTreeSize << std::endl;

            // reading total number of items in dat file
            archiveReader.seek(archiveReader.size() - filesTreeSize - 8);
            archiveReader.readUint32(filesTotalNumber);
            std::cout << "Tree size: " << filesTotalNumber << std::endl;

            // reading files data one by one
            for (unsigned int i = 0; i != filesTotalNumber; ++i) {
                std::cout << "Reading entry " << i << " out of " << filesTotalNumber << std::endl;
                uint32_t filenameSize = 0;
                uint8_t compressed = 0;
                uint32_t unpackedSize = 0;
                uint32_t packedSize = 0;
                uint32_t dataOffset = 0;

                archiveReader.readUint32(filenameSize);
                std::string filename;
                filename.resize(filenameSize);
                archiveReader.readString(filename);
                std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
                std::replace(filename.begin(), filename.end(), '\\','/');

                archiveReader.readUint8(compressed);
                archiveReader.readUint32(unpackedSize);
                archiveReader.readUint32(packedSize);
                archiveReader.readUint32(dataOffset);

                _entries.insert(std::make_pair(filename, DatArchiveEntry({
                     .packedSize = packedSize,
                     .unpackedSize = unpackedSize,
                     .dataOffset = dataOffset,
                     .isCompressed = (bool) compressed
                 })));
            }
        }

        bool DatArchiveDriver::exists(const std::string& path) {
            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');
            return _entries.count(path) != 0;
        }

        std::shared_ptr<IFile> DatArchiveDriver::open(const std::string& path, IFile::OpenMode mode) {
            std::string unixStylePath = path;
            std::replace(unixStylePath.begin(), unixStylePath.end(), '\\','/');
            return nullptr;
        }
    }
}
