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

// Related headers
#include "../UI/Image.h"

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

Image::Image(const std::string& filename) : Falltergeist::UI::Base()
{
    setTexture(ResourceManager::getInstance()->texture(filename));
}

Image::Image(Image* image) : Falltergeist::UI::Base()
{
    // @fixme: we should use "clone" feature here
    setTexture(new Graphics::Texture(image->texture()->width(), image->texture()->height()));
    unsigned int* pixels = (unsigned int*)image->texture()->sdlSurface()->pixels;
    _texture->loadFromRGBA(pixels);
}

Image::Image(unsigned int width, unsigned int height) : Falltergeist::UI::Base()
{
    setTexture(new Graphics::Texture(width, height));
}

Image::Image(Graphics::Texture* texture) : Falltergeist::UI::Base()
{
    setTexture(texture);
}

Image::Image(libfalltergeist::Frm::File* frm, unsigned int direction) : Falltergeist::UI::Base()
{
    if (direction >= frm->directions()->size())
    {
        throw Exception("Image::Image(frm, direction) - direction not found: " + std::to_string(direction));
    }

    // direction texture
    setTexture(new Graphics::Texture(frm->directions()->at(direction)->width(), frm->directions()->at(direction)->height()));

    // full frm texture
    Graphics::Texture* texture = new Graphics::Texture(frm->width(), frm->height());
    texture->loadFromRGBA(frm->rgba(ResourceManager::getInstance()->palFileType("color.pal")));

    // direction offset in full texture
    unsigned int y = 0;
    for (unsigned int i = 0; i != direction; ++i)
    {
        y += frm->directions()->at(direction)->height();
    }

    texture->copyTo(_texture, 0, 0, 0, y, frm->directions()->at(direction)->width(), frm->directions()->at(direction)->height());
    delete texture;
    auto dir = frm->directions()->at(direction);
    setOffset(
        frm->offsetX(direction) + dir->shiftX(),
        frm->offsetY(direction) + dir->shiftY()
    );
}

Image::~Image()
{
}

}
}
