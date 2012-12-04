#ifndef FALLTERGEIST_CLICKMASK_H
#define FALLTERGEIST_CLICKMASK_H

#include "Engine/InteractiveSurface.h"

namespace Falltergeist
{

class ClickMask : public InteractiveSurface
{
public:
    ClickMask(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);
};

}
#endif // FALLTERGEIST_CLICKMASK_H
