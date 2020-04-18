#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../UI/Rectangle.h"

namespace Falltergeist
{
    namespace UI
    {
        Rectangle::Rectangle(Point pos, Size size, SDL_Color color) : Base(pos), _size(size), _color(color)
        {
        }

        void Rectangle::render(bool eggTransparency)
        {
            Game::getInstance()->renderer()->drawRect(position(),_size, _color);
        }

        bool Rectangle::opaque(unsigned int x, unsigned int y)
        {
            return false;
        }

        bool Rectangle::opaque(const Point &pos)
        {
            return false;
        }

        Size Rectangle::size() const
        {
            return _size;
        }
    }
}
