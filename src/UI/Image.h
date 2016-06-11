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

#ifndef FALLTERGEIST_UI_IMAGE_H
#define FALLTERGEIST_UI_IMAGE_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Graphics/Sprite.h"
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{

namespace Graphics
{
class Sprite;
}

namespace Format
{
namespace Frm
{
    class File;
}
}
namespace UI
{

class Image : public Base
{
public:
    Image(const std::string& filename);
    Image(Format::Frm::File* frm, unsigned int direction);

    ~Image() override;
    virtual void render(bool eggTransparency = false) override;

    virtual void render(const Size &size, bool eggTransparency = false) override;

    bool opaque(unsigned int x, unsigned int y);
    virtual bool opaque(const Point &pos) override;

    virtual Size size() const override;
private:
    Graphics::Sprite _sprite;
};

}
}
#endif // FALLTERGEIST_UI_IMAGE_H
