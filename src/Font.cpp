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

// C++ standard includes

// Falltergeist includes
#include "Base/StlFeatures.h"
#include "Font.h"
#include "ResourceManager.h"

// Third party includes

namespace Falltergeist
{
using namespace Base;

Font::Font(const std::string& filename, unsigned int color)
{
    _filename = filename;
    _aaf = ResourceManager::getInstance()->aafFileType(filename);
    _color = color;

    unsigned int width = _aaf->maximumWidth()*16u;
    unsigned int height = _aaf->maximumHeight()*16u;

    unsigned int rgba[width * height];

    for (unsigned int y = 0; y != height; y++)
    {
        for (unsigned int x = 0; x != width; x++)
        {
            unsigned int index = y * width + x;
            unsigned char alpha = _aaf->rgba()[index];
            //if (alpha > 0) alpha = 0xff;
            rgba[index] = (color & 0xFFFFFF00) | alpha;
        }
    }

    _texture = make_unique<Graphics::Texture>(width, height);
    _texture->loadFromRGBA(rgba);
}

Font::~Font()
{
}

unsigned int Font::color()
{
    return _color;
}

unsigned short Font::height()
{
    return _aaf->maximumHeight();
}

unsigned short Font::width()
{
    return _aaf->maximumWidth();
}

unsigned short Font::horizontalGap()
{
    return _aaf->horizontalGap();
}

unsigned short Font::verticalGap()
{
    return _aaf->verticalGap();
}

unsigned short Font::spaceWidth()
{
    return _aaf->spaceWidth();
}

Graphics::Texture* Font::texture()
{
    return _texture.get();
}

std::string Font::filename() const
{
    return _filename;
}

libfalltergeist::Aaf::File* Font::aaf()
{
    return _aaf;
}

}
