#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist {
    namespace Graphics {
        class Rectangle final {
        public:
            Rectangle(const Point& a, const Point& b);

            Rectangle(const Point& position, const Size& size);

            const Point& position() const;

            const Point& secondPosition() const;

            const Size& size() const;

            bool hasIntersectionWith(const Rectangle& other) const;

            bool contains(const Point& point) const;

        private:
            const Point _a;

            const Point _b;

            const Size _size;
        };
    }
}
