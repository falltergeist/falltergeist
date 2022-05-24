#pragma once

// Project includes

// Third-party includes

// stdlib
#include <cstdint>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Aaf
        {
            class Glyph
            {
                public:
                    Glyph(uint16_t width, uint16_t height);
                    ~Glyph();

                    uint16_t width() const;
                    void setWidth(uint16_t width);

                    uint16_t height() const;
                    void setHeight(uint16_t height);

                    uint32_t dataOffset() const;
                    void setDataOffset(uint32_t value);

                protected:
                    uint16_t _width = 0;
                    uint16_t _height = 0;
                    uint32_t _dataOffset = 0;

                    std::vector<unsigned char> _data;
            };
        }
    }
}
