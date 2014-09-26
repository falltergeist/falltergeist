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

#ifndef FALLTERGEIST_IMAGELIST_H
#define FALLTERGEIST_IMAGELIST_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/Graphics/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
class Image;

class ImageList : public ActiveUI
{
protected:
    std::vector<Image*> _images;
    unsigned int _currentImage = 0;
public:
    ImageList(std::vector<std::string> imageList, int x = 0, int y = 0);
    ImageList(std::vector<Image*> imageList, int x = 0, int y = 0);
    ImageList(int x = 0, int y = 0);
    ~ImageList();

    void addImage(Image* image);
    void addImage(std::string filename);
    void setCurrentImage(unsigned int number);
    unsigned int currentImage();
    virtual Texture* texture();
    std::vector<Image*>* images();
};

}
#endif // FALLTERGEIST_IMAGELIST_H
