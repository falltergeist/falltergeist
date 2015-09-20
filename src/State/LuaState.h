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
#include "../Lua/Inheritable.h"
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
class Image;

namespace State
{

class LuaState : public State
{
public:

    LuaState(luabridge::LuaRef table);
    ~LuaState() override;

    template <typename T, typename ...ArgT>
    static T* pushNew(ArgT... args)
    {
        T* obj = new T(args...);
        Game::getInstance()->pushState(obj);
        return obj;
    }

    void think() override;
    void handle(Event::Event* event) override;
    void render() override;

    void addUI(UI::Base* ui);


    virtual void onStateActivate(Event::State* event) override;

    virtual void onStateDeactivate(Event::State* event) override;

    virtual void onKeyDown(Event::Keyboard* event) override;

private:
    Lua::Inheritable _inheritable;

};

}
}
#endif // FALLTERGEIST_STATE_LUASTATE_H
