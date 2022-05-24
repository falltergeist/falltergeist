// Project includes
#include "../../Format/Dat/Entry.h"
#include "../../Format/Dat/File.h"

// Third-party includes

// stdlib
#include <algorithm>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            Entry::Entry(File* datFile)
            {
                _datFile = datFile;
            }

            std::string Entry::filename() const
            {
                return _filename;
            }

            void Entry::setFilename(std::string value)
            {
                std::replace(value.begin(), value.end(), '\\','/');
                std::transform(value.begin(), value.end(), value.begin(), ::tolower);
                _filename = value;
            }

            uint32_t Entry::packedSize() const
            {
                return _packedSize;
            }

            void Entry::setPackedSize(uint32_t value)
            {
                _packedSize = value;
            }

            uint32_t Entry::unpackedSize() const
            {
                return _unpackedSize;
            }

            void Entry::setUnpackedSize(uint32_t value)
            {
                _unpackedSize = value;
            }

            uint32_t Entry::dataOffset() const
            {
                return _dataOffset;
            }

            void Entry::setDataOffset(uint32_t value)
            {
                _dataOffset = value;
            }

            bool Entry::compressed() const
            {
                return _compressed;
            }

            void Entry::setCompressed(bool value)
            {
                _compressed = value;
            }

            File* Entry::datFile()
            {
                return _datFile;
            }
        }
    }
}
