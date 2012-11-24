#ifndef FALLTERGEIST_BUTTON_H
#define FALLTERGEIST_BUTTON_H

#include  "InteractiveSurface.h"

namespace Falltergeist
{

class Button : public InteractiveSurface
{
public:
    Button(int width, int height, int x = 0, int y = 0);
    Button(Surface * surface);
};

}
#endif // FALLTERGEIST_BUTTON_H
