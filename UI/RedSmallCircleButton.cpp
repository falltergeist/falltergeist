#include "RedSmallCircleButton.h"

namespace Falltergeist
{

RedSmallCircleButton::RedSmallCircleButton(int x, int y) : ImageButton(0, 0, x, y)
{
    _releasedImage = (char*)"art/intrface/lilredup.frm";
    _pressedImage = (char*)"art/intrface/lilreddn.frm";
}


}
