#pragma once

namespace Falltergeist {
    namespace VFS {
        class IDriver;

        class IFile {
        public:
            enum class OpenMode {
                Read,
                WriteTruncate,
                WriteAppend,
                ReadWrite,
                ReadWriteTruncate,
                ReadWriteAppend
            };

            enum class SeekFrom {
                Begin,
                Current,
                End
            };

            virtual ~IFile() = default;

            virtual unsigned int size() = 0;

            virtual bool isOpened() = 0;

            virtual unsigned int seek(unsigned int offset, SeekFrom seekFrom = SeekFrom::Current) = 0;

            virtual unsigned int tell() = 0;

            virtual unsigned int read(unsigned char* to, unsigned int size) = 0;

            virtual unsigned int write(const char* from, unsigned int size) = 0;

        protected:
            friend class IDriver;

            virtual void _open(OpenMode mode) = 0;

            virtual void _close() = 0;
        };
    }
}
