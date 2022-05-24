// Project includes
#include "../../Format/Aaf/Glyph.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Aaf
        {
            Glyph::Glyph(uint16_t width, uint16_t height) : _width(width), _height(height)
            {
            }

            Glyph::~Glyph()
            {
            }

            uint16_t Glyph::height() const
            {
                return _height;
            }

            void Glyph::setHeight(uint16_t height)
            {
                _height = height;
            }

            uint16_t Glyph::width() const
            {
                return _width;
            }

            void Glyph::setWidth(uint16_t width)
            {
                _width = width;
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
