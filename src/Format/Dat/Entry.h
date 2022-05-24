#pragma once

// Project includes

// Third-party includes

// stdlib
#include <cstdint>
#include <memory>
#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class File;

            class Entry
            {
                public:
                    Entry(File* datFile);

                    std::string filename() const;
                    void setFilename(std::string value);

                    uint32_t packedSize() const;
                    void setPackedSize(uint32_t value);

                    uint32_t unpackedSize() const;
                    void setUnpackedSize(uint32_t value);

                    uint32_t dataOffset() const;
                    void setDataOffset(uint32_t value);

                    bool compressed() const;
                    void setCompressed(bool value);

                    File* datFile();

                protected:
                    File* _datFile;
                    std::string _filename;
                    uint32_t _packedSize;
                    uint32_t _unpackedSize;
                    uint32_t _dataOffset;
                    bool _compressed;
            };
        }
    }
}
