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
#include "../UI/TextArea.h"

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
#include "../UI/TextSymbol.h"

// Third party includes
#include <SDL.h>

using namespace std;

namespace Falltergeist
{
namespace UI
{

TextArea::TextArea(const Point& pos) : Base(pos)
{
    _timestampCreated = SDL_GetTicks();
}

TextArea::TextArea(int x, int y) : TextArea(Point(x, y))
{
}

TextArea::TextArea(const string& text, const Point& pos) : Base(pos)
{
    _timestampCreated = SDL_GetTicks();
    setText(text);
}

TextArea::TextArea(const string& text, int x, int y) : TextArea(text, Point(x, y))
{
}

TextArea::TextArea(const TextArea& textArea, Point pos) : Base(pos)
{
    _timestampCreated = textArea._timestampCreated;
    _text = textArea._text;
    _font = textArea._font;
    _backgroundColor = textArea._backgroundColor;
    _size = textArea._size;
    _horizontalAlign = textArea._horizontalAlign;
    _verticalAlign = textArea._verticalAlign;
    _wordWrap = textArea._wordWrap;
}

TextArea::~TextArea()
{
}

void TextArea::appendText(const string& text)
{
    _text += text;
    _changed = true;
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
}

void TextArea::setText(const string& text)
{
    _text = text;
    _changed = true;
}

Font* TextArea::font()
{
    if (!_font)
    {
        _font = ResourceManager::getInstance()->font();
    }
    return _font;
}

void TextArea::setFont(Font* font)
{
    _font = font;
    _changed = true;
}

void TextArea::setWordWrap(bool wordWrap)
{
    if (_wordWrap == wordWrap) return;
    _wordWrap = wordWrap;
    _changed = true;
}

bool TextArea::wordWrap() const
{
    return _wordWrap;
}

void TextArea::setOutline(bool outline)
{
    _outline = outline;
}

bool TextArea::outline() const
{
    return _outline;
}

void TextArea::setOutlineColor(unsigned int color)
{
    _outlineColor = color;
}

unsigned int TextArea::outlineColor() const
{
    return _outlineColor;
}

Size TextArea::size() const
{
    return Size(
        _size.width() ?: _calculatedSize.width(),
        _size.height() ?: _calculatedSize.height()
    );
}

void TextArea::calculateSize()
{
    _calculate();
}

void TextArea::setSize(const Size& size)
{
    if (_size == size) return;
    _size = size;
    _changed = true;
}

void TextArea::setWidth(int width)
{
    setSize({width, _size.height()});
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

    unsigned x = 0, wordWidth = 0;
    unsigned y = 0;

    vector<vector<TextSymbol>> lines = {vector<TextSymbol>()};
    vector<unsigned> widths = {0};

    // Parsing lines of text
    // Cutting lines when it is needed (\n or when exceeding _width)
    istringstream istream(_text);
    string word;
    auto aFont = font();
    auto glyphs = aFont->aaf()->glyphs();
    while (istream >> word)
    {
        // calculate word width
        wordWidth = 0;
        for (unsigned char ch : word)
        {
            wordWidth += glyphs->at(ch)->width() + aFont->horizontalGap();
        }
        // switch to next line if word is too long
        if (_size.width() && _wordWrap && (x + wordWidth) > (unsigned)_size.width())
        {
            word = '\n' + word;
        }
        // include whitespaces
        while (!istream.eof() && isspace((int)istream.peek()))
        {
            word.push_back((char)istream.get());
        }
        // place the word
        for (unsigned char ch : word)
        {
            if (ch == ' ')
            {
                x += aFont->aaf()->spaceWidth() + aFont->horizontalGap();
            }

            if (ch == '\n' || (_size.width() && x >= (unsigned)_size.width()))
            {
                widths.back() = x;
                x = 0;
                y += aFont->height() + aFont->verticalGap();
                lines.emplace_back();
                widths.push_back(0);
            }

            if (ch == ' ' || ch == '\n')
                continue;

            TextSymbol symbol(ch, x, y);
            symbol.setFont(aFont);
            lines.back().push_back(symbol);

            x += glyphs->at(ch)->width() + aFont->horizontalGap();
            widths.back() = x;
        }
    }

    // Calculating textarea sizes if needed
    _calculatedSize = _size;
    if (_size.width() == 0)
    {
        _calculatedSize.setWidth(*std::max_element(widths.begin(), widths.end()));
    }
    if (_size.height() == 0)
    {
        _calculatedSize.setHeight(lines.size()*font()->height() + (lines.size() - 1)*font()->verticalGap());
    }

    // Align
    for (unsigned i = 0; i != lines.size(); ++i)
    {
        auto& line = lines.at(i);

        unsigned xOffset = 0;
        unsigned yOffset = 0;

        if (_horizontalAlign != HorizontalAlign::LEFT)
        {
            xOffset = (_size.width() ? _size.width() : _calculatedSize.width()) - widths.at(i);
            if(_horizontalAlign == HorizontalAlign::CENTER)
            {
                xOffset =  xOffset / 2;
            }
        }

        for (auto& symbol : line)
        {
            symbol.setX(symbol.x() + xOffset);
            symbol.setY(symbol.y() + yOffset);
            // outline symbols
            if (_outline)
            {
                auto outlineFont = ResourceManager::getInstance()->font(symbol.font()->filename(), _outlineColor);

                _addOutlineSymbol(symbol, outlineFont,  0, -1);
                _addOutlineSymbol(symbol, outlineFont,  0,  1);
                _addOutlineSymbol(symbol, outlineFont, -1,  0);
                _addOutlineSymbol(symbol, outlineFont, -1, -1);
                _addOutlineSymbol(symbol, outlineFont, -1,  1);
                _addOutlineSymbol(symbol, outlineFont,  1,  0);
                _addOutlineSymbol(symbol, outlineFont,  1, -1);
                _addOutlineSymbol(symbol, outlineFont,  1,  1);
            }
        
            _symbols.push_back(symbol);
        }
    }
    _changed = false;
}

void TextArea::_addOutlineSymbol(const TextSymbol& symb, Font* font, int32_t ofsX, int32_t ofsY)
{
    _symbols.emplace_back(symb.chr(), symb.x() + ofsX, symb.y() + ofsY);
    _symbols.back().setFont(font);
}

string TextArea::text() const
{
    return _text;
}

unsigned int TextArea::timestampCreated() const
{
    return _timestampCreated;
}

void TextArea::render(bool eggTransparency)
{
    if (_changed) _calculate();

    for (auto& symbol : _symbols)
    {
        auto pos = position();
        symbol.render(pos.x(), pos.y());
    }
}

TextArea& TextArea::operator<<(const string& text)
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

TextArea& TextArea::operator=(const string& text)
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

TextArea& TextArea::operator+=(const string& text)
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

unsigned int TextArea::pixel(const Point& pos)
{
    if (!Rect::inRect(pos, this->size()))
    {
        return 0; // transparent
    }
    return 0xFFFFFFFF; // white color
}

}
}
