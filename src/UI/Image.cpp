#include "../UI/Image.h"

namespace Falltergeist
{
    namespace UI
    {
        Image::Image(std::unique_ptr<Graphics::Sprite> sprite)
            : Falltergeist::UI::Base(Point(0, 0)), _sprite(std::move(sprite)) {
        }

        void Image::render(bool eggTransparency)
        {
            _sprite->trans(_trans);
            _sprite->render(position() + offset(), eggTransparency, light(), _outline, _lightLevel);
        }

        const Size& Image::size() const
        {
            return _sprite->size();
        }

        bool Image::opaque(const Point &position)
        {
            if (position.x() < 0 || position.y() < 0) {
                return false;
            }
            return _sprite->opaque(position);
        }

        void Image::render(const Size& size, bool eggTransparency)
        {
            _sprite->renderScaled(position() + offset(), size, eggTransparency, light(), _outline);
        }
    }
}
