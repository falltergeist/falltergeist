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
class FontString;

class TextArea : public ActiveUI
{
protected:
    std::vector<FontString*> _strings;
    void init();
    unsigned char _horizontalAlign = HORIZONTAL_ALIGN_LEFT;
    unsigned char _verticalAlign = VERTICAL_ALIGN_TOP;
    unsigned int _width = 0;
    unsigned int _height = 0;
    unsigned int _backgroundColor = 0;
    bool _wordWrap = false;
    unsigned int _calculateWidth();
public:
    enum { HORIZONTAL_ALIGN_LEFT = 0, HORIZONTAL_ALIGN_CENTER, HORIZONTAL_ALIGN_RIGHT, HORIZONTAL_ALIGN_JUSTIFY };
    enum { VERTICAL_ALIGN_TOP = 0, VERTICAL_ALIGN_CENTER, VERTICAL_ALIGN_BOTTOM, VERTICAL_ALIGN_JUSTIFY };    
    TextArea(libfalltergeist::MsgMessage* message, int x = 0, int y = 0);
    TextArea(std::string text, int x = 0, int y = 0);
    TextArea(int x = 0, int y = 0);
    TextArea(std::shared_ptr<TextArea> textArea, int x = 0, int y = 0);
    ~TextArea();

    TextArea* setBackgroundColor(unsigned int color);
    unsigned int getBackgroundColor();

    TextArea* setText(libfalltergeist::MsgMessage* message);
    TextArea* setText(int number);
    TextArea* setText(std::string text);
    TextArea* appendText(std::string text);
    std::string text();

    TextArea* setHorizontalAlign(unsigned char align);
    unsigned char horizontalAlign();

    TextArea* setVerticalAlign(unsigned char align);
    unsigned char verticalAlign();

    TextArea* setHeight(unsigned int height);
    unsigned int height();

    TextArea* setWidth(unsigned int width);
    unsigned int width();

    TextArea* setWordWrap(bool wordWrap);
    bool wordWrap();

    TextArea* setFont(std::shared_ptr<Font> font);
    std::shared_ptr<Font> font();

    virtual Texture* texture();

};

}
#endif // FALLTERGEIST_TEXTAREA_H
