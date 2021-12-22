#pragma once

#include "../VFS/IFile.h"
#include <string>
#include <fstream>
#include <filesystem>

namespace Falltergeist {
    namespace VFS {
        class NativeDriver;

        class NativeFile final : public IFile {
        public:
            NativeFile(const std::filesystem::path& path);

            ~NativeFile() override = default;

            unsigned int size() override;

            bool isOpened() override;

            unsigned int seek(unsigned int offset, SeekFrom seekFrom) override;

            unsigned int tell() override;

            unsigned int read(unsigned char* to, unsigned int size) override;

            unsigned int read(char* to, unsigned int size) override;

            unsigned int write(const char* from, unsigned int size) override;

        protected:
            friend class NativeDriver;

            void _open(OpenMode mode) override;

            void _close() override;

        private:
            std::fstream _stream;
            std::filesystem::path _path;
            OpenMode _mode = OpenMode::Read;
        };
    }
}
