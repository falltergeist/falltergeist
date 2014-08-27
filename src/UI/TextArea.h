/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// C++ standard includes
#include <string>
#include <vector>

// Falltergeist includes
#include "../Engine/ActiveUI.h"

// Third party includes
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{
class Font;

class TextArea : public ActiveUI
{
protected:
    void _init();
    void _calculateSize();
    std::string _text;
    std::vector<std::string>* _textLines = 0;
    unsigned char _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    unsigned char _verticalAlign = VERTICAL_ALIGN_TOP;
    int _width = 0;
    int _height = 0;
    int _calculatedWidth = 0;
    int _calculatedHeight = 0;
    unsigned int _color = 0x3FF800FF;
    Font* _font = 0;
    bool _wordWrap = false;
public:
    enum { HORIZONTAL_ALIGN_LEFT = 0, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT, HORIZONTAL_ALIGN_JUSTIFY };
    enum { VERTICAL_ALIGN_TOP = 0, VERTICAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_JUSTIFY };    
    TextArea(libfalltergeist::MsgMessage* message, int x = 0, int y = 0);
    TextArea(std::string text, int x = 0, int y = 0);
    TextArea(int x = 0, int y = 0);
    TextArea(TextArea* textArea, int x = 0, int y = 0);
    ~TextArea();

    void init();

    void setBackgroundColor(unsigned int color);

    TextArea* setText(libfalltergeist::MsgMessage* message);
    TextArea* setText(int number);
    TextArea* setText(std::string text);
    TextArea* appendText(std::string text);
    TextArea* appendText(int number);
    std::string text();

    std::vector<std::string>* textLines();
    //std::vector<Surface*>* textSurfaces();


    TextArea* setHorizontalAlign(unsigned char align);
    unsigned char horizontalAlign();

    TextArea* setVerticalAlign(unsigned char align);
    unsigned char verticalAlign();

    TextArea* setHeight(int height);
    int height();

    TextArea* setWidth(int width);
    int width();

    TextArea* setColor(unsigned int color);
    unsigned int color();

    TextArea* setWordWrap(bool wordWrap);
    bool wordWrap();

    TextArea* setFont(std::string filename);
    Font* font();    

    virtual Texture* texture();

};

}
#endif // FALLTERGEIST_TEXTAREA_H
