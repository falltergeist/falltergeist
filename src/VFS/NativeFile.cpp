// Project includes
#include "../VFS/NativeFile.h"

// Third-party includes

// stdlib
#include <cassert>

namespace Falltergeist {
    namespace VFS {
        static std::ios_base::seekdir convertSeekDirection(IFile::SeekFrom seekFrom) {
            switch (seekFrom) {
                case IFile::SeekFrom::Begin:
                    return std::ios_base::beg;
                case IFile::SeekFrom::Current:
                    return std::ios_base::cur;
                case IFile::SeekFrom::End:
                    return std::ios_base::end;
            }

            assert(false);
        };

        static std::ios_base::openmode convertOpenMode(IFile::OpenMode mode) {
            switch (mode) {
                case IFile::OpenMode::Read:
                    return std::fstream::binary | std::fstream::in;
                case IFile::OpenMode::WriteTruncate:
                    return std::fstream::binary | std::fstream::out | std::fstream::trunc;
                case IFile::OpenMode::WriteAppend:
                    return std::fstream::binary | std::fstream::out | std::fstream::app;
                case IFile::OpenMode::ReadWrite:
                    return std::fstream::binary | std::fstream::in | std::fstream::out;
                case IFile::OpenMode::ReadWriteTruncate:
                    return std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::trunc;
                case IFile::OpenMode::ReadWriteAppend:
                    return std::fstream::binary | std::fstream::in | std::fstream::out | std::fstream::app;
            }

            assert(false);
        }


        NativeFile::NativeFile(const std::filesystem::path& path) : _path(path) {
        }

        unsigned int NativeFile::size() {
            if (!isOpened()) {
                return 0;
            }

            unsigned int currentPosition = tell();
            seek(0, SeekFrom::End);
            unsigned int size = tell();
            seek(currentPosition, SeekFrom::Begin);
            return size;
        }

        void NativeFile::_open(IFile::OpenMode mode) {
            if (isOpened()) {
                // TODO allow reopening in other mode
                return;
            }

            _mode = mode;
            _stream.open(_path, convertOpenMode(mode));
        }

        bool NativeFile::isOpened() {
            return _stream.is_open();
        }

        void NativeFile::_close() {
            _stream.close();
        }

        unsigned int NativeFile::seek(unsigned int offset, SeekFrom seekFrom) {
            if (!isOpened()) {
                return 0;
            }

            _stream.seekg(offset, convertSeekDirection(seekFrom));
            _stream.seekp(offset, convertSeekDirection(seekFrom));

            return tell();
        }

        unsigned int NativeFile::tell() {
            return _stream.tellg();
        }

        unsigned int NativeFile::read(unsigned char* to, unsigned int size) {
            if (!isOpened()) {
                return 0;
            }

            _stream.read((char* )to, size);
            if (_stream) {
                return size;
            }

            return _stream.gcount();
        }

        unsigned int NativeFile::read(char* to, unsigned int size) {
            return read(reinterpret_cast<unsigned char*>(to), size);
        }

        unsigned int NativeFile::write(const char* from, unsigned int size) {
            if (!isOpened() || _mode == OpenMode::Read) {
                return 0;
            }

            _stream.write(from, size);
            if (_stream) {
                return size;
            }

            // Error during write
            return 0;
        }
    }
}
