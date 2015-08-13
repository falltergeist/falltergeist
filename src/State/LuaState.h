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

#ifndef FALLTERGEIST_STATE_LUASTATE_H
#define FALLTERGEIST_STATE_LUASTATE_H

// C++ standard includes

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
class Image;

namespace Lua
{
    class Script;
}
namespace State
{

class LuaState : public State
{

public:
    LuaState(const std::string& filename);
    virtual ~LuaState();

    virtual int x() const;
    virtual void setX(int value);

    virtual int y() const;
    virtual void setY(int value);

    virtual bool modal() const;
    virtual void setModal(bool value);

    virtual bool fullscreen() const;
    virtual void setFullscreen(bool value);

    virtual void init();
    virtual void think();
    virtual void handle(Event* event);
    virtual void render();

    virtual void addImage(Image* ui);


    static void export_to_lua_script(Lua::Script* script);

private:
    Lua::Script* _script = nullptr;

};

}
}
#endif // FALLTERGEIST_STATE_LUASTATE_H
