#include "ImageButton.h"
#include "ResourceManager.h"

namespace Falltergeist
{

ImageButton::ImageButton(char * releasedImage, char * pressedImage, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _releasedImage = releasedImage;
    _pressedImage = pressedImage;
}

void ImageButton::draw()
{
    if (_hovered && _leftButtonPressed)
    {
        loadFromSurface(ResourceManager::getSurface(_pressedImage, getX(), getY()));
    }
    else
    {
        loadFromSurface(ResourceManager::getSurface(_releasedImage, getX(), getY()));
    }
}

}
