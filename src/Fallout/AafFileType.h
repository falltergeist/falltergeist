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

#ifndef FALLTERGEIST_AAFFILETYPE_H
#define FALLTERGEIST_AAFFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{
struct AafGlyph
{
    unsigned short width;
    unsigned short height;
    unsigned int dataOffset;
    char * data;
};

class AafFileType : public VirtualFile
{
protected:
    unsigned short _maximumHeight;
    unsigned short _horizontalGap;
    unsigned short _spaceWidth;
    unsigned short _verticalGap;
    AafGlyph * _glyphs;
    void _init();
public:
    AafFileType(VirtualFile * virtualFile);
    AafGlyph * getChar(unsigned char chr);
    unsigned short getSpaceWidth();
    unsigned short getHorizontalGap();
    unsigned short getMaximumHeight();
    ~AafFileType();
};

}
#endif // FALLTERGEIST_AAFFILETYPE_H
