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

#ifndef FALLTERGEIST_UI_IMAGE_H
#define FALLTERGEIST_UI_IMAGE_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../UI/Base.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{
namespace UI
{

class Image : public Falltergeist::UI::Base
{
public:
    Image(const std::string& filename);
    Image(unsigned int width, unsigned int height);
    Image(Image* image);
    Image(Texture* texture);
    Image(libfalltergeist::Frm::File* frm, unsigned int direction);
    ~Image() override;

    unsigned int width() const override;
    unsigned int height() const override;
};

}
}
#endif // FALLTERGEIST_UI_IMAGE_H
