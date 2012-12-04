#include "ClickMask.h"

namespace Falltergeist
{

ClickMask::ClickMask(unsigned int width, unsigned int height, int x, int y) : InteractiveSurface(width, height, x , y)
{
    setBackgroundColor(0x01000000);
    setBorderColor(0xFFFF0000);
}

}
