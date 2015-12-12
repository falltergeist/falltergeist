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
#include "../Base/StlFeatures.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
using Base::make_unique;

namespace UI
{

ImageList::ImageList(const Point& pos) : Falltergeist::UI::Base(pos)
{
}

ImageList::ImageList(std::vector<std::string> imageList, int x, int y) : ImageList(Point(x, y))
{
    for (auto& frmName : imageList) addImage(std::make_unique<Image>(frmName));
}

ImageList::ImageList(std::vector<Image*> imageList, int x, int y) : ImageList(Point(x, y))
{
    for (auto& image : imageList) addImage(make_unique<Image>(*image));
}

ImageList::~ImageList()
{
}

unsigned int ImageList::currentImage() const
{
    return _currentImage;
}

void ImageList::setCurrentImage(unsigned int number)
{
    _currentImage = number;
}

void ImageList::addImage(std::unique_ptr<Image> image)
{
    _images.push_back(std::move(image));
}

void ImageList::addImage(const std::string& filename)
{
    addImage(std::make_unique<Image>(filename));
}

Graphics::Texture* ImageList::texture() const
{
    return _images.at(currentImage())->texture();
}

const std::vector<std::unique_ptr<Image>>& ImageList::images() const
{
    return _images;
}

}
}
