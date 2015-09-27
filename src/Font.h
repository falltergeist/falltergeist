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

#ifndef FALLTERGEIST_FONT_H
#define FALLTERGEIST_FONT_H

// C++ standard includes
#include <vector>
#include <string>

// Falltergeist includes
#include "Graphics/Texture.h"

// Third party includes
#include <libfalltergeist/Aaf/File.h>
#include <libfalltergeist/Aaf/Glyph.h>

namespace Falltergeist
{

class Font
{
public:
    Font(const std::string& filename, unsigned int color);
    ~Font();

    unsigned int color();

    unsigned short horizontalGap();

    unsigned short verticalGap();

    unsigned short spaceWidth();

    unsigned short width();
    unsigned short height();
    
    std::string filename() const;

    Graphics::Texture* texture();

    libfalltergeist::Aaf::File* aaf();

protected:
    unsigned int _color = 0;
    libfalltergeist::Aaf::File* _aaf = nullptr;
    Graphics::Texture* _texture = nullptr;
    std::string _filename;

};

}
#endif // FALLTERGEIST_FONT_H
