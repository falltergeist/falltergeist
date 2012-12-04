#include "../UI/FpsCounter.h"
#include <sstream>

namespace Falltergeist
{

FpsCounter::FpsCounter(int x, int y) : TextArea(x,y)
{
    _lastTicks = SDL_GetTicks();
    _frames = 0;
    setText(_frames);
    setWidth(40);
    setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
}

void FpsCounter::think()
{
    if (_lastTicks + 1000 > SDL_GetTicks())
    {
        _frames++;
    }
    else
    {
        setText(_frames);
        _frames = 0;
        _lastTicks = SDL_GetTicks();
    }
}

}
