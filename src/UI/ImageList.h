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

#ifndef FALLTERGEIST_UI_IMAGELIST_H
#define FALLTERGEIST_UI_IMAGELIST_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{
class Image;

class ImageList : public Falltergeist::UI::Base
{
public:
    ImageList(const Point& pos = Point());
    ImageList(std::vector<std::string> imageList, int x, int y);
    ~ImageList() override;

    void addImage(std::unique_ptr<Image> image);
    void addImage(const std::string& filename);
    void setCurrentImage(unsigned int number);
    unsigned int currentImage() const;
    const std::vector<std::unique_ptr<Image>>& images() const;

    virtual bool opaque(const Point &pos) override;

    virtual void render(bool eggTransparency) override;
    virtual void setPosition(const Point &pos) override;

protected:
    std::vector<std::unique_ptr<Image>> _images;
    unsigned int _currentImage = 0;
};

}
}
#endif // FALLTERGEIST_UI_IMAGELIST_H
