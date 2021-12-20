#include "../UI/Image.h"

namespace Falltergeist
{
    namespace UI
    {
        Image::Image(std::unique_ptr<Graphics::Sprite> sprite) : Falltergeist::UI::Base()
        {
            this->sprite = std::move(sprite);
        }

        void Image::render(bool eggTransparency)
        {
            sprite->trans(_trans);
            sprite->render(position().x(),position().y(), eggTransparency, light(), _outline, _lightLevel);
        }

        Size Image::size() const
        {
            return sprite->size();
        }

        bool Image::opaque(unsigned int x, unsigned int y)
        {
            return sprite->opaque(x, y);
        }

        bool Image::opaque(const Point &position)
        {
            if (position.x() < 0 || position.y() < 0) {
                return false;
            }
            return opaque((unsigned)position.x(), (unsigned)position.y());
        }

        void Image::render(const Size& size, bool eggTransparency)
        {
            sprite->renderScaled(position().x(), position().y(), size, eggTransparency, light(), _outline);
        }
    }
}
