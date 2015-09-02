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
#include "../Lua/ImageButton.h"

// C++ standard includes

// Falltergeist includes
#include "../Logger.h"
#include "../Lua/Inheritable.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

ImageButton::~ImageButton()
{
}

ImageButton::ImageButton(const std::string& upImg, const std::string& downImg, const std::string& upSfx,
                         const std::string& downSfx, int x, int y) :
    UI::ImageButton::ImageButton(upImg, downImg, upSfx, downSfx, x, y)
{
}

void ImageButton::subclass(luabridge::LuaRef table)
{
    if (!_inheritable) _inheritable = std::unique_ptr<Inheritable>(new Inheritable(table));
}

void ImageButton::think()
{
    if (_inheritable && (bool)_inheritable->call("think")) {
        UI::Base::think();
    }
}

}
}
