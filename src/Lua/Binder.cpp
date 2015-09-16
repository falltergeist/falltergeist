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

// Libfalltergeist includes
#include "../Event/Event.h"
#include "../Exception.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Point.h"
#include "../Input/Mouse.h"
#include "../Lua/Binder.h"
#include "../Lua/ImageButton.h"
#include "../Lua/TextArea.h"
#include "../Lua/Script.h"
#include "../State/LuaState.h"
#include "../UI/Image.h"

// Third party includes

using namespace luabridge;

namespace Falltergeist
{
namespace Lua
{

Binder::Binder(lua_State* luaState)
    : _luaState(luaState)
{
}

Binder::~Binder()
{
}

luabridge::Namespace Binder::_gameNamespace()
{
    return luabridge::getGlobalNamespace(_luaState).beginNamespace("game");
}

void setState(State::State* state)
{
    Game::getInstance()->setState(state);
}

void pushState(State::State* state)
{
    Game::getInstance()->pushState(state);
}

void popState()
{
    Game::getInstance()->popState();
}

void quit()
{
    Game::getInstance()->quit();
}

void Binder::bindAll()
{
    _gameNamespace()
        .addFunction("setState", setState)
        .addFunction("pushState", pushState)
        .addFunction("popState", popState)
        .addFunction("quit", quit)

        // game.translate
        .addFunction("translate", translate)

        // game.mouse
        .addProperty<Input::Mouse*,void*>("mouse", []() -> Input::Mouse*
        {
            return Game::getInstance()->mouse();
        })

        // game.renderer
        .addProperty<Graphics::Renderer*,void*>("renderer", []() -> Graphics::Renderer*
        {
            return Game::getInstance()->renderer();
        })
    ;

    _bindBasicClasses();
    _bindStates();
    _bindUI();
}


void Binder::_bindBasicClasses()
{
    _gameNamespace()
        .beginClass<Point>("Point")
            .addConstructor<void(*)(int, int)>()
            .addProperty("x", &Point::x, &Point::setX)
            .addProperty("y", &Point::y, &Point::setY)
            .addFunction("__add", &Point::add)
            .addFunction("__sub", &Point::sub)
            .addFunction("__mul", &Point::mul)
            .addFunction("__div", &Point::div)
        .endClass()

        .beginClass<Size>("Size")
            .addConstructor<void(*)(int, int)>()
            .addProperty("width", &Size::width, &Size::setWidth)
            .addProperty("height", &Size::height, &Size::setHeight)
            .addFunction("__add", &Size::add)
            .addFunction("__sub", &Size::sub)
            .addFunction("__mul", &Size::mul)
            .addFunction("__div", &Size::div)
        .endClass()

        // game.Mouse
        .beginClass<Input::Mouse>("Mouse")
            .addProperty("x", &Input::Mouse::x, &Input::Mouse::setX)
            .addProperty("y", &Input::Mouse::y, &Input::Mouse::setY)
            .addProperty("position", &Input::Mouse::position, &Input::Mouse::setPosition)
            .addProperty("cursor", &Input::Mouse::cursor, &Input::Mouse::setCursor)
        .endClass()

        // game.Mouse
        .beginClass<Graphics::Renderer>("Renderer")
            .addProperty("size", &Graphics::Renderer::size)
            .addFunction("fadeIn", &Graphics::Renderer::fadeIn)
            .addFunction("fadeOut", &Graphics::Renderer::fadeOut)
        .endClass()

        // game.Event
        .beginClass<Event::Event>("Event")
            .addProperty("name", &Event::Event::name, &Event::Event::setName)
        .endClass()
    ;
}

void Binder::_bindUI()
{
    _gameNamespace()
        .beginNamespace("ui")
            // game.ui.UI
            .beginClass<UI::Base>("UI")
                .addProperty("position", &UI::Base::position, &UI::Base::setPosition)
                .addProperty("offset", &UI::Base::offset, &UI::Base::setOffset)
                .addProperty("size", &UI::Base::size)
            .endClass()

            // game.ui.Image
            .deriveClass<UI::Image, UI::Base>("Image")
                .addConstructor<void(*)(char const*)>()
            .endClass()

            // game.ui.ImageButton
            .deriveClass<UI::ImageButton, UI::Base>("ImageButtonBase")
            .endClass()

            .deriveClass<Lua::ImageButton, UI::ImageButton>("ImageButton")
                .addConstructor<void(*)(const std::string&, const std::string&, const std::string&, const std::string&, int, int)>()
                .addFunction("subclass", &Lua::ImageButton::subclass)
            .endClass()

            // game.ui.TextArea
            .deriveClass<Lua::TextArea, UI::Base>("TextArea")
                .addConstructor<void(*)(const char*, int, int)>()
                .addProperty<Size, const Size&>
                    ("size", &TextArea::size, &TextArea::setSize)
                .addProperty<std::string, const std::string&>
                    ("text", &TextArea::text, &TextArea::setText)
                .addProperty
                    ("horizontalAlign", &Lua::TextArea::luaHorizontalAlign, &Lua::TextArea::setLuaHorizontalAlign)
            .endClass()
    ;
}

void Binder::_bindStates()
{
    _gameNamespace()
        // game.State
        .beginClass<State::State>("StateBase")
        .endClass()
        .deriveClass<State::LuaState, State::State>("State")
            .addConstructor<void(*)(luabridge::LuaRef)>()
            .addProperty("position", &State::LuaState::position, &State::LuaState::setPosition)
            .addProperty("fullscreen", &State::LuaState::fullscreen, &State::LuaState::setFullscreen)
            .addProperty("modal", &State::LuaState::modal, &State::LuaState::setModal)
            .addFunction("addUI", &State::LuaState::addUI)
        .endClass()
    ;
}

}
}

