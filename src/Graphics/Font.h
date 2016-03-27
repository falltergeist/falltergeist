/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GRAPHICS_FONT_H
#define FALLTERGEIST_GRAPHICS_FONT_H

// C++ standard includes
#include <memory>
#include <vector>
#include <string>

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Texture.h"

// Third party includes

namespace Falltergeist {
namespace Graphics {

struct TextSymbol
{
    uint8_t chr;
    Point position;
};

class Font {
public:
    Font() {}
    virtual ~Font() {}

    virtual unsigned short horizontalGap() { return 0; }
    virtual unsigned short verticalGap() { return 0; }
    virtual unsigned short spaceWidth() { return 0; }
    virtual unsigned short width() { return 0; }
    virtual unsigned short height() { return 0; }
    virtual unsigned short glyphWidth(uint8_t ch) { return 0; }

    virtual std::string filename() const { return _filename; }
    virtual Graphics::Texture *texture() { return _texture.get(); }

protected:
    std::unique_ptr<Graphics::Texture> _texture = nullptr;
    std::string _filename;

};

}
}
#endif // FALLTERGEIST_GRAPHICS_FONT_H
