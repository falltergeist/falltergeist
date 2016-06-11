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

// Related headers
#include "../../Graphics/Font/AAF.h"

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../../Format/Aaf/Glyph.h"
#include "../../ResourceManager.h"

// Third party includes
#include <SDL_image.h>

namespace Falltergeist
{
namespace Graphics
{


AAF::AAF(const std::string& filename) : Font()
{
    _filename = filename;
    _aaf = ResourceManager::getInstance()->aafFileType(filename);

    unsigned int width = (_aaf->maximumWidth()+2)*16u;
    unsigned int height = (_aaf->maximumHeight()+2)*16u;

    _texture = std::make_unique<Graphics::Texture>(width, height);
    _texture->loadFromRGBA(_aaf->rgba());


}

AAF::~AAF()
{
}

unsigned short AAF::horizontalGap()
{
    return _aaf->horizontalGap();
}

unsigned short AAF::verticalGap()
{
    return _aaf->verticalGap();
}

unsigned short AAF::spaceWidth()
{
    return _aaf->spaceWidth();
}

unsigned short AAF::width()
{
    return _aaf->maximumWidth();
}

unsigned short AAF::height()
{
    return _aaf->maximumHeight();
}

unsigned short AAF::glyphWidth(uint8_t ch)
{
    return _aaf->glyphs()->at(ch)->width();
}

}
}
