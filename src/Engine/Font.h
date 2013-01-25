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

#ifndef FALLTERGEIST_FONT_H
#define FALLTERGEIST_FONT_H

#include "../Engine/Surface.h"
#include "../../lib/libfalltergeist/libfalltergeist.h"
#include <vector>

namespace Falltergeist
{

class Font
{
protected:
    std::vector<Surface *> * _glyphs;
    const char * _filename;
    unsigned int _color;
    libfalltergeist::AafFileType * _aafFileType;
public:
    Font(const char * filename, unsigned int color = 0x00FF00FF);
    ~Font();
    void setFilename(const char * filename);
    const char * getFilename();
    void setColor(unsigned int color);
    unsigned int getColor();
    Surface * getGlyph(unsigned char chr);
    unsigned short getHorizontalGap();
    unsigned short getVerticalGap();
    unsigned short getHeight();
};

}
#endif // FALLTERGEIST_FONT_H
