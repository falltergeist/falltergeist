#ifndef FALLTERGEIST_MOUSE_H
#define FALLTERGEIST_MOUSE_H

#include <SDL/SDL.h>
#include "../Engine/InteractiveSurface.h"

namespace Falltergeist
{

class Mouse : public InteractiveSurface
{

public:
    Mouse();
    virtual Surface * think();
    ~Mouse();

};

}

#endif // FALLTERGEIST_MOUSE_H
