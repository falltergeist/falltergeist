/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../UI/TextArea.h"
#include "../Engine/Font.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "../Engine/ResourceManager.h"

namespace Falltergeist
{

TextArea::TextArea(libfalltergeist::MsgMessage * message, int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = 0;
    this->setText(message->text());
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _color = 0xFF00FF00;
    _font = ResourceManager::font("font1.aaf", _color);
    setNeedRedraw(true);
}

TextArea::TextArea(const char * text, int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = 0;
    this->setText(text);
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _color = 0xFF00FF00;
    _font = ResourceManager::font("font1.aaf", _color);
    setNeedRedraw(true);
}

TextArea::TextArea(int x, int y) : InteractiveSurface(0,0,x,y)
{
    _text = 0;
    this->setText(" ");
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _color = 0xFF00FF00;
    _font = ResourceManager::font("font1.aaf", _color);
    setNeedRedraw(true);
}


TextArea::~TextArea()
{
    if (_text != 0) delete [] _text;
}

void TextArea::draw()
{
    if (!needRedraw()) return;    
    InteractiveSurface::draw();

    // if no font was setted
    if (!_font) throw Exception("TextArea::draw() - font is not setted");

    // if text is empty
    if (_text == 0 || strlen(_text) == 0) throw Exception("TextArea::draw() - text is 0");

    //parse text to the string lines
    std::vector<std::string *> * strings = new std::vector<std::string *>;
    std::string * string = new std::string();
    for (unsigned int i = 0; i != strlen(_text); ++i)
    {
        unsigned char chr = _text[i];
        if (chr == 0x0A || chr == '\n')
        {
            strings->push_back(string);
            string = new std::string();
        }
        else
        {
            string->push_back(chr);
        }
    }
    if (!string->empty())
    {
        strings->push_back(string);
    }

    //convert strings list to surfaces list
    std::vector<Surface *> * surfaces = new std::vector<Surface *>;
    for (std::vector<std::string *>::iterator it = strings->begin(); it != strings->end(); ++it)
    {
        // calculate surface width
        unsigned int surfaceWidth = 0;
        for(unsigned int i = 0; i != (*it)->size(); ++i)
        {
            unsigned char chr = (*it)->at(i);

            if (chr == ' ')
            {
                surfaceWidth += _font->spaceWidth();
            }
            else
            {
                surfaceWidth += _font->glyph(chr)->width() + _font->horizontalGap();
            }
        }

        //create string surface
        surfaces->push_back(new Surface(surfaceWidth, _font->height()));
        //draw characters on string surface
        unsigned int x = 0;
        for(unsigned int i = 0; i != (*it)->size(); ++i)
        {
            unsigned char chr = (*it)->at(i);
            if (chr == ' ')
            {
                x += _font->spaceWidth();
            }
            else
            {
                Surface * glyph = _font->glyph(chr);
                glyph->setX(x);
                glyph->setY(0);
                glyph->copyTo(surfaces->back());
                x += glyph->width() + _font->horizontalGap();
            }
        }

    }

// if width or height are unknown then calculate them from text
//if (!_width || !_height)
    {
        // width = max line width
        for (std::vector<Surface *>::iterator it = surfaces->begin(); it != surfaces->end(); ++it)
        {
            if ((*it)->width() > _width) _width = (*it)->width();
        }

        _height = surfaces->size()*_font->height() + (surfaces->size() - 1)*_font->verticalGap();
    }

    // Creating resulting surface
    Surface * surface = new Surface(_width, _height);

    // foreach lines surfaces
    unsigned int x = 0;
    unsigned int y = 0;
    for (std::vector<Surface *>::iterator it = surfaces->begin(); it != surfaces->end(); ++it)
    {
        switch(_horizontalAlign)
        {
            case HORIZONTAL_ALIGN_LEFT:
                break;
            case HORIZONTAL_ALIGN_CENTER:
                x = (_width-(*it)->width())/2;
                break;
            case HORIZONTAL_ALIGN_RIGHT:
                x = _width - (*it)->width();
                break;
            case HORIZONTAL_ALIGN_JUSTIFY:
                //@todo justify
                break;
        }
        (*it)->setX(x);
        (*it)->setY(y);
        (*it)->copyTo(surface);
        y += _font->height() + _font->verticalGap();
    }

    surface->setX(this->x());
    surface->setY(this->y());
    loadFromSurface(surface);

    delete surface;
    delete surfaces;
    delete strings;
    delete string;

    setNeedRedraw(false);
}

unsigned int TextArea::color()
{
    return _color;
}

TextArea * TextArea::setColor(unsigned int color)
{
    if (_color == color) return this;
    _color = color;
    if (!_font) return this;
    _font->setColor(color);
    setNeedRedraw(true);
    return this;
}

unsigned int TextArea::height()
{
    return _height;
}

TextArea * TextArea::setHeight(unsigned int height)
{
    if (height == _height) return this;
    _height = height;
    setNeedRedraw(true);
    return this;
}

unsigned int TextArea::width()
{
    return _width;
}

TextArea * TextArea::setWidth(unsigned int width)
{
    if (_width == width) return this;
    _width = width;
    setNeedRedraw(true);
    return this;
}

unsigned char TextArea::horizontalAlign()
{
    return _horizontalAlign;
}

TextArea * TextArea::setHorizontalAlign(unsigned char align)
{
    if (_horizontalAlign == align) return this;
    _horizontalAlign = align;
    setNeedRedraw(true);
    return this;
}

unsigned char TextArea::verticalAlign()
{
    return _verticalAlign;
}

TextArea * TextArea::setVerticalAlign(unsigned char align)
{
    if (_verticalAlign == align) return this;
    _verticalAlign = align;
    setNeedRedraw(true);
    return this;
}

char * TextArea::text()
{
    return _text;
}

TextArea * TextArea::setText(libfalltergeist::MsgMessage * message)
{
    setText(message->text());
    return this;
}

TextArea * TextArea::setText(unsigned int number)
{
    std::stringstream ss;
    ss << number;
    setText(ss.str().c_str());
    return this;
}

TextArea * TextArea::setText(const char * text)
{
    delete [] _text;
    _text = new char[strlen(text)+1]();
    strcpy(_text, text);
    setNeedRedraw(true);
    return this;
}

TextArea * TextArea::setFont(const char * filename)
{
    _font = ResourceManager::font("font1.aaf", _color);
    setNeedRedraw(true);
    return this;
}

}
