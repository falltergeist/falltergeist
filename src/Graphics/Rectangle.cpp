#include "../Graphics/Rectangle.h"

namespace Falltergeist {
    namespace Graphics {
        Rectangle::Rectangle(const Point &position, const Size &size) : _position(position), _size(size) {
        }

        const Point &Rectangle::position() const {
            return _position;
        }

        const Size &Rectangle::size() const {
            return _size;
        }
    }
}
