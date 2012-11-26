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
    ImageButton(char * releasedImage, char * pressedImage, int x = 0, int y = 0);
    virtual void draw();
};

}
#endif // FALLTERGEIST_IMAGEBUTTON_H
