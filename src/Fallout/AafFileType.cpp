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

#include "../Fallout/AafFileType.h"

namespace Falltergeist
{

AafFileType::AafFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _init();
}

AafFileType::~AafFileType()
{
    delete [] _glyphs; _glyphs = 0;
}

void AafFileType::_init()
{
    setPosition(0);
    // signature
    skipBytes(4);
    (*this) >> _maximumHeight >> _horizontalGap >> _spaceWidth >> _verticalGap;
    _glyphs = new AafGlyph[256];

    for (int i = 0; i != 256; ++i)
    {
        (*this) >> _glyphs[i].width >> _glyphs[i].height >> _glyphs[i].dataOffset;
    }

    setPosition(0x080C);
    for (int i = 0; i != 256; ++i)
    {
        unsigned int width = _glyphs[i].width;
        unsigned int height = _glyphs[i].height;
        if ( width * height  == 0) continue;

        _glyphs[i].data = new char[width * height];

        readBytes(_glyphs[i].data, width*height);
    }
}

AafGlyph * AafFileType::getChar(unsigned char chr)
{
    return &_glyphs[chr];
}

unsigned short AafFileType::getHorizontalGap()
{
    return _horizontalGap;
}

unsigned short AafFileType::getSpaceWidth()
{
    return _spaceWidth;
}

unsigned short AafFileType::getMaximumHeight()
{
    return _maximumHeight;
}

}
