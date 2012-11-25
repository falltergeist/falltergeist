#include "TextLabel.h"

#include "SDL/SDL.h"
#include "ResourceManager.h"
#include "Fallout/AafFileType.h"

#include <iostream>

namespace Falltergeist
{

TextLabel::TextLabel(const char * label, int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = label;
    _aafFileType = ResourceManager::getAafFileType("font1.aaf");

    loadFromSurface(_generateSurface());
    setX(x);
    setY(y);
}

AafFileType * TextLabel::getAafFileType()
{
    return _aafFileType;
}

Surface * TextLabel::_generateSurface()
{
    unsigned int i = 0;
    int width = 0;
    int height = getAafFileType()->getMaximumHeight();
    while (_text[i] != 0)
    {

        getAafFileType()->getChar(_text[i]);
        if (_text[i] != ' ')
        {
            width += getAafFileType()->getChar(_text[i])->width;
            width += getAafFileType()->getHorizontalGap();
        }
        else
        {
            width += getAafFileType()->getSpaceWidth();
        }
        i++;

    }
    Surface * surface = new Surface(width,height);
    int  x, y;
    i = 0;
    x = 0;
    y = 0;
    while (_text[i] != 0)
    {
        if (_text[i] != ' ')
        {
            char * data = getAafFileType()->getChar(_text[i])->data;
            int width = getAafFileType()->getChar(_text[i])->width;
            int height = getAafFileType()->getChar(_text[i])->height;
            int delta = getAafFileType()->getMaximumHeight() - height;
            int j = 0;
            for (int yy = 0; yy != height; ++yy)
            {
                for (int xx = 0; xx != width; ++xx)
                {
                    if (data[j] != 0)
                    {
                        unsigned int color = (0 << 24) | (255 << 16) | (0 << 8) | 255;
                        surface->setPixel(x + xx,y + yy + delta, color);
                    }
                    j++;
                }
            }
            x+=width + getAafFileType()->getHorizontalGap();
        }
        else
        {
            x += getAafFileType()->getSpaceWidth();
        }
        i++;
    }
    SDL_SetColorKey(surface->getSurface(),SDL_SRCCOLORKEY,0);
    return surface;
}

}

