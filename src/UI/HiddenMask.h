#ifndef FALLTERGEIST_HIDDENMASK_H
#define FALLTERGEIST_HIDDENMASK_H

#include "../Engine/InteractiveSurface.h"

namespace Falltergeist
{

class HiddenMask : public InteractiveSurface
{
public:
    HiddenMask(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);
    HiddenMask(Surface * other);
};

}
#endif // FALLTERGEIST_HIDDENMASK_H
