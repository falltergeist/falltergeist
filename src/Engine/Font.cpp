/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <iostream>

// Falltergeist includes
#include "../Engine/Font.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"

// Third party includes

namespace Falltergeist
{

Font::Font(const char * filename, unsigned int color)
{
    _color = 0;
    _glyphs = new std::vector<Surface *>;
    setFilename(filename);
    setColor(color);
    for (int i = 0; i < 256; i++) _glyphs->push_back(0);
}

Font::~Font()
{
    while (!_glyphs->empty())
    {
        delete _glyphs->back();
        _glyphs->pop_back();
    }
    delete _glyphs;
}

void Font::setFilename(const char * filename)
{
    _filename = filename;
    _aafFileType = ResourceManager::aafFileType(_filename);
}

const char * Font::filename()
{
    return _filename;
}

void Font::setColor(unsigned int color)
{
    if (_color == color) return;
    _color = color;
    while (!_glyphs->empty())
    {
        delete _glyphs->back();
        _glyphs->pop_back();
    }
    delete _glyphs;
    _glyphs = new std::vector<Surface *>;
    for (int i = 0; i < 256; i++) _glyphs->push_back(0);
}

unsigned int Font::color()
{
    return _color;
}

unsigned short Font::height()
{
    return _aafFileType->maximumHeight();
}

unsigned short Font::horizontalGap()
{
    return _aafFileType->horizontalGap();
}

unsigned short Font::verticalGap()
{
    return _aafFileType->verticalGap();
}

unsigned short Font::spaceWidth()
{
    return _aafFileType->spaceWidth();
}

Surface * Font::glyph(unsigned char chr)
{
    if (_glyphs->at(chr) != 0) return _glyphs->at(chr);

    int charWidth = _aafFileType->glyphs()->at(chr)->width();
    int charHeight = _aafFileType->glyphs()->at(chr)->height();
    int height = this->height();
    int delta = height - charHeight;

    Surface * surface = new Surface(charWidth,height);
    int i = 0;
    for(int y = 0; y != charHeight; ++y)
    {
        for (int x = 0; x != charWidth; ++x)
        {
            unsigned char ch = _aafFileType->glyphs()->at(chr)->data()->at(i);
            if (ch != 0)
            {
                float lightness;
                switch (ch)
                {
                    case 9:
                        lightness = 1.2;
                        break;
                    case 8:
                        lightness = 1.1;
                        break;
                    case 7:
                        lightness = 1;
                        break;
                    case 6:
                        lightness = 0.9;
                        break;
                    case 5:
                        lightness = 0.8;
                        break;
                    case 4:
                        lightness = 0.7;
                        break;
                    case 3:
                        lightness = 0.6;
                        break;
                    case 2:
                        lightness = 0.5;
                        break;
                    case 1:
                        lightness = 0.4;
                        break;
                }

                unsigned int color = this->color();

                //unsigned char red =   ((color & 0x00FF0000) >> 16) * lightness;
                //unsigned char green = ((color & 0x0000FF00) >> 8) * lightness;
                //unsigned char blue =  (color & 0x000000FF) * lightness;
                //color = 0xFF000000 | red << 16 | green << 8 | blue;
                color = ((unsigned char)( 0xFF * lightness) << 24) | (0x00FFFFFF & color);

                surface->setPixel(x,delta + y,color);
            }
            i++;
        }
    }
    _glyphs->at(chr) = surface;
    return _glyphs->at(chr);

}

}
