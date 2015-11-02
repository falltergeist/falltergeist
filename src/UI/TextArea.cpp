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
#include "../Event/Mouse.h"
#include "../Font.h"
#include "../FontString.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../Logger.h"

// Third party includes
#include <SDL.h>

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

TextArea::TextArea(const std::string& text, const Point& pos) : Base(pos)
{
    _timestampCreated = SDL_GetTicks();
    setText(text);
}

TextArea::TextArea(const std::string& text, int x, int y) : TextArea(text, Point(x, y))
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

void TextArea::_needUpdate(bool lines)
{
    _changed = true;
    if (lines)
    {
        _lines.clear();
    }
}

void TextArea::appendText(const std::string& text)
{
    _text += text;
    _needUpdate(true);
}

TextArea::HorizontalAlign TextArea::horizontalAlign() const
{
    return _horizontalAlign;
}

void TextArea::setHorizontalAlign(HorizontalAlign align)
{
    if (_horizontalAlign == align) return;
    _horizontalAlign = align;
    _needUpdate();
}

TextArea::VerticalAlign TextArea::verticalAlign() const
{
    return _verticalAlign;
}

void TextArea::setVerticalAlign(VerticalAlign align)
{
    if (_verticalAlign == align) return;
    _verticalAlign = align;
    _needUpdate();
}

void TextArea::setText(const std::string& text)
{
    _text = text;
    _needUpdate(true);
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
    _needUpdate(true);
}

void TextArea::setFont(const std::string& fontName, unsigned int color)
{
    setFont(ResourceManager::getInstance()->font(fontName, color));
}

std::string TextArea::fontName()
{
    return font()->filename();
}

void TextArea::setWordWrap(bool wordWrap)
{
    if (_wordWrap == wordWrap) return;
    _wordWrap = wordWrap;
    _needUpdate(true);
}

bool TextArea::wordWrap() const
{
    return _wordWrap;
}

void TextArea::setOutline(bool outline)
{
    _outlineColor = outline ? 0x000000ff : 0;
}

bool TextArea::outline() const
{
    return _outlineColor != 0;
}

void TextArea::setOutlineColor(unsigned int color)
{
    _outlineColor = color;
    _needUpdate();
}

unsigned int TextArea::outlineColor() const
{
    return _outlineColor;
}

int TextArea::lineOffset() const
{
    return _lineOffset;
}

void TextArea::setLineOffset(int offset)
{
    _lineOffset = offset;
    _needUpdate();
}

Size TextArea::size() const
{
    return Size(
        _size.width() ?: _calculatedSize.width(),
        _size.height() ?: _calculatedSize.height()
    );
}

Size TextArea::textSize()
{
    _updateSymbols();
    return _calculatedSize;
}

int TextArea::numLines()
{
    _updateLines();
    return _lines.size();
}

void TextArea::setSize(const Size& size)
{
    if (_size == size) return;
    // width affect line composition, so we need full update
    _needUpdate(_size.width() != size.width());
    _size = size;
}

void TextArea::setWidth(int width)
{
    setSize({width, _size.height()});
}

