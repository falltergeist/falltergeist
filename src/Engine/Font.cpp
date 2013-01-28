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

#include "../Engine/Font.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include <iostream>

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
    delete _glyphs;
}

void Font::setFilename(const char * filename)
{
    _filename = filename;
    _aafFileType = ResourceManager::getAafFileType(_filename);
}

const char * Font::getFilename()
{
    return _filename;
}

void Font::setColor(unsigned int color)
{
    if (_color == color) return;
    _color = color;
    delete _glyphs;
    _glyphs = new std::vector<Surface *>;
    for (int i = 0; i < 256; i++) _glyphs->push_back(0);
}

unsigned int Font::getColor()
{
    return _color;
}

unsigned short Font::getHeight()
{
    return _aafFileType->maximumHeight();
}

unsigned short Font::getHorizontalGap()
{
    return _aafFileType->horizontalGap();
}

unsigned short Font::getVerticalGap()
{
    return _aafFileType->verticalGap();
}

Surface * Font::getGlyph(unsigned char chr)
{

    if (_glyphs->at(chr) != 0) return _glyphs->at(chr);

    int charWidth = _aafFileType->glyphs()->at(chr)->width();
    int charHeight = _aafFileType->glyphs()->at(chr)->height();
    int height = getHeight();
    int delta = height - charHeight;
    //char * data = _aafFileType->getChar(chr)->data;

    Surface * surface = new Surface(charWidth,height);
    int i = 0;
    for(int y = 0; y != charHeight; ++y)
    {
        for (int x = 0; x != charWidth; ++x)
        {
            unsigned char ch = _aafFileType->glyphs()->at(chr)->data()->at(i);
            if (ch != 0)
            {
                long lightness;
                switch (ch)
                {
                    case 8:
                        lightness = 1.15;
                        break;
                    case 7:
                        lightness = 1.3;
                        break;
                    case 6:
                        lightness = 1.45;
                        break;
                    case 5:
                        lightness = 1.6;
                        break;
                    case 4:
                        lightness = 1.75;
                        break;
                    case 3:
                        lightness = 2;
                        break;
                    case 2:
                        lightness = 2.15;
                        break;
                    case 1:
                        lightness = 2.3;
                        break;
                    default:
                        lightness = 1;
                        break;
                }

                unsigned int color = getColor();
                unsigned int red =   ((color & 0xFF000000) >> 16) / lightness;
                unsigned int green = ((color & 0x00FF0000) >> 8)  / lightness;
                unsigned int blue =   (color & 0x0000FF00) / lightness;
                unsigned int alpha =  (color & 0x000000FF) >> 24;
                color = (alpha << 24 ) | (red << 16) | (green << 8) | blue;
                surface->setPixel(x,delta + y,color);
            }
            i++;
        }
    }
    _glyphs->at(chr) = surface;
    return _glyphs->at(chr);

}

}
