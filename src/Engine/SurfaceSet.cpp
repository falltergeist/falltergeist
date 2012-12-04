#include "src/Engine/SurfaceSet.h"

namespace Falltergeist
{

SurfaceSet::SurfaceSet(int x, int y) : InteractiveSurface(0,0,x,y)
{
    _surfaces = new std::vector<Surface *>;
    currentSurface = 0;
}

SurfaceSet::~SurfaceSet()
{
    delete _surfaces;
}

void SurfaceSet::addSurface(Surface * surface)
{
    _surfaces->push_back(surface);
}

SDL_Surface * SurfaceSet::getSurface()
{
    return _surfaces->at(currentSurface)->getSurface();
}

}
