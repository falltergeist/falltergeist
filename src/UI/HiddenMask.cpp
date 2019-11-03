#include "../Graphics/Rect.h"
#include "../Graphics/Texture.h"
#include "../UI/HiddenMask.h"

namespace Falltergeist
{
    namespace UI
    {
        HiddenMask::HiddenMask(unsigned int width, unsigned int height, int x, int y)// : Image(width, height)
        {
            setPosition({x, y});
        }

        HiddenMask::~HiddenMask()
        {
        }

        void HiddenMask::render(bool eggTransparency)
        {
        }

        void HiddenMask::think(float deltaTime)
        {
        }

        bool HiddenMask::opaque(const Point &pos)
        {
            return Graphics::Rect::inRect(pos, this->size());
        }
    }
}
