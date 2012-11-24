#ifndef FALLTERGEIST_SCREEN_H
#define FALLTERGEIST_SCREEN_H

#include <iostream>
#include <SDL/SDL.h>

namespace Falltergeist
{
class Surface;


class Screen
{
protected:
    static const double BASE_WIDTH;
    static const double BASE_HEIGHT;
    SDL_Surface * _screen;
    Surface * _surface;
public:
    Screen(int width, int height, int bpp);
    ~Screen();
    Surface * getSurface();
    void clear();
    int getWidth();
    int getHeight();
    void flip();
};

}
#endif // FALLTERGEIST_SCREEN_H
