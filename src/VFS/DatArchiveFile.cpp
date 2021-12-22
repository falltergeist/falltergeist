#include "../VFS/DatArchiveFile.h"

namespace Falltergeist {
    namespace VFS {
        DatArchiveFile::DatArchiveFile(const DatArchiveEntry& entry,  const fnReadBytes& readFunction) : _entry(entry), _readFunction(readFunction) {
        }

        unsigned int DatArchiveFile::size() {
            return _entry.unpackedSize;
        }

        void DatArchiveFile::_open(OpenMode mode) {
            if (mode != OpenMode::Read) {
                return;
            }

            _isOpened = true;
        }

        bool DatArchiveFile::isOpened() {
            return _isOpened;
        }

        void DatArchiveFile::_close() {
            _isOpened = false;
        }

        unsigned int DatArchiveFile::seek(unsigned int position, IFile::SeekFrom seekFrom) {
            if (!isOpened()) {
                return 0;
            }

            if (seekFrom == SeekFrom::Begin) {
                _seekPosition = position;
            } else if (seekFrom == SeekFrom::End) {
                _seekPosition = size() - position;
            } else {
                _seekPosition += position;
            }

            _seekPosition = std::min(_seekPosition, size() - 1);

            return tell();
        }

        unsigned int DatArchiveFile::tell() {
            if (!isOpened()) {
                return 0;
            }
            return _seekPosition;
        }

        unsigned int DatArchiveFile::read(unsigned char* to, unsigned int size) {
            if (!isOpened()) {
                return 0;
            }

            unsigned int bytesAvailable = std::min(size, this->size() - tell());
            if (bytesAvailable == 0) {
                return 0;
            }

            _readFunction(_entry.dataOffset + tell(), to, bytesAvailable);
            _seekPosition += bytesAvailable;

            return bytesAvailable;
        }

        unsigned int DatArchiveFile::read(char* to, unsigned int size) {
            return read(reinterpret_cast<unsigned char*>(to), size);
        }

        unsigned int DatArchiveFile::write(const char* from, unsigned int size) {
            if (!isOpened()) {
                return 0;
            }

            // does not support write operations
            return 0;
        }
    }
}
