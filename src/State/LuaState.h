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
    ~LuaState() override;

    bool modal() const override ;
    void setModal(bool value) override;

    bool fullscreen() const override;
    void setFullscreen(bool value) override;

    const Point& position() const override;
    void setPosition(const Point& pos) override;

    void init() override;
    void think() override;
    void handle(Event::Event* event) override;
    void render() override;

    void addUI(UI::Base* ui);

private:
    Lua::Script* _script = nullptr;

};

}
}
#endif // FALLTERGEIST_STATE_LUASTATE_H
