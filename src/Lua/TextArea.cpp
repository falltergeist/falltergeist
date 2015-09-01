/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// Related headers
#include "../Lua/TextArea.h"

// C++ standard includes

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Lua
{

TextArea::TextArea(const std::string& text, int x, int y) : UI::TextArea(text, x, y)
{
}

TextArea::TextArea(int x, int y) : UI::TextArea(x, y)
{
}

TextArea::TextArea(UI::TextArea* textArea, int x, int y) : UI::TextArea(textArea, x, y)
{
}

TextArea::~TextArea()
{
}

unsigned TextArea::luaHorizontalAlign() const
{
    return static_cast<unsigned>(_horizontalAlign);
}

void TextArea::setLuaHorizontalAlign(unsigned align)
{
    if (align > static_cast<unsigned>(HorizontalAlign::JUSTIFY)) return; //@todo Log error

    setHorizontalAlign(static_cast<HorizontalAlign>(align));
}

void TextArea::setWidth(unsigned int width)
{
    TextArea::setWidth(width);
}

unsigned int TextArea::width() const
{
    return TextArea::width();
}

}
}
