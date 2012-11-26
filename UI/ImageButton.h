#ifndef FALLTERGEIST_IMAGEBUTTON_H
#define FALLTERGEIST_IMAGEBUTTON_H

#include "InteractiveSurface.h"

namespace Falltergeist
{

class ImageButton : public InteractiveSurface
{
protected:
    char * _releasedImage;
    char * _pressedImage;
public:
    ImageButton(const char * releasedImage = 0, const char * pressedImage = 0, int x = 0, int y = 0);
    virtual void draw();
    void setReleasedImage(const char * releasedImage);
    void setPressedImage(const char * pressedImage);
};

}
#endif // FALLTERGEIST_IMAGEBUTTON_H
