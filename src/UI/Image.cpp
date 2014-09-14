/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../Engine/Graphics/Texture.h"
#include "../Engine/ResourceManager.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

Image::Image(std::string filename) : ActiveUI()
{
    setTexture(ResourceManager::texture(filename));
}

Image::Image(std::shared_ptr<Image> image) : ActiveUI()
{
    _imageTexture = std::shared_ptr<Texture>(new Texture(image->texture()->width(), image->texture()->height()));
    _imageTexture->loadFromRGBA(image->texture()->data());
    setTexture(_imageTexture);
}

Image::Image(unsigned int width, unsigned int height) : ActiveUI()
{
    _imageTexture = std::shared_ptr<Texture>(new Texture(width, height));
    setTexture(_imageTexture);
}

Image::Image(std::shared_ptr<Texture> texture) : ActiveUI()
{
    _imageTexture = std::shared_ptr<Texture>(new Texture(texture->width(), texture->height()));
    _imageTexture->loadFromRGBA(texture->data());
    setTexture(_imageTexture);
}

Image::Image(std::shared_ptr<libfalltergeist::FrmFileType> frm, unsigned int direction)
{
    _imageTexture = std::shared_ptr<Texture>(new Texture(frm->width(), frm->height()));
    _imageTexture->loadFromRGBA(frm->rgba(ResourceManager::palFileType("color.pal")));
    setTexture(_imageTexture);
    setXOffset(frm->offsetX(direction) + frm->shiftX(direction) - width()/2);
    setYOffset(frm->offsetY(direction) + frm->shiftY(direction) - height());
}

Image::~Image()
{
}

unsigned int Image::width()
{
    return texture()->width();
}

unsigned int Image::height()
{
    return texture()->height();
}

}
