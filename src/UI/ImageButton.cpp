#include "src/UI/ImageButton.h"
#include "src/Engine/ResourceManager.h"

namespace Falltergeist
{

ImageButton::ImageButton(const char * releasedImage, const char * pressedImage, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _releasedImage = (char*)releasedImage;
    _pressedImage = (char*)pressedImage;
}

void ImageButton::draw()
{
    InteractiveSurface::draw();
    if (_hovered && _leftButtonPressed)
    {
        loadFromSurface(ResourceManager::getSurface(_pressedImage, getX(), getY()));
    }
    else
    {
        loadFromSurface(ResourceManager::getSurface(_releasedImage, getX(), getY()));
    }
}

void ImageButton::setPressedImage(const char * pressedImage)
{
    _pressedImage = (char*)pressedImage;
}

void ImageButton::setReleasedImage(const char * releasedImage)
{
    _releasedImage = (char*)releasedImage;
}

}
