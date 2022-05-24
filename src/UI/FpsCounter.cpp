// Project includes
#include "../UI/FpsCounter.h"

// Third-party includes

// stdlib
#include <sstream>

namespace Falltergeist
{
    namespace UI
    {
        FpsCounter::FpsCounter(const Graphics::Point& pos) : TextArea(pos)
        {
            _millisecondsTracked = 0;
            setText("0");
            setWidth(40);
            setHorizontalAlign(TextArea::HorizontalAlign::RIGHT);
        }

        void FpsCounter::think(const float &deltaTime)
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
