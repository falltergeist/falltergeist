#include "TextLabel.h"

#include "SDL/SDL.h"
#include "ResourceManager.h"
#include "Fallout/AafFileType.h"

#include <iostream>

namespace Falltergeist
{

TextLabel::TextLabel(const char * label, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _color = 0x00FF00FF;
    _width = 0;
    _height = 0;
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _label = label;
    _font = 0;
}

TextLabel::~TextLabel()
{
    delete _font; _font = 0;
}

void TextLabel::draw()
{
    if (_font == 0) throw Exception("TextLabel::draw() - font is not setted");
    unsigned int width, height;
    int x,y;

    //calculating size of text surface
    unsigned int i = 0;
    width = 0;
    height = _font->getHeight();
    while (_label[i] != 0)
    {
        width += _font->getGlyph(_label[i])->getWidth();
        width += _font->getHorizontalGap();
        i++;
    }

    // Creating new textSurface
    Surface * textSurface = new Surface(width,height);
    //SDL_SetColorKey(textSurface->getSurface(), SDL_SRCCOLORKEY, 0);
    i = 0;
    x = 0;
    while (_label[i] != 0)
    {
        Surface * glyph = _font->getGlyph(_label[i]);
        glyph->setX(x);
        glyph->blit(textSurface);
        x += glyph->getWidth();
        i++;
        if (i < strlen(_label))
        {
            x += _font->getHorizontalGap();
        }
    }

    if (_width == 0 && _height == 0)
    {
        textSurface->setX(getX());
        textSurface->setY(getY());
        loadFromSurface(textSurface);
        return;
    }

    if (_height == 0) _height = height;

    // using align
    Surface * surface = new Surface(_width,_height,getX(),getY());
    //SDL_SetColorKey(surface->getSurface(), SDL_SRCCOLORKEY, 0);
    x = 0; y = 0;
    switch(_verticalAlign)
    {
        case VERTICAL_ALIGN_TOP:
            break;
        case VERTIVAL_ALIGN_CENTER:
        case VERTICAL_ALIGN_JUSTIFY:
            y = (_height - height)/2 ;
            break;
        case VERTICAL_ALIGN_BOTTOM:
            y = _height - height;
            break;
    }
    switch(_horizontalAlign)
    {
        case HORIZONTAL_ALIGN_LEFT:
            break;
        case HORIZONTAL_ALIGN_CENTER:
            x = (_width - width)/2;
            break;
        case HORIZONTAL_ALIGN_RIGHT:
            x = _width - width;
            break;
        case HORIZONTAL_ALIGN_JUSTIFY:
            //@todo justify
            break;
    }
    textSurface->setX(x);
    textSurface->setY(y);
    textSurface->blit(surface);
    loadFromSurface(surface);
}

Font * TextLabel::getFont()
{
    return _font;
}

void TextLabel::setColor(unsigned int color)
{
    if (_color == color) return;
    _color = color;
    if (_font == 0) return;
    _font->setColor(_color);
    needRedraw = true;
}

void TextLabel::setFont(const char * filename)
{
    delete _font; _font = 0;
    _font = new Font(filename, _color);
    needRedraw = true;
}

void TextLabel::setWidth(unsigned int width)
{
    if (_width == width) return;
    _width = width;
    needRedraw = true;
}

unsigned int TextLabel::getWidth()
{
    return _width;
}

void TextLabel::setHeight(unsigned int height)
{
    if (_height == height) return;
    _height = height;
    needRedraw = true;
}

unsigned int TextLabel::getHeight()
{
    return _height;
}

void TextLabel::setHorizontalAlign(unsigned int align)
{
    if (_horizontalAlign == align) return;
    _horizontalAlign = align;
    needRedraw = true;
}

unsigned int TextLabel::getHorizontalAlign()
{
    return _horizontalAlign;
}

void TextLabel::setVerticalAlign(unsigned int align)
{
    if (_verticalAlign == align) return;
    _verticalAlign = align;
    needRedraw = true;
}

unsigned int TextLabel::getVerticalAlign()
{
    return _verticalAlign;
}

}
