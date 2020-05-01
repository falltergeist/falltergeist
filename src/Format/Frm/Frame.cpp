#include "../Frm/Frame.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Frm
        {
            Frame::Frame(uint16_t width, uint16_t height) : _indexes(width * height, 0)
            {
                _width = width;
                _height = height;
            }

            uint16_t Frame::width() const
            {
                return _width;
            }

            uint16_t Frame::height() const
            {
                return _height;
            }

            int16_t Frame::offsetX() const
            {
                return _offsetX;
            }

            void Frame::setOffsetX(int16_t value)
            {
                _offsetX = value;
            }

            int16_t Frame::offsetY() const
            {
                return _offsetY;
            }

            void Frame::setOffsetY(int16_t value)
            {
                _offsetY = value;
            }

            uint8_t Frame::index(uint16_t x, uint16_t y) const
            {
                if (x >= _width || y >= _height) return 0;

                return _indexes.at(_width*y + x);
            }

            uint8_t* Frame::data()
            {
                return _indexes.data();
            }
        }
    }
}
