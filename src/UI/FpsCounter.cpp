#include <sstream>
#include "../UI/FpsCounter.h"

namespace Falltergeist
{
    namespace UI
    {
        FpsCounter::FpsCounter(const Point& pos) : TextArea(pos)
        {
            _nanosecondsTracked = 0;
            setText("0");
            setWidth(40);
            setHorizontalAlign(TextArea::HorizontalAlign::RIGHT);
        }

        FpsCounter::FpsCounter(int x, int y) : FpsCounter(Point(x, y))
        {
        }

        FpsCounter::~FpsCounter()
        {
        }

        void FpsCounter::think(uint32_t nanosecondsPassed)
        {
            _nanosecondsTracked += nanosecondsPassed;

            uint32_t nanosecondsInOneSecond = 1e9;

            if (_nanosecondsTracked >= nanosecondsInOneSecond) { // 1 seconds
                _nanosecondsTracked -= nanosecondsInOneSecond;
                setText(std::to_string(_frames));
                _frames = 0;
            } else {
                _frames++;
            }
        }

        unsigned int FpsCounter::frames()
        {
            return _frames;
        }
    }
}