// TODO: anyone is welcome to do this better..
void TextArea::_updateSymbols()
{
    if (!_changed) return;

    _symbols.clear();

    if (_text.empty())
    {
        _changed = false;
        return;
    }

    _updateLines();

    // at positive offset, skip number of first lines
    auto lineBegin = std::min(
        _lines.cbegin() + (_lineOffset > 0 ? _lineOffset : 0),
        _lines.cend()
    );
    auto lineEnd = _lines.cend();
    if (_size.height())
    {
        // calculate how much lines we can fit inside TextArea, taking vertical padding into account
        auto activeHeight = _size.height() - _paddingTopLeft.height() - _paddingBottomRight.height();
        lineEnd = std::max(
            std::min(
                _lines.cbegin() + _lineOffset + ((activeHeight + font()->verticalGap()) / (font()->height() + font()->verticalGap())),
                _lines.cend()
            ),
            _lines.cbegin()
        );
    }

    int numVisibleLines = std::distance(lineBegin, lineEnd);

    // Calculating textarea sizes if needed
    if (numVisibleLines > 0)
    {
        _calculatedSize.setWidth(std::max_element(lineBegin, lineEnd)->width);
        _calculatedSize.setHeight(numVisibleLines * font()->height() + (numVisibleLines - 1) * font()->verticalGap());
    }
    else
    {
        _calculatedSize = Size(0, 0);
    }

    // Alignment and outlining
    auto outlineFont = (_outlineColor != 0)
                       ? ResourceManager::getInstance()->font(font()->filename(), _outlineColor)
                       : nullptr;

    Point offset;
    // lines are generated with respect to horizontal padding only, so we should only change vertical;
    // on negative offset, add padding at the top, on positive - shift lines upwards
    offset.setY(_paddingTopLeft.height() + (font()->height() + font()->verticalGap()) * (- _lineOffset));
    // index of visible line
    size_t lineIdx = _lineOffset < 0 ? (size_t)(- _lineOffset) : 0;
    for (auto it = lineBegin; it != lineEnd; ++it, ++lineIdx)
    {
        auto& line = *it;
        offset.setX(0);
        if (_horizontalAlign != HorizontalAlign::LEFT)
        {
            offset.setX((_size.width() ? _size.width() : _calculatedSize.width()) - line.width);
            if (_horizontalAlign == HorizontalAlign::CENTER)
            {
                offset.rx() /= 2;
            }
        }
        if (lineIdx < _customLineShifts.size())
        {
            offset.rx() += _customLineShifts[lineIdx];
        }

        for (TextSymbol symbol : line.symbols)
        {
            symbol.position += offset;
            // outline symbols
            if (_outlineColor != 0)
            {
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

void TextArea::_updateLines()
{
    // check if already generated
    if (!_lines.empty()) return;

    _lines.resize(1);

    // here we respect only horizontal padding in order to properly wrap lines; vertical is handled on higher level
    int x = _paddingTopLeft.width(),
        y = 0,
        wordWidth = 0,
        maxWidth = _size.width() ? (_size.width() - _paddingBottomRight.width()) : 0;
    
    // Parsing lines of text
    // Cutting lines when it is needed (\n or when exceeding _width)
    std::istringstream istream(_text);
    std::string word, part;
    auto aFont = font();
    auto glyphs = aFont->aaf()->glyphs();

    // on first iteation, process only leading whitespaces
    while (!istream.eof() && isspace((int)istream.peek()))
    {
        part.push_back((char)istream.get());
    }
    do
    {
        if (word.size() > 0)
        {
            // calculate word width
            wordWidth = 0;
            for (unsigned char ch : word)
            {
                wordWidth += glyphs->at(ch)->width() + aFont->horizontalGap();
            }
            // switch to next line if word is too long
            if (_wordWrap && maxWidth && (x + wordWidth) > maxWidth)
            {
                part.push_back('\n');
            }
            part += word;
            // include trailing whitespaces
            while (!istream.eof() && isspace((int)istream.peek()))
            {
                part.push_back((char)istream.get());
            }
        }
        // place the part
        for (unsigned char ch : part)
        {
            if (ch == ' ')
            {
                x += aFont->aaf()->spaceWidth() + aFont->horizontalGap();
            }

            if (ch == '\n' || (_wordWrap && maxWidth && x >= maxWidth))
            {
                _lines.back().width = x;
                x = 0;
                y += aFont->height() + aFont->verticalGap();
                _lines.emplace_back();
            }

            if (ch == ' ' || ch == '\n')
                continue;

            Line& line = _lines.back();
            TextSymbol symbol {ch, {x, y}, aFont};
            line.symbols.push_back(symbol);
            x += glyphs->at(ch)->width() + aFont->horizontalGap();
            line.width = x;
        }
        part.clear();

    } while (istream >> word);
}

void TextArea::_addOutlineSymbol(const TextSymbol& symb, Font* font, int32_t ofsX, int32_t ofsY)
{
    _symbols.emplace_back(TextSymbol {symb.chr, symb.position + Point(ofsX, ofsY), font});
}

std::string TextArea::text() const
{
    return _text;
}

unsigned int TextArea::timestampCreated() const
{
    return _timestampCreated;
}

void TextArea::render(bool eggTransparency)
{
    if (_changed)
    {
        _updateSymbols();
    }

    auto pos = position();
    auto renderer = Game::getInstance()->renderer();

    for (auto& symbol : _symbols)
    {
        auto aFont = symbol.font ?: font();
        unsigned textureX = (symbol.chr%16) * aFont->width();
        unsigned textureY = (symbol.chr/16) * aFont->height();
        Point drawPos = symbol.position + pos;
        renderer->drawTexture(aFont->texture(), drawPos.x(), drawPos.y(), textureX, textureY, aFont->width(), aFont->height());
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

unsigned int TextArea::pixel(const Point& pos)
{
    if (!Rect::inRect(pos, this->size()))
    {
        return 0; // transparent
    }
    return 0xFFFFFFFF; // white color
}

void TextArea::handle(Event::Event* event)
{
    Base::handle(event);
    if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
    {
        mouseEvent->setHandled(false);
        mouseEvent->setObstacle(false);
    }
}

const Size& TextArea::paddingTopLeft() const
{
    return _paddingTopLeft;
}

void TextArea::setPaddingTopLeft(const Size& pad)
{
    _needUpdate(_paddingTopLeft.width() != pad.width());
    _paddingTopLeft = pad;
}

const Size& TextArea::paddingBottomRight() const
{
    return _paddingBottomRight;
}

void TextArea::setPaddingBottomRight(const Size& pad)
{
    _needUpdate(_paddingBottomRight.width() != pad.width());
    _paddingBottomRight = pad;
}

void TextArea::setPadding(const Size& topLeft, const Size& bottomRight)
{
    setPaddingTopLeft(topLeft);
    setPaddingBottomRight(bottomRight);
}

const std::vector<int>& TextArea::customLineShifts() const
{
    return _customLineShifts;
}

void TextArea::setCustomLineShifts(std::vector<int> shifts)
{
    _customLineShifts = shifts;
}

}
}
