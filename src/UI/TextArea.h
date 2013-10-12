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

#ifndef FALLTERGEIST_TEXTAREA_H
#define FALLTERGEIST_TEXTAREA_H

#include "../Engine/InteractiveSurface.h"
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{
class Font;

/**
 * if (!_width && !_height)
 * {
 *     calculate width and height from the text
 * }
 * else
 * {
 *     (if _wordwrap)
 *     {
 *         wrap the whole word
 *     }
 *     else
 *     {
 *         wrap symbols
 *     }
 * }
 */

class TextArea : public InteractiveSurface
{
protected:
    void _init();
    void _calculateSize();
    char * _text;
    std::vector<std::string> * _textLines;
    std::vector<Surface *> * _textSurfaces;
    unsigned char _horizontalAlign;
    unsigned char _verticalAlign;
    unsigned int _width;
    unsigned int _calculatedWidth;
    unsigned int _calculatedHeight;
    unsigned int _height;
    unsigned int _color;
    Font * _font;
    bool _wordWrap;
public:
    enum { HORIZONTAL_ALIGN_LEFT = 0, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT, HORIZONTAL_ALIGN_JUSTIFY };
    enum { VERTICAL_ALIGN_TOP = 0, VERTICAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_JUSTIFY };    
    TextArea(libfalltergeist::MsgMessage * message, int x = 0, int y = 0);
    TextArea(const char * text, int x = 0, int y = 0);
    TextArea(int x = 0, int y = 0);
    TextArea(std::string text, int x = 0, int y = 0);
    ~TextArea();

    void init();

    virtual void draw();

    TextArea * setText(libfalltergeist::MsgMessage * message);
    TextArea * setText(const char * text);
    TextArea * setText(int number);
    TextArea * appendText(const char * text);
    TextArea * appendText(int number);
    TextArea * setText(std::string text);
    char * text();

    std::vector<std::string> * textLines();
    std::vector<Surface *> * textSurfaces();


    TextArea * setHorizontalAlign(unsigned char align);
    unsigned char horizontalAlign();

    TextArea * setVerticalAlign(unsigned char align);
    unsigned char verticalAlign();

    TextArea * setHeight(unsigned int height);
    unsigned int height();

    TextArea * setWidth(unsigned int width);
    unsigned int width();

    TextArea * setColor(unsigned int color);
    unsigned int color();

    TextArea * setWordWrap(bool wordWrap);
    bool wordWrap();

    TextArea * setFont(const char * filename);
};

}
#endif // FALLTERGEIST_TEXTAREA_H
