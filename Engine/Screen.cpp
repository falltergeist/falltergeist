#include "Engine/Screen.h"
#include "Engine/Surface.h"

namespace Falltergeist
{

const double Screen::BASE_WIDTH = 640.0;
const double Screen::BASE_HEIGHT = 480.0;

Screen::Screen(int width, int height, int bpp)
{
    std::cout << "Setting up video mode " << width << "x" << height << "x" << bpp << "...";
    _screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
    if (_screen == 0)
    {
        std::cout << "[FAIL]" << std::endl;
    }
    std::cout << "[OK]" << std::endl;

    _surface = new Surface(width,height);
}

Screen::~Screen()
{
    delete _surface;
}

Surface * Screen::getSurface()
{
    return _surface;
}

void Screen::clear()
{
    _surface->clear();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = getHeight();
    rect.w = getWidth();
    SDL_FillRect(_screen,&rect,0);
}

int Screen::getHeight()
{
    return _screen->h;
}

int Screen::getWidth()
{
    return _screen->w;
}

void Screen::flip()
{
    SDL_BlitSurface(_surface->getSurface(), 0, _screen, 0);


    if (SDL_Flip(_screen) == -1)
    {
        std::cout << "[ERROR]Can't flip screen" << std::endl;
        throw Exception(SDL_GetError());
    }
}

}
