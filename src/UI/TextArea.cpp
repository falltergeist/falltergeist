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

// Falltergeist includes
#include "../Engine/Font.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/CrossPlatform.h"
#include "../UI/TextArea.h"
#include "../Engine/Graphics/Texture.h"

// Third party includes

namespace Falltergeist
{

TextArea::TextArea(libfalltergeist::MsgMessage* message, int x, int y) : ActiveUI(x, y)
{
    setText(message->text());
}

TextArea::TextArea(int x, int y) : ActiveUI(x, y)
{
}

TextArea::TextArea(std::string text, int x, int y) : ActiveUI(x, y)
{
    setText(text);
}

TextArea::TextArea(TextArea* textArea, int x, int y) : ActiveUI(x, y)
{
    /*
    setText(textArea->text());
    setColor(textArea->color());
    setHorizontalAlign(textArea->horizontalAlign());
    setVerticalAlign(textArea->verticalAlign());
    if (textArea->_width) setWidth(textArea->width());
    if (textArea->_height) setWidth(textArea->height());
    setFont(textArea->font()->filename());
    setWordWrap(textArea->wordWrap());
    */
}

TextArea::~TextArea()
{
/*
    delete _textLines;

    if (_textSurfaces != 0)
    {
        while (!_textSurfaces->empty())
        {
            delete _textSurfaces->back();
            _textSurfaces->pop_back();
        }
        delete _textSurfaces;
    }

    delete _font;
*/
}

Font * TextArea::font()
{
    return _font;
}

void TextArea::_calculateSize()
{
}

TextArea * TextArea::appendText(std::string text)
{
    _text += text;
    return this;
}


TextArea * TextArea::appendText(int number)
{
    std::stringstream ss;
    ss << number;
    return appendText(ss.str());
}



unsigned int TextArea::color()
{
    return _color;
}

TextArea * TextArea::setColor(unsigned int color)
{
    if (_color == color) return this;
    _color = color;
    if (!_font) return this;
    _font->setColor(color);
    return this;
}

int TextArea::height()
{
    if (_height == 0)
    {
        if (_calculatedHeight == 0) _calculateSize();
        return _calculatedHeight;
    }
    return _height;
}

TextArea * TextArea::setHeight(int height)
{
    if (height == _height) return this;
    _height = height;
    return this;
}

int TextArea::width()
{
    if (_width == 0)
    {
        if (_calculatedWidth == 0) _calculateSize();
        return _calculatedWidth;
    }
    return _width;
}

TextArea * TextArea::setWidth(int width)
{
    if (_width == width) return this;
    _width = width;
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
    return this;
}

std::string TextArea::text()
{
    return _text;
}

TextArea * TextArea::setText(libfalltergeist::MsgMessage * message)
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
    if (_text.compare(text) == 0) return this; // if text not changed

    _calculatedWidth = 0;
    _calculatedHeight = 0;
    delete _textLines; _textLines = 0;
    _text = text;
    return this;
}

TextArea * TextArea::setFont(std::string filename)
{
    delete _font;
    _font = new Font(filename, _color);
    return this;
}

TextArea * TextArea::setWordWrap(bool wordWrap)
{
    _wordWrap = wordWrap;
    return this;
}

bool TextArea::wordWrap()
{
    return _wordWrap;
}

void TextArea::setBackgroundColor(unsigned int color)
{

}

Texture* TextArea::texture()
{
    if (!_texture) _texture = new Texture(10, 10);
    return _texture;
}

}
