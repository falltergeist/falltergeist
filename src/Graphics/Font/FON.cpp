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

#include "Base/StlFeatures.h"
#include <ResourceManager.h>
#include "FON.h"

namespace Falltergeist {
using Base::make_unique;
namespace Graphics {


FON::FON(const std::string& filename) : Font() {
    _filename = filename;
    _fon = ResourceManager::getInstance()->fonFileType(filename);

    unsigned int width = _fon->maximumWidth()*16u;
    unsigned int height = _fon->maximumHeight()*16u;


    _texture = make_unique<Graphics::Texture>(width, height);
    _texture->loadFromRGBA(_fon->rgba());
}

FON::~FON() {

}

unsigned short FON::horizontalGap() {
    return _fon->horizontalGap();
}

unsigned short FON::verticalGap() {
    return _fon->verticalGap();
}

unsigned short FON::spaceWidth() {
    return _fon->spaceWidth();
}

unsigned short FON::width() {
    return _fon->maximumWidth();
}

unsigned short FON::height() {
    return _fon->maximumHeight();
}
}
}
