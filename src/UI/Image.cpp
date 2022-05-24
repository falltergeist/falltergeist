// Project includes
#include "../UI/Image.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        using Point = Graphics::Point;

        Image::Image(std::unique_ptr<Graphics::Sprite> sprite)
            : Falltergeist::UI::Base(Point(0, 0)), _sprite(std::move(sprite)) {
        }

        void Image::render(bool eggTransparency)
        {
            _sprite->trans(_trans);
            _sprite->render(position() + offset(), eggTransparency, light(), _outline, _lightLevel);
        }

        const Graphics::Size& Image::size() const
        {
            return _sprite->size();
        }

        bool Image::opaque(const Graphics::Point &position)
        {
            if (position.x() < 0 || position.y() < 0) {
                return false;
            }
            return _sprite->opaque(position);
        }

        void Image::render(const Graphics::Size& size, bool eggTransparency)
        {
            _sprite->renderScaled(position() + offset(), size, eggTransparency, light(), _outline);
        }
    }
}
