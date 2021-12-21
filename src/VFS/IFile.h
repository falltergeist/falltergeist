#pragma once

namespace Falltergeist {
    namespace VFS {
        class IFile {
        public:
            enum class OpenMode {
                Read
            };

            enum class SeekFrom {
            };

            virtual ~IFile() = default;

            virtual unsigned int size() = 0;

            virtual void open(OpenMode mode) = 0;

            virtual void close() = 0;

            virtual unsigned int seek(unsigned int offset, SeekFrom seekFrom) = 0;

            virtual unsigned int tell() = 0;

            virtual unsigned int read(unsigned char* to, unsigned int size) = 0;

            virtual unsigned int Write(const char* buffer, unsigned int size) = 0;
        };
    }
}