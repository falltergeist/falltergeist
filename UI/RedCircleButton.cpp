#include "RedCircleButton.h"

namespace Falltergeist
{

RedCircleButton::RedCircleButton(int x, int y) : ImageButton(0,0,x,y)
{  
    _releasedImage = (char*)"art/intrface/menuup.frm";
    _pressedImage = (char*)"art/intrface/menudown.frm";
}

}
