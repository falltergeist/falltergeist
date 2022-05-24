#pragma once

// Project includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        // static class for Rectangle-related function
        class Rect
        {
            public:
                // checks if given point is located withing the rectangle specified by size
                static bool inRect(const Point& needle, const Size& size);

                // checks if given point is located withing the rectangle with given top-left position and size
                static bool inRect(const Point& needle, const Point& topLeft, const Size& size);

                // checks if two rectangles, given as their top-left positions and sizes, intersect each other
                static bool intersects(const Point& topLeft1, const Size& size1, const Point& topLeft2, const Size& size2);
        };
    }
}
