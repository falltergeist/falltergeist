// Project includes
#include "../UI/ElevatorProgress.h"
#include "../Graphics/Rectangle.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        using Point = Graphics::Point;
        using Size = Graphics::Size;

        ElevatorProgress::ElevatorProgress(uint8_t progress, const Graphics::Point& pos) : Base(pos), _progress(progress)
        {
            _sprite = std::make_shared<Graphics::Sprite>("art/intrface/gaj000.frm");

            for (auto i = 0; i < 13; i++) {
                _rects.push_back({0, i * 55 + 1, 92, 56});
            }
            _size = Size(92, 56);
        }

        ElevatorProgress::ElevatorProgress(const Graphics::Point& pos) : ElevatorProgress(0, pos)
        {
        }

        uint8_t ElevatorProgress::progress() const
        {
            return _progress;
        }

        void ElevatorProgress::setProgress(uint8_t progress)
        {
            if (progress < 13) {
                _progress = progress;
            }
        }

        bool ElevatorProgress::opaque(const Graphics::Point &pos)
        {
            if (pos.x() > _size.width() || pos.x() < 0 || pos.y() > _size.height() || pos.y() < 0) {
                return false;
            }

            SDL_Rect rect = _rects.at(_progress);
            return _sprite->opaque(Point(pos.x() + rect.x, pos.y() + rect.y));
        }

        void ElevatorProgress::render(bool eggTransparency)
        {
            SDL_Rect rect = _rects.at(_progress);
            _sprite->renderCropped(position(), Graphics::Rectangle(Point(rect.x, rect.y), Size(rect.w, rect.h)));
        }
    }
}
