#pragma once

#include <cstdint>

namespace Falltergeist::Graphics {
    /**
     * This is immutable Value Object for RGBA color
     */
    class Color final {
    public:
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

        uint8_t red() const;

        uint8_t green() const;

        uint8_t blue() const;

        uint8_t alpha() const;

        const Color withAlpha(uint8_t alpha) const;

    private:
        uint8_t _red;

        uint8_t _green;

        uint8_t _blue;

        uint8_t _alpha;
    };
}
