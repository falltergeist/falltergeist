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

#include "../Fallout/PalFileType.h"

#include <iostream>

namespace Falltergeist
{

PalColor::operator int()
{
    int color = ((red * 4) << 16) | ((green * 4) << 8) | (blue * 4);
    if (color == 0) return 0;
    return 0xFF000000 | color;
}

PalColor::operator unsigned int()
{
    unsigned int color = ((red * 4) << 16) | ((green * 4) << 8) | (blue * 4);
    if (color == 0) return 0;
    return 0xFF000000 | color;
}

PalFileType::PalFileType(VirtualFile * virtualFile) : VirtualFile(virtualFile)
{
    _colors = new PalColor[256];
    _init();
}

PalFileType::~PalFileType()
{
    delete [] _colors; _colors = 0;
}

/**
 * Reads data from pal file
 * @brief PalFileType::_init
 */
void PalFileType::_init()
{
    setPosition(0);
    // reading colors from file
    for (unsigned char i = 0; i < 255; i++)
    {
        (*this) >> _colors[i].red >> _colors[i].green >> _colors[i].blue;
    }
}

/**
 * Returns color by given index
 * @brief PalFileType::getColor
 * @param colorIndex
 * @return
 */
PalColor * PalFileType::getColor(unsigned char colorIndex)
{
    return &_colors[colorIndex];
}

}
