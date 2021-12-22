#pragma once

#include "../VFS/IFile.h"
#include "../VFS/DatArchiveEntry.h"
#include <functional>

namespace Falltergeist {
    namespace VFS {
        class DatArchiveDriver;

        class DatArchiveFile final : public IFile {
        public:
            typedef std::function<unsigned int (unsigned int seekPosition, unsigned char* to, unsigned int size)> fnReadBytes;

            DatArchiveFile(const DatArchiveEntry& entry, const fnReadBytes& readFunction);

            ~DatArchiveFile() override = default;

            unsigned int size() override;

            bool isOpened() override;

            unsigned int seek(unsigned int position, SeekFrom seekFrom) override;

            unsigned int tell() override;

            unsigned int read(unsigned char* to, unsigned int size) override;

            unsigned int write(const char* from, unsigned int size) override;

        protected:
            friend class DatArchiveDriver;

            void _open(OpenMode mode) override;

            void _close() override;

        private:
            bool _isOpened = false;
            unsigned int _seekPosition = 0;
            DatArchiveEntry _entry;
            fnReadBytes _readFunction;
        };
    }
}
