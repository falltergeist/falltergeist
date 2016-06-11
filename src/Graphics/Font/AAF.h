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

#ifndef FALLTERGEIST_GRAPHICS_FONT_AAF_H
#define FALLTERGEIST_GRAPHICS_FONT_AAF_H

// C++ standard includes

// Falltergeist includes
#include "../../Format/Aaf/File.h"
#include "../../Graphics/Font.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

class AAF : public Graphics::Font
{

public:
    AAF(const std::string& filename);
    ~AAF();

    virtual unsigned short horizontalGap() override;
    virtual unsigned short verticalGap() override;
    virtual unsigned short spaceWidth() override;
    virtual unsigned short width() override;
    virtual unsigned short height() override;
    virtual unsigned short glyphWidth(uint8_t ch) override;


private:
    Format::Aaf::File* _aaf = nullptr;
};

}
}
#endif //FALLTERGEIST_GRAPHICS_FONT_AAF_H
