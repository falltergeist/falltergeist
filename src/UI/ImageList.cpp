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
#include "../UI/ImageList.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

ImageList::ImageList(std::vector<std::string> imageList, int x, int y) : ActiveUI(x,y)
{
    for (auto& frmName : imageList) addImage(std::shared_ptr<Image>(new Image(frmName)));
}

ImageList::ImageList(std::vector<std::shared_ptr<Image>> imageList, int x, int y) : ActiveUI(x,y)
{
    for (auto& image : imageList) addImage(image);
}

ImageList::ImageList(int x, int y) : ActiveUI(x,y)
{
}

ImageList::~ImageList()
{
}

unsigned int ImageList::currentImage()
{
    return _currentImage;
}

void ImageList::setCurrentImage(unsigned int number)
{
    _currentImage = number;
}

void ImageList::addImage(std::shared_ptr<Image> image)
{
    _images.push_back(image);
}

void ImageList::addImage(std::string filename)
{
    addImage(std::shared_ptr<Image>(new Image(filename)));
}

Texture* ImageList::texture()
{
    return _images.at(currentImage())->texture();
}

std::vector<std::shared_ptr<Image>>* ImageList::images()
{
    return &_images;
}

}
