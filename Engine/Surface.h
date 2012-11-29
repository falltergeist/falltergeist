#ifndef FALLTERGEIST_SURFACE_H
#define FALLTERGEIST_SURFACE_H

#include "SDL/SDL.h"
#include "Engine/Exception.h"

namespace Falltergeist
{
class FrmFileType;

class Surface
{
protected:
    SDL_Surface * _surface;
    int _x;
    int _y;
    unsigned int _borderColor;
    void _lock();
    void _unlock();
public:
    bool needRedraw;
    Surface(int width = 0, int height = 0, int x = 0, int y = 0);
    Surface(Surface * other);
    virtual ~Surface();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    virtual SDL_Surface * getSurface();
    unsigned int getPixel(int x, int y);
    void setPixel(int x, int y, unsigned int color);
    void loadFromSurface(Surface * surface);
    void setX(int x);
    void setY(int y);
    void fill(unsigned int color);
    void border(unsigned int color);
    void clear();
    Surface * crop(int x = 0, int y = 0, int width = 0, int height = 0);
    virtual void think();
    virtual void draw();
    virtual void blit(Surface * surface);
};

}
#endif // FALLTERGEIST_SURFACE_H
