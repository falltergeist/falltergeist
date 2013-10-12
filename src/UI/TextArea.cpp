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
#include "../Engine/CrossPlatform.h"

using namespace Falltergeist::CrossPlatform;

namespace Falltergeist
{

TextArea::TextArea(libfalltergeist::MsgMessage * message, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    init();
    setText(message->text());
}

TextArea::TextArea(const char * text, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    init();
    setText(text);
}

TextArea::TextArea(int x, int y) : InteractiveSurface(0, 0, x, y)
{
    init();
}

TextArea::TextArea(std::string text, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    init();
    setText(text);
}

void TextArea::init()
{
    _text = 0;
    _textLines = 0;
    _textSurfaces = 0;
    _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    _verticalAlign = VERTICAL_ALIGN_TOP;
    _width = 0;
    _height = 0;
    _calculatedWidth = 0;
    _calculatedHeight = 0;
    _color = 0xFF3FF800; //Green
    _font = new Font("font1.aaf", _color);
    _wordWrap = false;
    needRedraw(true);
}

TextArea::~TextArea()
{
    delete [] _text;
    delete _textLines;

    if (_textSurfaces != 0)
    {
        while (!_textSurfaces->empty())
        {
            delete _textSurfaces->back();
            _textSurfaces->pop_back();
        }
        delete _textSurfaces;
    }
    delete _font;
}

std::vector<std::string> * TextArea::textLines()
{
    if (_textLines != 0) return _textLines;

    _textLines = new std::vector<std::string>;

    unsigned int stringWidth = 0;
    unsigned int wordWidth = 0;
    std::string word = "";
    _textLines->push_back("");

    for (unsigned int i = 0; i != strlen(_text); ++i)
    {
        unsigned char chr = _text[i];
        if (chr == '\n')
        {
            _textLines->back() += word; // add current word to the last line
            word = "";
            wordWidth = 0;

            _textLines->push_back(""); // add new empty line
            stringWidth = 0;
        }
        else
        {
            word += chr;
            wordWidth += (chr == ' ') ? (_font->spaceWidth()) : (_font->glyph(chr)->width() + _font->horizontalGap());

            // If text area size set and string becomes too long
            if (_width > 0 && (stringWidth + wordWidth >= _width))
            {
                if (_wordWrap)
                {
                    _textLines->push_back(""); //add new empty line
                    stringWidth = 0;
                }
                else
                {
                    _textLines->back() += word;
                    word = "";
                    wordWidth = 0;

                    _textLines->push_back("");
                    stringWidth = 0;
                }
            }
            else
            {
                if (chr == ' ')  // space
                {
                    _textLines->back() += word;
                    stringWidth += wordWidth;
                    word = "";
                    wordWidth = 0;

                }
            }
        }
    }
    if (!word.empty())
    {
        _textLines->back() += word;
    }

    return _textLines;
}

std::vector<Surface *> * TextArea::textSurfaces()
{
    if (_textSurfaces != 0) return _textSurfaces;

    _textSurfaces = new std::vector<Surface *>;

    std::vector<std::string>::iterator it;

    for (it = textLines()->begin(); it != textLines()->end(); ++it)
    {
        unsigned int width = 0;
        for (unsigned int i = 0; i < (*it).length(); i++)
        {
            width += ((*it).c_str()[i] == 0x20) ? (_font->spaceWidth()) : (_font->glyph((*it).c_str()[i])->width() + _font->horizontalGap());
        }
        _textSurfaces->push_back(new Surface(width, _font->height()));
    }

    return _textSurfaces;
}


void TextArea::_calculateSize()
{
    if (_text == 0 || strlen(_text) == 0 || _font == 0) return;

    _calculatedWidth = 0;
    _calculatedHeight = 0;

    // searching for maximum width
    for (std::vector<Surface *>::iterator it = textSurfaces()->begin(); it != textSurfaces()->end(); ++it)
    {
        if ((*it)->width() > _calculatedWidth) _calculatedWidth = (*it)->width();
    }

    _calculatedHeight = textLines()->size() * _font->height() + (textLines()->size() - 1) * _font->verticalGap();
}

TextArea * TextArea::appendText(const char * text)
{
    std::string str;
    str += this->text();
    str += text;
    return setText(str);
}


TextArea * TextArea::appendText(int number)
{
    std::stringstream ss;
    ss << number;
    return appendText(ss.str().c_str());
}

void TextArea::draw()
{
    if (!needRedraw()) return;
    InteractiveSurface::draw();

    if (!_font) throw Exception("TextArea::draw() - font is not setted");

    // if text is empty
    if (_text == 0 || strlen(_text) == 0)
    {
        loadFromSurface(new Surface(0, 0, this->x(), this->y()));
        return;
    }

    unsigned int line = 0;
    for (std::vector<std::string>::iterator it = textLines()->begin(); it != textLines()->end(); ++it)
    {
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
                     ->copyTo(textSurfaces()->at(line));
                x += glyph->width() + _font->horizontalGap();
                if (i == (*it).size() - 1) x -= _font->horizontalGap();
            }
        }
        line++;
    }

    // Creating resulting surface
    Surface * surface = new Surface(this->width(), this->height());
    surface->backgroundColor(backgroundColor())
           ->clear();
    // foreach lines surfaces
    unsigned int x = 0;
    unsigned int y = 0;
    for (std::vector<Surface *>::iterator it = textSurfaces()->begin(); it != textSurfaces()->end(); ++it)
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

    // clear used memory

    while(!_textSurfaces->empty())
    {
        delete _textSurfaces->back();
        _textSurfaces->pop_back();
    }
    delete _textSurfaces; _textSurfaces = 0;
    delete surface;
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
    return setText(message->text());
}

TextArea * TextArea::setText(int number)
{
    std::stringstream ss;
    ss << number;
    return setText(ss.str());
}

TextArea * TextArea::setText(const char * text)
{
    std::string txt(text);
    return setText(txt);
}

TextArea * TextArea::setText(std::string text)
{
    if (_text != 0) // if text not empty
    {
        std::string oldText(_text);
        std::string newText(text);
        if (oldText.compare(newText) == 0) return this; // if text not changed
    }

    _calculatedWidth = 0;
    _calculatedHeight = 0;
    delete _textLines; _textLines = 0;
    if (_textSurfaces != 0)
    {
        while (!_textSurfaces->empty())
        {
            delete _textSurfaces->back();
            _textSurfaces->pop_back();
        }
        delete _textSurfaces; _textSurfaces = 0;
    }
    delete [] _text;
    _text = new char[text.length()+1]();
    strcpy(_text, text.c_str());
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
