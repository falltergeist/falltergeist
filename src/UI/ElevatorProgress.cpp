#include "../UI/ElevatorProgress.h"
#include "../Graphics/Rectangle.h"

namespace Falltergeist
{
    using namespace std;

    namespace UI
    {

        ElevatorProgress::ElevatorProgress(uint8_t progress, const Point& pos) : Base(pos), _progress(progress)
        {
            _sprite = make_shared<Graphics::Sprite>("art/intrface/gaj000.frm");

            for (auto i = 0; i < 13; i++) {
                _rects.push_back({0, i * 55 + 1, 92, 56});
            }
            _size = Size(92, 56);
        }

        ElevatorProgress::ElevatorProgress(const Point& pos) : ElevatorProgress(0, pos)
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

        bool ElevatorProgress::opaque(const Point &pos)
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
