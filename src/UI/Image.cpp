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
            sprite->render(position(), eggTransparency, light(), _outline, _lightLevel);
        }

        Size Image::size() const
        {
            return sprite->size();
        }

        bool Image::opaque(const Point &position)
        {
            if (position.x() < 0 || position.y() < 0) {
                return false;
            }
            return sprite->opaque(position);
        }

        void Image::render(const Size& size, bool eggTransparency)
        {
            sprite->renderScaled(position(), size, eggTransparency, light(), _outline);
        }
    }
}
