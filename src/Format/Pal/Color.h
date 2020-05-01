#pragma once

#include <cstdint>

namespace Falltergeist
{
    namespace Format
    {
        namespace Pal
        {
            class Color
            {
                public:
                    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
                    ~Color();

                    operator int() const;
                    operator unsigned int() const;

                    void setRed(uint8_t red);
                    uint8_t red() const;

                    void setGreen(uint8_t green);
                    uint8_t green() const;

                    void setBlue(uint8_t blue);
                    uint8_t blue() const;

                    void setAlpha(uint8_t alpha);
                    uint8_t alpha() const;

                    void nomod();

                protected:
                    uint8_t _red;
                    uint8_t _green;
                    uint8_t _blue;
                    uint8_t _alpha;
                    bool _nomod = false;
            };
        }
    }
}
