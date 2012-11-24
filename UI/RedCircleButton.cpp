#include "RedCircleButton.h"
#include "ResourceManager.h"

namespace Falltergeist
{

RedCircleButton::RedCircleButton(int x, int y) : InteractiveSurface(0,0)
{  
    loadFromSurface(ResourceManager::getSurface("art/intrface/menuup.frm"));
    setX(x);
    setY(y);
}

}
