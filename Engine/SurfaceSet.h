#ifndef FALLTERGEIST_SURFACESET_H
#define FALLTERGEIST_SURFACESET_H

#include "Engine/InteractiveSurface.h"
#include <vector>

namespace Falltergeist
{

class SurfaceSet : public InteractiveSurface
{
protected:
    std::vector<Surface *> * _surfaces;
public:
    SurfaceSet(int x = 0, int y = 0);
    ~SurfaceSet();
    unsigned int currentSurface;
    void addSurface(Surface * surface);
    SDL_Surface * getSurface();
};

}
#endif // FALLTERGEIST_SURFACESET_H
