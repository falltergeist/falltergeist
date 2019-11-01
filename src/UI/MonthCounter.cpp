#include "../UI/MonthCounter.h"

namespace Falltergeist
{
    using namespace std;

    namespace UI
    {
        enum
        {
            MONTH_TEXTURE_WIDTH  = 28,
            MONTH_TEXTURE_HEIGHT = 14,
            MONTH_TEXTURE_HORIZONTAL_OFFSET = 15
        };

        MonthCounter::MonthCounter(Month month, const Point& pos) : Base(pos), _month(month)
        {
            _sprite = make_shared<Graphics::Sprite>("art/intrface/months.frm");

            for (auto i = 0; i<12; i++) {
                _rects.push_back({0,i*15,29,14});
            }
            _size = Size(29,14);
        }

        MonthCounter::MonthCounter(const Point& pos) : MonthCounter(Month::JANUARY, pos)
        {
        }

        MonthCounter::Month MonthCounter::month() const
        {
            return _month;
        }

        void MonthCounter::setMonth(Month month)
        {
            _month = month;
        }

        bool MonthCounter::opaque(const Point &pos)
        {
            if (pos.x() > _size.width() || pos.x()<0 || pos.y() > _size.height() || pos.y()<0) {
                return false;
            }

            SDL_Rect rect = _rects.at(_month);
            return _sprite->opaque(pos.x()+rect.x, pos.y()+rect.y);
        }

        void MonthCounter::render(bool eggTransparency)
        {
            SDL_Rect rect = _rects.at(_month);
            _sprite->renderCropped(position().x(), position().y(), rect.x, rect.y, rect.w, rect.h);
        }
    }
}
