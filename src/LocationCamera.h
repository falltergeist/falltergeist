#pragma once

#include "Graphics/Point.h"
#include "Graphics/Size.h"

namespace Falltergeist
{
    class LocationCamera final
    {
        public:
            LocationCamera(const Graphics::Size& size, const Graphics::Point& center);

            ~LocationCamera();

            Graphics::Point topLeft() const;

            const Graphics::Point& center() const;

            void setCenter(const Graphics::Point& pos);

            const Graphics::Size& size() const;

            void setSize(const Graphics::Size& size);

        private:
            Graphics::Point _center;

            Graphics::Size _size;
    };
}
