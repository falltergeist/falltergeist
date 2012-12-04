#include "../UI/HiddenMask.h"

namespace Falltergeist
{

HiddenMask::HiddenMask(unsigned int width, unsigned int height, int x, int y) : InteractiveSurface(width, height, x , y)
{
    setBackgroundColor(0x77FF0000);
    hide();
}

HiddenMask::HiddenMask(Surface * other) : InteractiveSurface(other)
{
    hide();
}

}
