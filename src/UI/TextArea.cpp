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

TextArea::TextArea(libfalltergeist::MsgMessage * message, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _text = 0;
    _lines = 0;
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    _color = 0xFF00FF00;
    _font = new Font("font1.aaf", _color);
    _wordWrap = false;
    this->setText(message->text());
    needRedraw(true);
}

TextArea::TextArea(const char * text, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _text = 0;
    _lines = 0;
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    _color = 0xFF00FF00;
    _font = new Font("font1.aaf", _color);
    _wordWrap = false;
    this->setText(text);
    needRedraw(true);
}

TextArea::TextArea(int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _text = 0;
    _lines = 0;
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    _color = 0xFF00FF00;
    _font = new Font("font1.aaf", _color);
    _wordWrap = false;
    this->setText(" ");
    needRedraw(true);
}


TextArea::~TextArea()
{
    delete [] _text;
    delete _lines;
    delete _font;
}


std::vector<std::string> * TextArea::lines()
{
    if (_lines != 0) return _lines;

    _lines = new std::vector<std::string>;

    unsigned int stringWidth = 0;
    unsigned int wordWidth = 0;
    std::string word = "";
    _lines->push_back("");
    for (unsigned int i = 0; i != strlen(_text); ++i)
    {
        unsigned char chr = _text[i];
        if (chr == 0x0D) //new line
        {
            ++i;
            _lines->back().append(word);
            _lines->push_back("");
            word = "";
            wordWidth = 0;
            stringWidth = 0;
        }
        else
        {
            //if (!word.empty() && chr != 0x20) wordWidth += _font->horizontalGap();
            word.push_back(chr);
            if (chr == 0x20)
            {
                wordWidth += _font->spaceWidth();
            }
            else
            {
                wordWidth += _font->glyph(chr)->width() + _font->horizontalGap();
            }

            if (_width*_height != 0 && (stringWidth + wordWidth >= _width))
            {
                if (_wordWrap)
                {
                    _lines->push_back("");
                    stringWidth = 0;
                }
                else
                {
                    _lines->back().append(word);
                    _lines->push_back("");
                    word = "";
                    wordWidth = 0;
                    stringWidth = 0;
                }
            }
            else
            {
                if (chr == 0x20)  // space
                {
                    _lines->back().append(word);
                    stringWidth += wordWidth;
                    word = "";
                    wordWidth = 0;
                }
            }
        }
    }
    if (!word.empty())
    {
        _lines->back().append(word);
    }

    return _lines;
}


void TextArea::_calculateSize()
{
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    // if text is empty
    if (_text == 0 || strlen(_text) == 0 || !_font) return;

    for (std::vector<std::string>::iterator it = lines()->begin(); it != lines()->end(); ++it)
    {
        // calculate surface width
        unsigned int surfaceWidth = 0;
        for(unsigned int i = 0; i != (*it).size(); ++i)
        {
            unsigned char chr = (*it).at(i);

            if (chr == ' ')
            {
                surfaceWidth += _font->spaceWidth();
            }
            else
            {
                surfaceWidth += _font->glyph(chr)->width() + _font->horizontalGap();
                if (i == (*it).size() - 1) surfaceWidth -= _font->horizontalGap();
            }
        }
        if (surfaceWidth > _calculatedWidth) _calculatedWidth = surfaceWidth;
    }

    _calculatedHeight = lines()->size() * _font->height() + (lines()->size() - 1) * _font->verticalGap();
}

TextArea * TextArea::draw()
{
    if (!needRedraw()) return this;
    InteractiveSurface::draw();

    // if no font was setted
    if (!_font) throw Exception("TextArea::draw() - font is not setted");

    // if text is empty
    if (_text == 0 || strlen(_text) == 0) throw Exception("TextArea::draw() - text is 0");


    _calculateSize();
    //convert strings list to surfaces list
    std::vector<Surface *> * surfaces = new std::vector<Surface *>;
    for (std::vector<std::string>::iterator it = lines()->begin(); it != lines()->end(); ++it)
    {
        //create string surface
        surfaces->push_back(new Surface(this->_calculatedWidth, _font->height()));
        //draw characters on string surface
        unsigned int x = 0;
        for(unsigned int i = 0; i != (*it).size(); ++i)
        {
            unsigned char chr = (*it).at(i);
            if (chr == ' ')
            {
                x += _font->spaceWidth();
            }
            else
            {
                Surface * glyph = _font->glyph(chr);
                glyph->x(x)
                     ->y(0)
                     ->copyTo(surfaces->back());
                x += glyph->width() + _font->horizontalGap();
                if (i == (*it).size() - 1) x -= _font->horizontalGap();
            }
        }

    }

    // Creating resulting surface
    Surface * surface = new Surface(this->width(), this->height());
    surface->backgroundColor(backgroundColor())
           ->clear();
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
                x = (this->width() -(*it)->width())/2;
                break;
            case HORIZONTAL_ALIGN_RIGHT:
                x = this->width() - (*it)->width();
                break;
            case HORIZONTAL_ALIGN_JUSTIFY:
                //@todo justify
                break;
        }
        (*it)->x(x);
        (*it)->y(y);
        (*it)->copyTo(surface);
        y += _font->height() + _font->verticalGap();
    }

    surface->x(this->x());
    surface->y(this->y());
    loadFromSurface(surface);

    while(!surfaces->empty())
    {
        delete surfaces->back();
        surfaces->pop_back();
    }
    delete surfaces;
    delete surface;

    needRedraw(false);
    return this;
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
    needRedraw(true);
    return this;
}

unsigned int TextArea::height()
{
    if (_height == 0)
    {
        if (_calculatedHeight == 0) _calculateSize();
        return _calculatedHeight;
    }
    return _height;
}

TextArea * TextArea::setHeight(unsigned int height)
{
    if (height == _height) return this;
    _height = height;
    needRedraw(true);
    return this;
}

unsigned int TextArea::width()
{
    if (_width == 0)
    {
        if (_calculatedWidth == 0) _calculateSize();
        return _calculatedWidth;
    }
    return _width;
}

TextArea * TextArea::setWidth(unsigned int width)
{
    if (_width == width) return this;
    _width = width;
    needRedraw(true);
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
    needRedraw(true);
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
    needRedraw(true);
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
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    delete _lines;
    _lines = 0;
    delete [] _text;
    _text = new char[strlen(text)+1]();
    strcpy(_text, text);
    needRedraw(true);
    return this;
}

TextArea * TextArea::setFont(const char * filename)
{
    delete _font;
    _font = new Font(filename, _color);
    needRedraw(true);
    return this;
}

TextArea * TextArea::setWordWrap(bool wordWrap)
{
    _wordWrap = wordWrap;
    return this;
}

bool TextArea::wordWrap()
{
    return _wordWrap;
}

}
