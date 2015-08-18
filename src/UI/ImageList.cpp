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
#include "../UI/ImageList.h"

// C++ standard includes

// Falltergeist includes
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

ImageList::ImageList(std::vector<std::string> imageList, int x, int y) : Falltergeist::UI::Base(x,y)
{
    for (auto& frmName : imageList) addImage(new Image(frmName));
}

ImageList::ImageList(std::vector<Image*> imageList, int x, int y) : Falltergeist::UI::Base(x,y)
{
    for (auto& image : imageList) addImage(new Image(image));
}

ImageList::ImageList(int x, int y) : Falltergeist::UI::Base(x,y)
{
}

ImageList::~ImageList()
{
    while (!_images.empty())
    {
        delete _images.back();
        _images.pop_back();
    }
}

unsigned int ImageList::currentImage() const
{
    return _currentImage;
}

void ImageList::setCurrentImage(unsigned int number)
{
    _currentImage = number;
}

void ImageList::addImage(Image* image)
{
    _images.push_back(image);
}

void ImageList::addImage(const std::string& filename)
{
    addImage(new Image(filename));
}

Texture* ImageList::texture() const
{
    return images()->at(currentImage())->texture();
}

const std::vector<Image*>* ImageList::images() const
{
    return &_images;
}

}
}
