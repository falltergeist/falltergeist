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
#include "../Point.h"

// Third party includes

namespace Falltergeist
{

class Font;

// TODO: move inside TextArea class? This class is useless elsewhere.
class TextSymbol
{
public:
    TextSymbol(const uint8_t chr, const Point& position);
    TextSymbol(const TextSymbol& other);

    virtual ~TextSymbol();

    Font* font() const;
    void setFont(Font* font);

    Point position() const;
    void setPosition(const Point&);

    void render(const Point& offset);

    uint8_t chr() const;

protected:
    uint8_t _chr;

    Point _position;

    Font* _font;
    
};

}
#endif // FALLTERGEIST_TEXTSYMBOL_H
