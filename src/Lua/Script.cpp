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

// C++ standard includes
#include <iostream>

// Falltergeist includes
#include "../Event/Event.h"
#include "../Exception.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Point.h"
#include "../Input/Mouse.h"
#include "../Lua/ImageButton.h"
#include "../Lua/TextArea.h"
#include "../Lua/Script.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace Lua
{

using namespace luabridge;

Script::Script(const std::string& filename)
{
    _filename = filename;
    _lua_State = luaL_newstate();

    _initialize();

    if (luaL_loadfile(_lua_State, filename.c_str()))
    {
        std::string error = lua_tostring(_lua_State, -1);
        // pop error message from the stack
        lua_pop(_lua_State, 1);
        throw Exception("Lua::Script::Script() " + error);
    }

}

void Script::_initialize()
{
    luaL_openlibs(_lua_State);

    // luabridge::Namespace::addProperty cannot deduce setter type =(
    static void (*const setterGameMouse)(Input::Mouse*) = nullptr;
    static Input::Mouse* (*const getterGameMouse)() = []() -> Input::Mouse*
    {
        return Game::getInstance()->mouse();
    };

    luabridge::getGlobalNamespace(_lua_State)
        .beginNamespace("game")

            // game.Mouse
            .beginClass<Input::Mouse>("Mouse")
                .addProperty("x", &Input::Mouse::x, &Input::Mouse::setX)
                .addProperty("y", &Input::Mouse::y, &Input::Mouse::setY)
                .addProperty("cursor", &Input::Mouse::cursor, &Input::Mouse::setCursor)
            .endClass()

            // game.Event
            .beginClass<Event::Event>("Event")
                .addProperty("name", &Event::Event::name, &Event::Event::setName)
            .endClass()

            // game.State
            .beginClass<State::LuaState>("State")
                .addProperty("x", &State::LuaState::x, &State::LuaState::setX)
                .addProperty("y", &State::LuaState::y, &State::LuaState::setY)
                //.addProperty("position", &State::State::position, &State::State::setPosition)
                .addProperty("fullscreen", &State::LuaState::fullscreen, &State::LuaState::setFullscreen)
                .addProperty("modal", &State::LuaState::modal, &State::LuaState::setModal)
                .addFunction("addUI", &State::LuaState::addUI)
            .endClass()
            .beginNamespace("ui")

                .beginClass<Falltergeist::Point>("Point")
                    .addConstructor<void(*)(int, int)>()
                    .addProperty("x", &Falltergeist::Point::x, &Falltergeist::Point::setX)
                    .addProperty("y", &Falltergeist::Point::y, &Falltergeist::Point::setY)
                    .addFunction("add", &Falltergeist::Point::add)
                    .addFunction("sub", &Falltergeist::Point::sub)
                    //.addFunction("__add", &Falltergeist::Point::operator+)
                .endClass()

                .beginClass<Falltergeist::Size>("Size")
                    .addConstructor<void(*)(int, int)>()
                    .addProperty("width", &Falltergeist::Size::width, &Falltergeist::Size::setWidth)
                    .addProperty("height", &Falltergeist::Size::height, &Falltergeist::Size::setHeight)
                    .addFunction("add", &Falltergeist::Size::add)
                    .addFunction("sub", &Falltergeist::Size::sub)
                .endClass()

                // game.ui.UI
                .beginClass<Falltergeist::UI::Base>("UI")
                    //.addProperty("x", &UI::x, &UI::setX)
                    //.addProperty("y", &UI::y, &UI::setY)
                .endClass()

                // game.ui.Image
                .deriveClass<UI::Image, Falltergeist::UI::Base>("Image")
                    .addConstructor<void(*)(char const*)>()
                .endClass()

                // game.ui.ImageButton
                .deriveClass<Lua::ImageButton, Falltergeist::UI::Base>("ImageButton")
                    .addConstructor<void(*)(unsigned, int, int)>()
                .endClass()

                // game.ui.TextArea
                .deriveClass<Lua::TextArea, Falltergeist::UI::Base>("TextArea")
                    .addConstructor<void(*)(const char*, int, int)>()
                    .addProperty("width", &Lua::TextArea::width, &Lua::TextArea::setWidth)
                    .addProperty("horizontalAlign", &Lua::TextArea::luaHorizontalAlign, &Lua::TextArea::setLuaHorizontalAlign)
                .endClass()
            .endNamespace()

            // game.translate
            .addFunction("translate", translate)

            // game.mouse
            .addProperty ("mouse", getterGameMouse, setterGameMouse)
        .endNamespace();
}

void Script::run()
{
    int result = lua_pcall(_lua_State, 0, 0, 0);

    if (result)
    {
        std::string error = lua_tostring(_lua_State, -1);
        // pop error message from the stack
        lua_pop(_lua_State, 1);
        throw Exception("Lua::Script::run() " + error);
    }
}

Script::~Script()
{
    lua_close(_lua_State);
}

bool Script::get(const std::string& name, bool defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (lua_isnil(_lua_State, -1))
    {
        return defaultValue;
    }
    bool ret = lua_toboolean(_lua_State, -1);
    lua_pop(_lua_State, 1);
    return ret;
}

int Script::get(const std::string& name, int defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isnumber(_lua_State, -1))
    {
        return defaultValue;
    }
    int ret = lua_tointeger(_lua_State, -1);
    lua_pop(_lua_State, 1);
    return ret;
}

double Script::get(const std::string& name, double defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isnumber(_lua_State, -1))
    {
        return defaultValue;
    }
    double ret = lua_tonumber(_lua_State, -1);
    lua_pop(_lua_State, 1);
    return ret;
}

std::string Script::get(const std::string& name, const std::string& defaultValue)
{
    lua_getglobal(_lua_State, name.c_str());
    if (!lua_isstring(_lua_State, -1))
    {
        return defaultValue;
    }
    std::string ret = lua_tostring(_lua_State, -1);
    lua_pop(_lua_State, 1);
    return ret;
}

lua_State* Script::luaState()
{
    return _lua_State;
}

}
}
