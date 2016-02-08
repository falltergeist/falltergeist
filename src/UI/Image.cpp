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
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

Image::Image(const std::string& filename) : Falltergeist::UI::Base(), _sprite(filename)
{
    //setTexture(filename);
}
/*
Image::Image(const Image& image) : Falltergeist::UI::Base(), _sprite("")
{
    // @fixme: we should use "clone" feature here
    _generateTexture(image.texture()->width(), image.texture()->height());
// TODO: newrender    unsigned int* pixels = (unsigned int*)image.texture()->sdlSurface()->pixels;
//    _texture->loadFromRGBA(pixels);
}

Image::Image(const Size& size) : Image((unsigned)size.width(), (unsigned)size.height())
{
}

Image::Image(unsigned int width, unsigned int height) : Falltergeist::UI::Base(), _sprite("")
{
    _generateTexture(width, height);
}

Image::Image(Graphics::Texture* texture) : Falltergeist::UI::Base(), _sprite("")
{
    setTexture(texture);
}

Image::Image(Format::Frm::File* frm, unsigned int direction) : Falltergeist::UI::Base(), _sprite("")
{
    if (direction >= frm->directions()->size())
    {
        throw Exception("Image::Image(frm, direction) - direction not found: " + std::to_string(direction));
    }

    // direction texture
    auto directionObj = frm->directions()->at(direction);
    _generateTexture(directionObj->width(), directionObj->height());

    // full frm texture
    Graphics::Texture* texture = ResourceManager::getInstance()->texture(frm->filename());

    // direction offset in full texture
    unsigned int y = 0;
    for (unsigned int i = 0; i != direction; ++i)
    {
        y += frm->directions()->at(direction)->height();
    }

// TODO: newrender    texture->copyTo(_texture, 0, 0, 0, y, frm->directions()->at(direction)->width(), frm->directions()->at(direction)->height());
    auto dir = frm->directions()->at(direction);
    setOffset(
        frm->offsetX(direction) + dir->shiftX(),
        frm->offsetY(direction) + dir->shiftY()
    );
}
*/
Image::~Image()
{
}

void Image::setTexture(const std::string& filename)
{
    setTexture(ResourceManager::getInstance()->texture(filename));
}

void Image::render(bool eggTransparency)
{
  _sprite.render(x(),y());
}

Image::Image(Format::Frm::File *frm) : Falltergeist::UI::Base(), _sprite(frm)
{

}
}
}
