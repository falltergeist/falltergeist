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
        namespace Frm
        {
            class Frame
            {
                public:
                    Frame() = default;
                    Frame(uint16_t width, uint16_t height);
                    Frame(const Frame& other) = delete;
                    Frame(Frame&& other) = default;
                    Frame& operator= (const Frame&) = delete;
                    Frame& operator= (Frame&&) = default;
                    ~Frame() = default;

                    uint16_t width() const;
                    uint16_t height() const;

                    int16_t offsetX() const;
                    void setOffsetX(int16_t value);

                    int16_t offsetY() const;
                    void setOffsetY(int16_t value);

                    uint8_t index(uint16_t x, uint16_t y) const;

                    uint8_t* data();

                protected:
                    uint16_t _width = 0;
                    uint16_t _height = 0;
                    int16_t _offsetX = 0;
                    int16_t _offsetY = 0;
                    std::vector<uint8_t> _indexes;
            };
        }
    }
}
