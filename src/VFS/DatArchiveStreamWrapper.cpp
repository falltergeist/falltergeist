// Project includes
#include "../VFS/DatArchiveStreamWrapper.h"
#include "../Exception.h"

// Third-party includes

// stdlib
#include <algorithm>

namespace Falltergeist {
    namespace VFS {
        DatArchiveStreamWrapper::DatArchiveStreamWrapper(const std::string& path) {
            _stream.open(path, std::ios_base::binary | std::ios_base::in);
            if (!_stream.is_open()) {
                throw Exception("DatArchiveStreamWrapper - can't open _stream: " + path);
            }

            _stream.seekg(0, std::ios_base::end);
            _actualFileSize = _stream.tellg();
            _stream.seekg(0, std::ios_base::beg);

            uint32_t fileSizeInDatFile = 0;
            // reading data size from dat file
            seek(_actualFileSize - 4);
            _readUint32(fileSizeInDatFile);
            if (fileSizeInDatFile != _actualFileSize) {
                throw Exception("DatArchiveStreamWrapper - wrong file size: " + std::to_string(fileSizeInDatFile) +
                                " should be: " + std::to_string(_actualFileSize));
            }

            // reading size of files tree
            seek(_actualFileSize - 8);
            _readUint32(_filesTreeSize);

            // reading total number of items in dat file
            seek(_actualFileSize - _filesTreeSize - 8);
            _readUint32(_filesCount);

            // reading files data one by one
            for (unsigned int i = 0; i != _filesCount; ++i) {
                uint32_t filenameSize = 0;
                uint8_t compressed = 0;
                uint32_t unpackedSize = 0;
                uint32_t packedSize = 0;
                uint32_t dataOffset = 0;

                _readUint32(filenameSize);
                std::string filename;
                filename.resize(filenameSize);
                readBytes(&filename[0], filename.length());
                std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);
                std::replace(filename.begin(), filename.end(), '\\','/');

                _readUint8(compressed);
                _readUint32(unpackedSize);
                _readUint32(packedSize);
                _readUint32(dataOffset);

                _entries.insert(std::make_pair(filename, DatArchiveEntry{
                    packedSize,
                    unpackedSize,
                    dataOffset,
                    (bool) compressed
                }));
            }
        }

        void DatArchiveStreamWrapper::seek(unsigned int position) {
            _stream.seekg(position, std::ios::beg);
        }

        unsigned int DatArchiveStreamWrapper::readBytes(char* destination, unsigned int size) {
            _stream.read(destination, size);
            if (_stream) {
                return size;
            }

            return _stream.gcount();
        }

        const std::map<std::string, DatArchiveEntry>& DatArchiveStreamWrapper::entries() const {
            return _entries;
        }

        void DatArchiveStreamWrapper::_readUint8(uint8_t& dest) {
            _stream.read(reinterpret_cast<char*>(&dest), 1);
        }

        void DatArchiveStreamWrapper::_readUint32(uint32_t& dest) {
            _stream.read(reinterpret_cast<char*>(&dest), 4);
        }
    }
}
