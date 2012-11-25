#ifndef FALLTERGEIST_SURFACE_H
#define FALLTERGEIST_SURFACE_H

#include "SDL/SDL.h"
#include "Exception.h"

namespace Falltergeist
{
class FrmFileType;

class Surface
{
protected:
    SDL_Surface * _surface;
    int _x;
    int _y;
    void _lock();
    void _unlock();
public:
    Surface(int width = 0, int height = 0, int x = 0, int y = 0);
    Surface(Surface * other);
    virtual ~Surface();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    unsigned int getPixel(int x,int y);
    void setPixel(int x, int y, unsigned int color);
    virtual SDL_Surface * getSurface();

    void loadFromSurface(Surface * surface);
    void setX(int x);
    void setY(int y);
    void clear();
    virtual void think();
    virtual void blit(Surface * surface);
};

}
#endif // FALLTERGEIST_SURFACE_H
