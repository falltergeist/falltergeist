#include "../VFS/DatArchiveFile.h"

namespace Falltergeist {
    namespace VFS {
        unsigned int DatArchiveFile::size() {
            return 0;
        }

        void DatArchiveFile::_open(IFile::OpenMode mode) {
        }

        bool DatArchiveFile::isOpened() {
            return false;
        }

        void DatArchiveFile::_close() {
        }

        unsigned int DatArchiveFile::seek(unsigned int offset, IFile::SeekFrom seekFrom) {
            return 0;
        }

        unsigned int DatArchiveFile::tell() {
            return 0;
        }

        unsigned int DatArchiveFile::read(unsigned char* to, unsigned int size) {
            return 0;
        }

        unsigned int DatArchiveFile::write(const char* from, unsigned int size) {
            return 0;
        }
    }
}
