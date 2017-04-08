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

// Related headers
#include "../UI/Image.h"

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"
#include "../Format/Frm/File.h"
#include "../Format/Frm/Direction.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TransFlags.h"
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

Image::Image(const std::string& filename) : Falltergeist::UI::Base(), _sprite(filename)
{
}

Image::~Image()
{
}

void Image::render(bool eggTransparency)
{
    _sprite.trans(_trans);
    _sprite.render(position().x(),position().y(), eggTransparency, light(), _outline, _lightLevel);
}

Image::Image(Format::Frm::File *frm, unsigned int direction) : Falltergeist::UI::Base(), _sprite(frm)
{
    if (direction >= frm->directions().size())
    {
        //throw Exception("Image::Image(frm, direction) - direction not found: " + std::to_string(direction));
        direction = 0;
    }
    auto& dir = frm->directions().at(direction);
    setOffset(frm->offsetX(direction) + dir.shiftX(),
      frm->offsetY(direction) + dir.shiftY());
}

Size Image::size() const
{
//    int w = _sprite.width();
//    int h = _sprite.height();
//    return Size(w,h);
    return _sprite.size();
}


bool Image::opaque(unsigned int x, unsigned int y)
{
    return _sprite.opaque(x, y);
}

bool Image::opaque(const Point &pos)
{
    return opaque(pos.x(), pos.y());
}

void Image::render(const Size &size, bool eggTransparency)
{
    _sprite.renderScaled(position().x(), position().y(), size.width(), size.height(), eggTransparency, light(), _outline);
}

}
}
