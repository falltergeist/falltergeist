/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_FONT_H
#define FALLTERGEIST_FONT_H

// C++ standard includes
#include <memory>
#include <vector>
#include <string>

// Falltergeist includes
#include "Graphics/Texture.h"
#include "Format/Aaf/File.h"

// Third party includes

namespace Falltergeist
{
    namespace Format
    {
        namespace Aaf
        {
            class File;
        }
    }

    class Font
    {
        public:
            Font(const std::string& filename, unsigned int color);
            ~Font();

            unsigned int color();

            unsigned short horizontalGap();

            unsigned short verticalGap();

            unsigned short spaceWidth();

            unsigned short width();
            unsigned short height();

            std::string filename() const;

            Graphics::Texture* texture();

            Format::Aaf::File* aaf();

        protected:
            unsigned int _color = 0;
            Format::Aaf::File* _aaf = nullptr;
            std::unique_ptr<Graphics::Texture> _texture = nullptr;
            std::string _filename;
    };
}
#endif // FALLTERGEIST_FONT_H
