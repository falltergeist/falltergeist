#include "RightArrowButton.h"

namespace Falltergeist
{

RightArrowButton::RightArrowButton(int x, int y) : ImageButton(0, 0, x, y)
{
    _pressedImage = (char*)"art/intrface/srd.frm";
    _releasedImage = (char*)"art/intrface/sru.frm";
}


}
