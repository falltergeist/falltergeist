#include "../Graphics/Rectangle.h"
#include <assert.h>

namespace Falltergeist {
    namespace Graphics {
        Rectangle::Rectangle(const Point &a, const Point& b)
        : _a(a), _b(b), _size(Size(b-a)) {
            assert(b >= a);
        }

        Rectangle::Rectangle(const Point &position, const Size& size)
        : _a(position), _b(position + Point(size.width(), size.height())), _size(size) {
        }


        const Point& Rectangle::position() const {
            return _a;
        }

        const Point& Rectangle::secondPosition() const {
            return _b;
        }


        const Size& Rectangle::size() const {
            return _size;
        }

        bool Rectangle::hasIntersectionWith(const Rectangle& other) const {
            return contains(other._a) || contains(other._b) || other.contains(_a) || other.contains(_b);
        }

        bool Rectangle::contains(const Point& point) const {
            return point >= _a && point <= _b;
        }
    }
}
