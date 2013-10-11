#ifndef FALLTERGEIST_MOUSE_H
#define FALLTERGEIST_MOUSE_H

#include <SDL/SDL.h>
#include "../Engine/InteractiveSurface.h"
#include "../Engine/ResourceManager.h"

namespace Falltergeist
{

class Mouse : public InteractiveSurface
{
protected:
    int _cursorX;
    int _cursorY;
public:
    enum {BIG_ARROW = 1,
          SCROLL_W,
          SCROLL_W_X,
          SCROLL_NW,
          SCROLL_NW_X,
          SCROLL_N,
          SCROLL_N_X,
          SCROLL_NE,
          SCROLL_NE_X,
          SCROLL_E,
          SCROLL_E_X,
          SCROLL_SE,
          SCROLL_SE_X,
          SCROLL_S,
          SCROLL_S_X,
          SCROLL_SW,
          SCROLL_SW_X};
    Mouse();
    ~Mouse();
    virtual Surface * think();
    int cursorX();
    int cursorY();
    void setCursorX(int x);
    void setCursorY(int y);
    void setCursor(unsigned int type);
    virtual int x();
    virtual int y();

};

}

#endif // FALLTERGEIST_MOUSE_H
