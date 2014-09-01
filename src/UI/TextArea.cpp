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
    _strings.push_back(new FontString(text, font));
    return this;
}

TextArea * TextArea::setFont(Font* font)
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
    return _height;
}

Texture* TextArea::texture()
{
    if (_texture) return _texture;

    // Рассчитываем размеры текстуры

    unsigned int width = 0;
    unsigned int height = 0;

    auto string = _strings.back();

    std::string text = string->text();
    Font* font = string->font();

    width = 0;
    height = font->height();

    for (unsigned int i = 0; i != text.length(); i++)
    {
        unsigned char chr = text[i];
        width += font->aaf()->glyphs()->at(chr)->width() + font->horizontalGap();
    }

    _texture = new Texture(width, height);
    unsigned int x = 0;
    unsigned int y = 0;

    for (unsigned int i = 0; i != text.length(); i++)
    {
        unsigned char chr = text[i];
        libfalltergeist::AafGlyph* glyph = font->aaf()->glyphs()->at(chr);

        unsigned int xOffset = (unsigned char)(chr%16) * font->width();
        unsigned int yOffset = (unsigned char)(chr/16) * font->height();

        font->texture()->copyTo(_texture, x, y, xOffset, yOffset, glyph->width(), glyph->height());
        x += glyph->width() + font->horizontalGap();

    }




    return _texture;
}

std::string TextArea::text()
{
    return _strings.back()->text();
}

}
