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

#ifndef FALLTERGEIST_LUA_LUATEXTAREA_H
#define FALLTERGEIST_LUA_LUATEXTAREA_H

// C++ standard includes

// Falltergeist includes
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

/**
 * This class provides lua interface to TextArea class
 * We are forced to have this class because TextArea have methods with strongly typed enums
 */
class LuaTextArea : public UI::TextArea
{
public:
    LuaTextArea(const std::string& text, int x = 0, int y = 0);
    LuaTextArea(int x = 0, int y = 0);
    LuaTextArea(LuaTextArea* textArea, int x = 0, int y = 0);
    ~LuaTextArea() override;

    void setWidth(unsigned int width);
    unsigned int width() const override;

    void setLuaHorizontalAlign(unsigned align);
    unsigned luaHorizontalAlign() const;

};

}
}
#endif // FALLTERGEIST_LUA_LUATEXTAREA_H
