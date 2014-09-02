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
#include "../UI/Image.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/ResourceManager.h"

// Third party includes

namespace Falltergeist
{

Image::Image(std::string filename) : ActiveUI()
{
    setTexture(ResourceManager::texture(filename));
}

Image::Image(Image* image) : ActiveUI()
{
    _imageTexture = new Texture(image->texture()->width(), image->texture()->height());
    _imageTexture->loadFromRGBA(image->texture()->data());
    setTexture(_imageTexture);
}

Image::Image(unsigned int width, unsigned int height) : ActiveUI()
{
    _imageTexture = new Texture(width, height);
    setTexture(_imageTexture);
}

Image::~Image()
{
    if (_imageTexture != 0)
    {
        delete _imageTexture;
        _imageTexture = 0;
    }
}


}
