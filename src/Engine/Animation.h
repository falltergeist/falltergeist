#ifndef FALLTERGEIST_ANIMATION_H
#define FALLTERGEIST_ANIMATION_H

#include "../Engine/InteractiveSurface.h"
#include <vector>

namespace Falltergeist
{

class Animation : public InteractiveSurface
{   
protected:
    std::vector<std::vector<Surface *> *>  * _surfaceSets;
    unsigned int _frameRate;
    unsigned int _currentFrame;
    unsigned int _currentSurfaceSet;
    unsigned int _lastTicks;
public:
    Animation(const char * filename, int x = 0, int y = 0);
    ~Animation();
    SDL_Surface * getSurface();
    void loadFromFrmFile(const char * filename);
    void think();
};

}
#endif // FALLTERGEIST_ANIMATION_H
