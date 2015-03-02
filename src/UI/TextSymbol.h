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

#ifndef FALLTERGEIST_TEXTSYMBOL_H
#define FALLTERGEIST_TEXTSYMBOL_H

// C++ standard includes
#include <cstdint>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

class Font;

class TextSymbol
{
protected:
    uint8_t _chr;

    int32_t _x = 0;
    int32_t _y = 0;

    std::shared_ptr<Font> _font;

public:
    TextSymbol(const uint8_t chr, int32_t x = 0, int32_t y = 0);
    TextSymbol(const TextSymbol& other);

    virtual ~TextSymbol();

    std::shared_ptr<Font> font();
    void setFont(std::shared_ptr<Font> font);

    int32_t x();
    void setX(int32_t x);

    int32_t y();
    void setY(int32_t y);

    void render(int32_t offsetX = 0, int32_t offsetY = 0);

    uint8_t chr();

};

}
#endif // FALLTERGEIST_TEXTSYMBOL_H
