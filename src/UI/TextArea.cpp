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
}

TextArea::TextArea(std::string text, int x, int y) : ActiveUI(x, y)
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
}

TextArea::~TextArea()
{
}

TextArea* TextArea::appendText(std::string text)
{
    _text += text;
    _changed = true;
    return this;
}


unsigned char TextArea::horizontalAlign()
{
    return _horizontalAlign;
}

TextArea * TextArea::setHorizontalAlign(unsigned char align)
{
    if (_horizontalAlign == align) return this;
    _horizontalAlign = align;
    _changed = true;
    return this;
}

unsigned char TextArea::verticalAlign()
{
    return _verticalAlign;
}

TextArea * TextArea::setVerticalAlign(unsigned char align)
{
    if (_verticalAlign == align) return this;
    _verticalAlign = align;
    _changed = true;
    return this;
}

TextArea * TextArea::setText(std::string text)
{
    _text = text;
    _changed = true;
    return this;
}

std::shared_ptr<Font> TextArea::font()
{
    if (!_font)
    {
        return ResourceManager::font();
    }
    return _font;
}

TextArea * TextArea::setFont(std::shared_ptr<Font> font)
{
    _font = font;
    _changed = true;
    return this;
}

TextArea * TextArea::setWordWrap(bool wordWrap)
{
    if (_wordWrap == wordWrap) return this;
    _wordWrap = wordWrap;
    _changed = true;
    return this;
}

bool TextArea::wordWrap()
{
    return _wordWrap;
}

TextArea* TextArea::setOutline(bool outline)
{
    _outline = outline;
    return this;
}

bool TextArea::outline()
{
    return _outline;
}

TextArea* TextArea::setOutlineColor(unsigned int color)
{
    _outlineColor = color;
    return this;
}

unsigned int TextArea::outlineColor()
{
    return _outlineColor;
}

TextArea* TextArea::setWidth(unsigned int width)
{
    if (_width == width)
    {
        return this;
    }
    _width = width;
    _changed = true;
    return this;
}

unsigned int TextArea::width()
{
    if (_width == 0)
    {
        if (_calculatedWidth == 0)
        {
            _calculate();
        }
        return _calculatedWidth;
    }
    return _width;
}

TextArea* TextArea::setHeight(unsigned int height)
{
    if (_height == height) return this;
    _height = height;
    _changed = true;
    return this;
}

unsigned int TextArea::height()
{
    if (_height == 0)
    {
        if (_calculatedHeight == 0)
        {
            _calculate();
        }
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

        if (_horizontalAlign != HORIZONTAL_ALIGN_LEFT)
        {
            xOffset = (_width ? _width : _calculatedWidth) - widths.at(i);
            if(_horizontalAlign == HORIZONTAL_ALIGN_CENTER)
            {
                xOffset =  xOffset / 2;
            }
        }

        for (auto& symbol : line)
        {
            symbol.setX(symbol.x() + xOffset);
            symbol.setY(symbol.y() + yOffset);
            //outline symbols
            if(_outline)
            {
                std::shared_ptr<Font> outlineFont = ResourceManager::font(symbol.font()->filename(), _outlineColor);
                
                auto outlineSymbolLeft = new TextSymbol(symbol.chr(), symbol.x()-1, symbol.y());
                auto outlineSymbolTopLeft = new TextSymbol(symbol.chr(), symbol.x()-1, symbol.y()-1);
                auto outlineSymbolBottomLeft = new TextSymbol(symbol.chr(), symbol.x()-1, symbol.y()+1);
                auto outlineSymbolRight = new TextSymbol(symbol.chr(), symbol.x()+1, symbol.y());
                auto outlineSymbolTopRight = new TextSymbol(symbol.chr(), symbol.x()+1, symbol.y()-1);
                auto outlineSymbolBottomRight = new TextSymbol(symbol.chr(), symbol.x()+1, symbol.y()+1);
                auto outlineSymbolBottom = new TextSymbol(symbol.chr(), symbol.x(), symbol.y()-1);
                auto outlineSymbolTop = new TextSymbol(symbol.chr(), symbol.x(), symbol.y()+1);
                
                outlineSymbolLeft->setFont(outlineFont);
                outlineSymbolTopLeft->setFont(outlineFont);
                outlineSymbolBottomLeft->setFont(outlineFont);
                outlineSymbolRight->setFont(outlineFont);
                outlineSymbolTopRight->setFont(outlineFont);
                outlineSymbolBottomRight->setFont(outlineFont);
                outlineSymbolBottom->setFont(outlineFont);
                outlineSymbolTop->setFont(outlineFont);
                
                _symbols.push_back(*outlineSymbolLeft);
                _symbols.push_back(*outlineSymbolTopLeft);
                _symbols.push_back(*outlineSymbolBottomLeft);
                _symbols.push_back(*outlineSymbolRight);
                _symbols.push_back(*outlineSymbolTopRight);
                _symbols.push_back(*outlineSymbolBottomRight);
                _symbols.push_back(*outlineSymbolBottom);
                _symbols.push_back(*outlineSymbolTop);
            }
        
            _symbols.push_back(symbol);
        }
    }
    _changed = false;
}

std::string TextArea::text()
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

}

