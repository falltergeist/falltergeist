#pragma once

#include <vector>
#include "../VFS/IFile.h"

namespace Falltergeist {
    namespace VFS {
        class MemoryDriver;

        class MemoryFile final : public IFile {
        public:
            MemoryFile() = default;

            MemoryFile(const MemoryFile& other) = delete;

            MemoryFile(MemoryFile&& other) = delete;

            MemoryFile& operator=(MemoryFile other) = delete;

            ~MemoryFile() override = default;

            unsigned int size() override;

            bool isOpened() override;

            unsigned int seek(unsigned int position, SeekFrom seekFrom) override;

            unsigned int tell() override;

            unsigned int read(unsigned char *to, unsigned int size) override;

            unsigned int read(char* to, unsigned int size) override;

            unsigned int write(const char *from, unsigned int size) override;

        protected:
            friend class MemoryDriver;

            friend class DatArchiveDriver;

            void _open(OpenMode mode) override;

            void _close() override;

        private:
            bool _isOpened = false;

            std::vector<unsigned char> _data;

            unsigned int _seekPosition = 0;

            OpenMode _mode = OpenMode::Read;
        };
    }
}
