#include <algorithm>
#include "../Graphics/Rect.h"

namespace Falltergeist
{
    namespace Graphics
    {
        bool Rect::inRect(const Point& needle, const Size& size)
        {
            return (needle.x() >= 0
                    && needle.x() < size.width()
                    && needle.y() >= 0
                    && needle.y() < size.height());
        }

        bool Rect::inRect(const Point& needle, const Point& topLeft, const Size& size)
        {
            Point bottomRight = topLeft + size;
            return (needle.x() >= topLeft.x()
                    && needle.x() < bottomRight.x()
                    && needle.y() >= topLeft.y()
                    && needle.y() < bottomRight.y());
        }

        bool Rect::intersects(const Point& topLeft1, const Size& size1, const Point& topLeft2, const Size& size2)
        {
            const Point bottomRight1 = topLeft1 + size1;
            const Point bottomRight2 = topLeft2 + size2;

            return !(std::max(topLeft1.x(), topLeft2.x()) > std::min(bottomRight1.x(), bottomRight2.x())
                     || std::max(topLeft1.y(), topLeft2.y()) > std::min(bottomRight1.y(), bottomRight2.y()));
        }
    }
}
