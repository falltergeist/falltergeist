#include "LeftArrowButton.h"

namespace Falltergeist
{

LeftArrowButton::LeftArrowButton(int x, int y) : ImageButton(0, 0, x, y)
{
    _releasedImage = (char*)"art/intrface/slu.frm";
    _pressedImage = (char*)"art/intrface/sld.frm";
}

}
