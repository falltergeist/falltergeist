// Project includes
#include "../VFS/MemoryFile.h"

// Third-party includes

// stdlib
#include <cstring>

namespace Falltergeist {
    namespace VFS {
        unsigned int MemoryFile::size() {
            return _data.size();
        }

        void MemoryFile::_open(IFile::OpenMode mode) {
            // TODO handle Append and Truncate mode
            _seekPosition = 0;
            _isOpened = true;
            _mode = mode;
        }

        bool MemoryFile::isOpened() {
            return _isOpened;
        }

        void MemoryFile::_close() {
            _isOpened = false;
        }

        unsigned int MemoryFile::seek(unsigned int position, SeekFrom seekFrom) {
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

        unsigned int MemoryFile::tell() {
            return _seekPosition;
        }

        unsigned int MemoryFile::read(unsigned char* to, unsigned int size) {
            if (!isOpened()) {
                return 0;
            }

            unsigned int bytesAvailable = std::min(size, this->size() - tell());
            if (bytesAvailable == 0) {
                return 0;
            }

            memcpy(to, _data.data(), bytesAvailable);
            _seekPosition += bytesAvailable;

            return bytesAvailable;
        }

        unsigned int MemoryFile::read(char* to, unsigned int size) {
            return read(reinterpret_cast<unsigned char*>(to), size);
        }

        unsigned int MemoryFile::write(const char* from, unsigned int size) {
            if (!isOpened() || _mode == OpenMode::Read) {
                return 0;
            }

            unsigned int bytesLeft = this->size() - tell();
            if (size > bytesLeft) {
                _data.resize(_data.size() + (size - bytesLeft));
            }

            memcpy(_data.data() + tell(), from, size);
            _seekPosition += size;

            return size;
        }
    }
}
