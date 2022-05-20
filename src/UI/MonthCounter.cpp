#include "../UI/MonthCounter.h"

namespace Falltergeist
{
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
            _sprite = std::make_shared<Graphics::Sprite>("art/intrface/months.frm");

            for (auto i = 0; i<12; i++) {
                _rects.emplace_back(Point(0,i*15), Size(29,14));
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

            return _sprite->opaque(_rects.at(_month).position() + pos);
        }

        void MonthCounter::render(bool eggTransparency)
        {
            _sprite->renderCropped(position(), _rects.at(_month));
        }
    }
}
