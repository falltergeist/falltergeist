#include "../VFS/NativeFile.h"

namespace Falltergeist {
    namespace VFS {
        NativeFile::NativeFile(const std::string& path) {

        }
        unsigned int NativeFile::size() { return 0; }
        void NativeFile::open(IFile::OpenMode mode) {}
        void NativeFile::close() {}
        unsigned int NativeFile::seek(unsigned int offset,
                                      IFile::SeekFrom seekFrom) {
            return 0;
        }
        unsigned int NativeFile::tell() { return 0; }
        unsigned int NativeFile::read(unsigned char* to, unsigned int size) {
            return 0;
        }
        unsigned int NativeFile::Write(const char* buffer, unsigned int size) {
            return 0;
        }
    }
}