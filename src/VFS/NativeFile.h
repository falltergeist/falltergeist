#pragma once

#include "../VFS/IFile.h"
#include <string>

namespace Falltergeist {
    namespace VFS {
        class NativeFile final : public IFile {
        public:
            NativeFile(const std::string& path);

            ~NativeFile() override = default;

            unsigned int size() override;

            void open(OpenMode mode) override;

            void close() override;

            unsigned int seek(unsigned int offset, SeekFrom seekFrom) override;

            unsigned int tell() override;

            unsigned int read(unsigned char* to, unsigned int size) override;

            unsigned int Write(const char* buffer, unsigned int size) override;
        };
    }
}