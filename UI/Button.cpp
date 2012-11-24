#include "Button.h"

namespace Falltergeist
{

Button::Button(int width, int height, int x, int y) : InteractiveSurface(width,height,x,y)
{
}

Button::Button(Surface * surface) : InteractiveSurface(surface)
{
}

}
