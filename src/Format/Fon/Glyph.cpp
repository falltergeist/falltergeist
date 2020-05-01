#include "../Fon/Glyph.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Fon
        {
            Glyph::Glyph(uint32_t width, uint32_t height) : _width(width), _height(height)
            {
            }

            uint32_t Glyph::width() const
            {
                return _width;
            }

            void Glyph::setWidth(uint32_t width)
            {
                _width = width;
            }

            uint32_t Glyph::height() const
            {
                return _height;
            }

            void Glyph::setHeight(uint32_t height)
            {
                _height = height;
            }

            uint32_t Glyph::dataOffset() const
            {
                return _dataOffset;
            }

            void Glyph::setDataOffset(uint32_t value)
            {
                _dataOffset = value;
            }
        }
    }
}
