#include "../Graphics/Rect.h"
#include "../Graphics/Texture.h"
#include "../UI/HiddenMask.h"

namespace Falltergeist
{
    namespace UI
    {
        using Point = Graphics::Point;

        HiddenMask::HiddenMask(unsigned int width, unsigned int height, int x, int y) : Base(Point(x, y)) {
        }

        HiddenMask::~HiddenMask()
        {
        }

        void HiddenMask::render(bool eggTransparency)
        {
        }

        void HiddenMask::think(const float &deltaTime)
        {
        }

        bool HiddenMask::opaque(const Graphics::Point &pos)
        {
            return Graphics::Rect::inRect(pos, this->size());
        }
    }
}
