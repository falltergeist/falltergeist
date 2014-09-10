/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include <sstream>
#include <iostream>

// Falltergeist includes
#include "../Engine/Font.h"
#include "../Engine/FontString.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/CrossPlatform.h"
#include "../UI/TextArea.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

TextArea::TextArea(libfalltergeist::MsgMessage* message, int x, int y) : ActiveUI(x, y)
{
    init();
    setText(message->text());
}

TextArea::TextArea(int x, int y) : ActiveUI(x, y)
{
    init();
}

TextArea::TextArea(std::string text, int x, int y) : ActiveUI(x, y)
{
    init();
    setText(text);
}

TextArea::TextArea(TextArea* textArea, int x, int y) : ActiveUI(x, y)
{
    init();
    setFont(textArea->_strings.back()->font());
    setBackgroundColor(textArea->_backgroundColor);
    setHeight(textArea->_height);
    setWidth(textArea->_width);
    setHorizontalAlign(textArea->_horizontalAlign);
    setVerticalAlign(textArea->_verticalAlign);
    setWordWrap(textArea->_wordWrap);
}

TextArea::~TextArea()
{
}

void TextArea::init()
{
    _strings.push_back(new FontString(""));
}


TextArea* TextArea::appendText(std::string text)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _strings.back()->setText(_strings.back()->text() + text);
    return this;
}


unsigned char TextArea::horizontalAlign()
{
    return _horizontalAlign;
}

TextArea * TextArea::setHorizontalAlign(unsigned char align)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _horizontalAlign = align;
    return this;
}

unsigned char TextArea::verticalAlign()
{
    return _verticalAlign;
}

TextArea * TextArea::setVerticalAlign(unsigned char align)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _verticalAlign = align;
    return this;
}

TextArea* TextArea::setText(libfalltergeist::MsgMessage* message)
{
    return setText(message->text());
}

TextArea * TextArea::setText(int number)
{
    std::stringstream ss;
    ss << number;
    return setText(ss.str());
}

TextArea * TextArea::setText(std::string text)
{
    if (_strings.size() == 1)
    {
        if (_strings.back()->text() == text) return this;
    }

    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    auto font = _strings.back()->font();
    while (!_strings.empty())
    {
        delete _strings.back();
        _strings.pop_back();
    }
    _strings.clear();
    _strings.push_back(new FontString(text, font));
    return this;
}

TextArea * TextArea::setFont(std::shared_ptr<Font> font)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    for (auto it = _strings.begin(); it != _strings.end(); it++)
    {
        (*it)->setFont(font);
    }
    return this;
}

TextArea * TextArea::setWordWrap(bool wordWrap)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _wordWrap = wordWrap;
    return this;
}

bool TextArea::wordWrap()
{
    return _wordWrap;
}

TextArea* TextArea::setBackgroundColor(unsigned int color)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _backgroundColor = color;
    return this;
}

TextArea* TextArea::setWidth(unsigned int width)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _width = width;
    return this;
}

unsigned int TextArea::width()
{
    if (_width == 0) return _calculateWidth();
    return _width;
}

TextArea* TextArea::setHeight(unsigned int height)
{
    if (_texture)
    {
        delete _texture;
        _texture = 0;
    }
    _height = height;
    return this;
}

unsigned int TextArea::height()
{
    if (_height == 0) return _calculateHeight();
    return _height;
}

