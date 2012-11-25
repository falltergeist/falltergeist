#include "TextLabel.h"

#include "SDL/SDL.h"
#include "ResourceManager.h"
#include "Fallout/AafFileType.h"

#include <iostream>

namespace Falltergeist
{

TextLabel::TextLabel(const char * label, const char * filename, int x, int y) : InteractiveSurface(0,0,x,y)
{
    _label = label;
    _font = new Font(filename);
    //loadFromSurface(_generateSurface());
    //setColor(0x00FF00FF);
    //setX(x);
    //setY(y);
}

Surface * TextLabel::_generateSurface()
{

    unsigned int i = 0;
    int width = 0;
    int height = _font->getHeight();
    while (_label[i] != 0)
    {
            width += _font->getGlyph(_label[i])->getWidth();
            width += _font->getHorizontalGap();
        i++;
    }

    Surface * surface = new Surface(width,height);
    i = 0;
    int x = 0;
    while (_label[i] != 0)
    {
        Surface * glyph = _font->getGlyph(_label[i]);
        glyph->setX(x);
        glyph->blit(surface);
        x += glyph->getWidth();
        x += _font->getHorizontalGap();
        i++;
    }
    SDL_SetColorKey(surface->getSurface(),SDL_SRCCOLORKEY,0);
    return surface;
}

Font * TextLabel::getFont()
{
    return _font;
}

void TextLabel::setColor(unsigned int color)
{
    _font->setColor(color);
    int x = getX();// + 200;
    int y = getY();
    loadFromSurface(_generateSurface());
    setX(x);
    setY(y);
}

}

