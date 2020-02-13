#include "../Pal/Color.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Pal
        {
            Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
            {
                _red = red;
                _green = green;
                _blue = blue;
                _alpha = alpha;
            }

            Color::~Color()
            {
            }

            void Color::setRed(uint8_t red)
            {
                _red = red;
            }

            uint8_t Color::red() const
            {
                return _red;
            }

            void Color::setGreen(uint8_t green)
            {
                _green = green;
            }

            uint8_t Color::green() const
            {
                return _green;
            }

            void Color::setBlue(uint8_t blue)
            {
                _blue = blue;
            }

            uint8_t Color::blue() const
            {
                return _blue;
            }

            void Color::setAlpha(uint8_t alpha)
            {
                _alpha = alpha;
            }

            uint8_t Color::alpha() const
            {
                return _alpha;
            }

            Color::operator int() const
            {
                return (int) (unsigned int) *this;
            }

            Color::operator unsigned int() const
            {
                uint8_t k;
                if (_nomod) {
                    k = 1;
                }
                else
                {
                    k = 4;
                }
                return ((red() * k) << 24) | ((green() * k) << 16) | ((blue() * k) << 8) | alpha();
            }

            void Color::nomod()
            {
                _nomod= true;
            }
        }
    }
}
