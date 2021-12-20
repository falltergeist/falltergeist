#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist {
    namespace Graphics {
        class Rectangle final {
        public:
            Rectangle(const Point &position, const Size &size);

            const Point &position() const;

            const Size &size() const;

        private:
            const Point _position;
            const Size _size;
        };
    }
}
