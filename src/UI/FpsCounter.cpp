#include <sstream>
#include "../UI/FpsCounter.h"

namespace Falltergeist
{
    namespace UI
    {
        FpsCounter::FpsCounter(const Point& pos) : TextArea(pos)
        {
            _millisecondsTracked = 0;
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

        void FpsCounter::think(float deltaTime)
        {
            _millisecondsTracked += deltaTime;

            if (_millisecondsTracked >= 1000.0f) {
                _millisecondsTracked -= 1000.0f;
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
