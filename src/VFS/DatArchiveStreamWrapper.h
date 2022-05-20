#pragma once

#include <fstream>
#include <stdint.h>
#include <map>
#include "../VFS/DatArchiveEntry.h"

namespace Falltergeist {
    namespace VFS {
        class DatArchiveStreamWrapper final {
        public:
            DatArchiveStreamWrapper(const std::string& path);

            DatArchiveStreamWrapper(const DatArchiveStreamWrapper& other) = delete;

            DatArchiveStreamWrapper(DatArchiveStreamWrapper&& other) = delete;

            void seek(unsigned int position);

            unsigned int readBytes(char* destination, unsigned int size);

            const std::map<std::string, DatArchiveEntry>& entries() const;

        private:
            uint32_t _actualFileSize = 0;

            uint32_t _filesTreeSize = 0;

            uint32_t _filesCount = 0;

            std::fstream _stream;

            void _readUint8(uint8_t& dest);

            void _readUint32(uint32_t& dest);

            std::map<std::string, DatArchiveEntry> _entries;
        };
    }
}
