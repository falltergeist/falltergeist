/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_FONTSTRING_H
#define FALLTERGEIST_FONTSTRING_H

// C++ standard includes
#include <string>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class Font;

class FontString
{
public:
    FontString(const std::string& text, Font* font = nullptr);
    Font* font() const;
    FontString* setFont(Font* font);
    std::string text() const;
    FontString* setText(const std::string& text);

protected:
    std::string _text;
    Font* _font;
};

}
#endif // FALLTERGEIST_FONTSTRING_H
