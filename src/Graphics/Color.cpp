#include "../Graphics/Color.h"

namespace Falltergeist::Graphics {
    Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) : _red(red), _green(green), _blue(blue), _alpha(alpha) {
    }

    uint8_t Color::red() const {
        return _red;
    }

    uint8_t Color::green() const {
        return _green;
    }

    uint8_t Color::blue() const {
        return _blue;
    }

    uint8_t Color::alpha() const {
        return _alpha;
    }

    const Color Color::withAlpha(uint8_t alpha) const {
        return Color(_red, _green, _blue, alpha);
    }
}
