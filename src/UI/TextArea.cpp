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
#include <algorithm>
#include <sstream>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../Font.h"
#include "../FontString.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Lua/Script.h"
#include "../ResourceManager.h"
#include "../UI/TextArea.h"
#include "../UI/TextSymbol.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

TextArea::TextArea(int x, int y) : ActiveUI(x, y)
{
    _timestampCreated = SDL_GetTicks();
    _calculate();
}

TextArea::TextArea(const std::string& text, int x, int y) : ActiveUI(x, y)
{
    _timestampCreated = SDL_GetTicks();
    setText(text);
}

TextArea::TextArea(TextArea* textArea, int x, int y) : ActiveUI(x, y)
{
    _timestampCreated = textArea->_timestampCreated;
    _text = textArea->_text;
    _font = textArea->_font;
    _backgroundColor = textArea->_backgroundColor;
    _height = textArea->_height;
    _width = textArea->_width;
    _horizontalAlign = textArea->_horizontalAlign;
    _verticalAlign = textArea->_verticalAlign;
    _wordWrap = textArea->_wordWrap;
    _calculate();
}

TextArea::~TextArea()
{
}

void TextArea::appendText(const std::string& text)
{
    _text += text;
    _changed = true;
    _calculate();
}


TextArea::HorizontalAlign TextArea::horizontalAlign() const
{
    return _horizontalAlign;
}

void TextArea::setHorizontalAlign(HorizontalAlign align)
{
    if (_horizontalAlign == align) return;
    _horizontalAlign = align;
    _changed = true;
    _calculate();
}

TextArea::VerticalAlign TextArea::verticalAlign() const
{
    return _verticalAlign;
}

void TextArea::setVerticalAlign(VerticalAlign align)
{
    if (_verticalAlign == align) return;
    _verticalAlign = align;
    _changed = true;
    _calculate();
}

void TextArea::setText(const std::string& text)
{
    _text = text;
    _changed = true;
    _calculate();
}

std::shared_ptr<Font> TextArea::font()
{
    if (!_font)
    {
        return ResourceManager::getInstance()->font();
    }
    return _font;
}

void TextArea::setFont(std::shared_ptr<Font> font)
{
    _font = font;
    _changed = true;
    _calculate();
}

void TextArea::setWordWrap(bool wordWrap)
{
    if (_wordWrap == wordWrap) return;
    _wordWrap = wordWrap;
    _changed = true;
    _calculate();
}

bool TextArea::wordWrap() const
{
    return _wordWrap;
}


void TextArea::setWidth(unsigned int width)
{
    if (_width == width) return;
    _width = width;
    _changed = true;
    _calculate();
}

unsigned int TextArea::width() const
{
    if (_width == 0)
    {
        return _calculatedWidth;
    }
    return _width;
}

void TextArea::setHeight(unsigned int height)
{
    if (_height == height) return;
    _height = height;
    _changed = true;
    _calculate();
}

unsigned int TextArea::height() const
{
    if (_height == 0)
    {
        return _calculatedHeight;
    }
    return _width;
}

void TextArea::_calculate()
{
    if (!_changed) return;

    _symbols.clear();

    if (_text.empty())
    {
        _changed = false;
        return;
    }

    unsigned x = 0;
    unsigned y = 0;

    std::vector<std::vector<TextSymbol>> lines = {std::vector<TextSymbol>()};
    std::vector<unsigned> widths = {0};

    // Parsing lines of text
    // Cutting lines when it is needed (\n or when exceeding _width)
    for (auto it = _text.begin(); it != _text.end(); ++it)
    {
        if (*it == ' ')
        {
            x += font()->aaf()->spaceWidth() + font()->horizontalGap();
        }

        if (*it == '\n' || (_width && x >= _width))
        {
            widths.back() = x;
            x = 0;
            y += font()->height() + font()->verticalGap();
            lines.push_back(std::vector<TextSymbol>());
            widths.push_back(0);
        }

        if (*it == ' ' || *it == '\n') continue;


        TextSymbol symbol(*it, x, y);
        symbol.setFont(font());
        lines.back().push_back(symbol);

        x += font()->aaf()->glyphs()->at(symbol.chr())->width() + font()->horizontalGap();
        widths.back() = x;
    }

    // Calculating textarea sizes if needed
    if (_width == 0)
    {
        _calculatedWidth = *std::max_element(widths.begin(), widths.end());
    }
    if (_height == 0)
    {
        _calculatedHeight = lines.size()*font()->height() + (lines.size() - 1)*font()->verticalGap();
    }

    // Align
    for (unsigned i = 0; i != lines.size(); ++i)
    {
        auto& line = lines.at(i);

        unsigned xOffset = 0;
        unsigned yOffset = 0;

        if (_horizontalAlign != HorizontalAlign::LEFT)
        {
            xOffset = (_width ? _width : _calculatedWidth) - widths.at(i);
            if(_horizontalAlign == HorizontalAlign::CENTER)
            {
                xOffset =  xOffset / 2;
            }
        }

        for (auto& symbol : line)
        {
            symbol.setX(symbol.x() + xOffset);
            symbol.setY(symbol.y() + yOffset);
            _symbols.push_back(symbol);
        }
    }
    _changed = false;
}

std::string TextArea::text() const
{
    return _text;
}

unsigned int TextArea::timestampCreated()
{
    return _timestampCreated;
}

void TextArea::render(bool eggTransparency)
{
    if (_changed) _calculate();

    for (auto& symbol : _symbols)
    {
        symbol.render(x(), y());
    }
}

TextArea& TextArea::operator<<(const std::string& text)
{
    appendText(text);
    return *this;
}

TextArea& TextArea::operator<<(unsigned value)
{
    appendText(std::to_string(value));
    return *this;
}

TextArea& TextArea::operator<<(signed value)
{
    appendText(std::to_string(value));
    return *this;
}

TextArea& TextArea::operator=(const std::string& text)
{
    setText(text);
    return *this;
}

TextArea& TextArea::operator=(unsigned value)
{
    setText(std::to_string(value));
    return *this;
}

TextArea& TextArea::operator=(signed value)
{
    setText(std::to_string(value));
    return *this;
}

TextArea& TextArea::operator+=(const std::string& text)
{
    appendText(text);
    return *this;
}

TextArea& TextArea::operator+=(unsigned value)
{
    appendText(std::to_string(value));
    return *this;
}

TextArea& TextArea::operator+=(signed value)
{
    appendText(std::to_string(value));
    return *this;
}

unsigned int TextArea::pixel(unsigned int x, unsigned int y)
{
    if ( x >= width() || y >= height())
    {
        return 0; // transparent
    }

    return 0xFFFFFFFF; // white color
}

void TextArea::export_to_lua_script(Lua::Script* script)
{
    luabridge::getGlobalNamespace(script->luaState())
        .beginNamespace("game")
            .beginNamespace("ui")
                .deriveClass<TextArea, ActiveUI>("TextArea")
                    .addConstructor<void(*)(const char*, int, int)>()
                    .addProperty("width", &TextArea::width, &TextArea::setWidth)
                    .addProperty("horizontalAlign", &TextArea::horizontalAlign, &TextArea::setHorizontalAlign)
                .endClass()
            .endNamespace()
        .endNamespace();
}

}

