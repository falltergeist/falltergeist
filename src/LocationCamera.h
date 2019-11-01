#pragma once

#include "Graphics/Point.h"
#include "Graphics/Size.h"

namespace Falltergeist
{
    using Graphics::Point;
    using Graphics::Size;

    class LocationCamera
    {
        protected:
            Point _center;
            Size _size;

        public:
            LocationCamera(const Size& size, const Point& center);
            ~LocationCamera();

            Point topLeft() const;

            const Point& center() const;
            void setCenter(const Point& pos);

            const Size& size() const;
            void setSize(const Size& size);
    };
}
