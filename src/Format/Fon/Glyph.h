#pragma once

// Project includes

// Third-party includes

// stdlib
#include <vector>
#include <cstdint>

namespace Falltergeist
{
    namespace Format
    {
        namespace Fon
        {
            class Glyph
            {
                public:
                    Glyph(uint32_t width, uint32_t height);

                    uint32_t width() const;
                    void setWidth(uint32_t width);

                    uint32_t height() const;
                    void setHeight(uint32_t height);

                    uint32_t dataOffset() const;
                    void setDataOffset(uint32_t value);

                protected:
                    uint16_t _width = 0;
                    uint16_t _height = 0;
                    uint32_t _dataOffset = 0;
            };
        }
    }
}
