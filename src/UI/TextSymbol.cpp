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
#include "../UI/TextSymbol.h"

// C++ standard includes

// Falltergeist includes
#include "../Font.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"

// Third party includes
namespace Falltergeist
{

TextSymbol::TextSymbol(const uint8_t chr, const Point& position)
{
    _chr = chr;
    setPosition(position);
}

TextSymbol::TextSymbol(const TextSymbol& other)
{
    _chr = other._chr;
    _position = other._position;
    _font = other._font;
}

TextSymbol::~TextSymbol()
{
}

Font* TextSymbol::font() const
{
    if (!_font)
    {
        return ResourceManager::getInstance()->font();
    }
    return _font;
}

void TextSymbol::setFont(Font* font)
{
    _font = font;
}

Point TextSymbol::position() const
{
    return _position;
}

void TextSymbol::setPosition(const Point& position)
{
    _position = position;
}

void TextSymbol::render(const Point& offset)
{
    unsigned textureX = (chr()%16) * font()->width();
    unsigned textureY = (chr()/16) * font()->height();
    Point drawPos = _position + offset;
    Game::getInstance()->renderer()->drawTexture(font()->texture(), drawPos.x(), drawPos.y(), textureX, textureY, font()->width(), font()->height());
}

uint8_t TextSymbol::chr() const
{
    return _chr;
}

}
