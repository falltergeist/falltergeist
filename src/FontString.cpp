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

// C++ standard includes

// Falltergeist includes
#include "FontString.h"
#include "Font.h"
#include "ResourceManager.h"

// Third party includes

namespace Falltergeist
{

FontString::FontString(std::string text, std::shared_ptr<Font> font)
{
    _text = text;

    if (!font)
    {
        font = ResourceManager::font();
    }
    _font = font;
}

std::shared_ptr<Font> FontString::font()
{
    return _font;
}

FontString* FontString::setFont(std::shared_ptr<Font> font)
{
    _font = font;
    return this;
}

std::string FontString::text()
{
    return _text;
}

FontString* FontString::setText(std::string text)
{
    _text = text;
    return this;
}

}