Texture* TextArea::texture()
{
    if (_texture) return _texture;

    _texture = new Texture(width(), height());
    _texture->fill(_backgroundColor);

    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int str_width_max = 0;
    unsigned int width_final = 0;
    unsigned int wrd_width = 0;
    unsigned int horizontal_word_gap;
    unsigned int horizontal_error;
    unsigned int space_width = 0; // width of space symbol with a gap

    std::vector<FontString*> _strings_tmp;
    std::string text_new;
    std::string wrd;
    _strings_tmp.push_back(new FontString(""));
    _strings_tmp.clear();

    // Building _strings_tmp -- lines of text
    // It'll be exact as it seen on the screen
    // Cutting lines when it needed (\n or when exceeding width)
    for (auto it = _strings.begin(); it != _strings.end(); ++it)
    {
        auto font = (*it)->font();
        std::string text = (*it)->text();
        text_new = "";
        wrd = "";
        wrd_width = 0;
        libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(' ');
        space_width = glyph->width() + font->horizontalGap();

        for (auto itt = text.begin(); itt != text.end(); ++itt)
        {
            auto chr = *itt;
            libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(chr);

            // adding word to string or char to word
            if ((chr == ' ') || (chr == '\n'))
            {
                if (text_new != "")
                    text_new += " ";
                text_new += wrd;
                wrd = "";
                wrd_width = 0;
                x += wrd_width;
                x += space_width;
            }
            else
            {
                wrd += chr;
                wrd_width += glyph->width() + font->horizontalGap();
                x += glyph->width() + font->horizontalGap();
            }

            // if wrap or new line
            if ((chr == '\n')||(_wordWrap == true && x + glyph->width() >= width()))
            {
                if (chr == '\n')
                    x = 0;
                else
                {
                    x = wrd_width;
                    wrd_width = 0;
                }
                _strings_tmp.push_back(new FontString(text_new, font));
                text_new = "";
                continue;
            }
        }

        // adding last word to string
        if (wrd != "")
        {
            if (text_new != "")
                text_new += " ";
            text_new += wrd;
        }

        // adding line of text if there is any
        if (text_new != "")
        {
            _strings_tmp.push_back(new FontString(text_new, font));
        }
    }

    // calculating max width of strings if needed
    if ((width() == 0) && (_horizontalAlign != HORIZONTAL_ALIGN_LEFT))
    {
        unsigned int str_width;
        str_width_max = 0;
        for (auto it = _strings_tmp.begin(); it != _strings_tmp.end(); ++it)
        {
            auto font = (*it)->font();
            std::string text = (*it)->text();
            // calculating width of current string
            str_width = 0;
            for (auto itt = text.begin(); itt != text.end(); ++itt)
            {
                // calculating width of current string
                auto chr = *itt;
                libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(chr);
                str_width += glyph->width() + font->horizontalGap();
            }
            if (str_width > str_width_max)
                str_width_max = str_width;
        }
    }

    // calculating text final width
    width_final = width() ? width() : str_width_max;

    x = 0;
    y = 0;
    // Building texture from _strings_tmp
    for (auto it = _strings_tmp.begin(); it != _strings_tmp.end(); ++it)
    {
        unsigned int str_width;
        auto font = (*it)->font();
        std::string text = (*it)->text();
        libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(' ');
        space_width = glyph->width() + font->horizontalGap();

        // calculating width of current string
        str_width = 0;
        for (auto itt = text.begin(); itt != text.end(); ++itt)
        {
            auto chr = *itt;
            libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(chr);
            str_width += glyph->width() + font->horizontalGap();
        }

        // calculating horizontal word gaps if needed
        if (_horizontalAlign == HORIZONTAL_ALIGN_JUSTIFY)
        {
            unsigned int spaces_number = 0;

            for (auto itt = text.begin(); itt != text.end(); ++itt)
            {
                auto chr = *itt;
                if (chr == ' ')
                    spaces_number++;
            }                                   
            if (spaces_number > 0)
            {
                unsigned int words_width;
                words_width = str_width - spaces_number*space_width;
                horizontal_word_gap = (width_final - words_width) / spaces_number;
                horizontal_error = width_final - words_width - spaces_number*horizontal_word_gap;
            }
        }

        // calculating starting x
        x = 0;
        if (_horizontalAlign == HORIZONTAL_ALIGN_CENTER)
            x = (width_final - str_width)/2;
        if (_horizontalAlign == HORIZONTAL_ALIGN_RIGHT)
            x = width_final - str_width;

        for (auto itt = text.begin(); itt != text.end(); ++itt)
        {
            auto chr = *itt;
            libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(chr);

            unsigned int xOffset = (unsigned char)(chr%16) * font->width();
            unsigned int yOffset = (unsigned char)(chr/16) * font->height();
            font->texture()->blitTo(_texture, x, y, xOffset, yOffset, font->width(), font->height());
            if ((chr == ' ') && (_horizontalAlign == HORIZONTAL_ALIGN_JUSTIFY))
            {
                x += horizontal_word_gap; 
                if (horizontal_error != 0)
                {
                    horizontal_error--;
                    x++;
                }
            }
            else
                x += glyph->width() + font->horizontalGap();
        }
        y += font->height() + font->verticalGap();
    }

    // deleting _string_tmp
    while (!_strings_tmp.empty())
    {
        delete _strings_tmp.back();
        _strings_tmp.pop_back();
    }

    return _texture;
}

std::string TextArea::text()
{
    return _strings.back()->text();
}

unsigned int TextArea::_calculateHeight()
{
    unsigned int totalHeight = 0;
    unsigned int height = 0;
    unsigned int maxHeight = 0;

    for (auto it = _strings.begin(); it != _strings.end(); ++it)
    {
        auto font = (*it)->font();
        std::string text = (*it)->text();

        for (auto itt = text.begin(); itt != text.end(); ++itt)
        {
            unsigned char chr = *itt;

            if (chr == '\n')
            {
                totalHeight += maxHeight;
                maxHeight = 0;
                height = 0;
            }
            else
            {
                height = font->aaf()->glyphs()->at(chr)->height() + font->aaf()->verticalGap();
                if (height > maxHeight)
                {
                    maxHeight = height;
                }
            }
        }
    }

    totalHeight += maxHeight;

    if (totalHeight > 0)
    {
        totalHeight -= _strings.back()->font()->aaf()->verticalGap();
    }

    return totalHeight;
}

unsigned int TextArea::_calculateWidth()
{
    unsigned int maxWidth = 0;
    unsigned int width = 0;

    for (auto it = _strings.begin(); it != _strings.end(); ++it)
    {
        auto font = (*it)->font();
        std::string text = (*it)->text();

        for (auto itt = text.begin(); itt != text.end(); ++itt)
        {
            unsigned char chr = *itt;

            if (chr == '\n')
            {
                if (width > maxWidth)
                {
                    maxWidth = width;
                }
                width = 0;
            }
            else
            {
                width += font->aaf()->glyphs()->at(chr)->width() + font->aaf()->horizontalGap();
            }
        }
    }
    if (width > maxWidth)
    {
        maxWidth = width;
    }
    return maxWidth;
}

}

