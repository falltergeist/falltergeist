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
#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Exception.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Point.h"
#include "../Input/Mouse.h"
#include "../Lua/Binder.h"
#include "../Lua/ImageButton.h"
#include "../Lua/LuabridgeStack.h"
#include "../Lua/TextArea.h"
#include "../Lua/Script.h"
#include "../State/Credits.h"
#include "../State/LoadGame.h"
#include "../State/LuaState.h"
#include "../State/Movie.h"
#include "../State/NewGame.h"
#include "../State/SettingsMenu.h"
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

/*void setState(State::State* state)
{
    Game::getInstance()->setState(state);
}*/

State::State* pushState(luabridge::LuaRef table)
{
    auto state = new State::LuaState(table);
    Game::getInstance()->pushState(state);
    return state;
}

void popState()
{
    Game::getInstance()->popState();
}

void quit()
{
    Game::getInstance()->quit();
}

template<class RetT, class ...T>
RetT* constructUi(State::State* state, T... args)
{
    RetT* obj = new RetT(args...);
    state->addUI(obj);
    return obj;
}

std::string _t(size_t msg, size_t number)
{
    return Falltergeist::_t((MSG_TYPE)msg, number);
}

void Binder::bindAll()
{
    _gameNamespace()
        //.addFunction("setState", setState)
        .addFunction("pushState", pushState)
        .addFunction("popState", popState)
        .addFunction("quit", quit)

        // game.translate
        .addFunction("translate", translate)
        // game._t
        .addFunction("_t", _t)

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

        // game.mixer
        .addProperty<Audio::Mixer*,void*>("mixer", []()
        {
            return Game::getInstance()->mixer();
        })
    ;

    _bindBasicClasses();
    _bindEvents();
    _bindStates();
    _bindUI();
    _bindLib();
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

        // game.Renderer
        .beginClass<Graphics::Renderer>("Renderer")
            .addProperty("size", &Graphics::Renderer::size)
            .addFunction("fadeIn", &Graphics::Renderer::fadeIn)
            .addFunction("fadeOut", &Graphics::Renderer::fadeOut)
        .endClass()

        // game.Mixer
        .beginClass<Audio::Mixer>("Mixer")
            .addFunction("stopSounds", &Audio::Mixer::stopSounds)
            .addFunction("stopMusic", &Audio::Mixer::stopMusic)
            .addFunction("pauseMusic", &Audio::Mixer::pauseMusic)
            .addFunction("resumeMusic", &Audio::Mixer::resumeMusic)
            .addFunction("playACMMusic", &Audio::Mixer::playACMMusic)
            .addFunction("playACMSound", &Audio::Mixer::playACMSound)
            // .addFunction("playMovieMusic", &Audio::Mixer::playMovieMusic)
        .endClass()
    ;
}

void Binder::_bindEvents()
{
    _gameNamespace()
        .beginNamespace("event")
            // game.Event
            .beginClass<Event::Event>("Event")
                .addProperty("name", &Event::Event::name, &Event::Event::setName)
            .endClass()
            .deriveClass<Event::Keyboard, Event::Event>("Keyboard")
                .addProperty("controlPressed", &Event::Keyboard::controlPressed)
                .addProperty("shiftPressed", &Event::Keyboard::shiftPressed)
                .addProperty("altPressed", &Event::Keyboard::altPressed)
                .addProperty("keyCode", &Event::Keyboard::keyCode)
            .endClass()
            .deriveClass<Event::State, Event::Event>("State")
            .endClass()
        .endNamespace()
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
                .addFunction<void(UI::Base::*)(const std::string&, std::function<void(Event::Event*)>)>("addEventHandler", &UI::Base::addEventHandler)
                .addFunction<void(UI::Base::*)(const std::string&)>("removeEventHandlers", &UI::Base::removeEventHandlers)
            .endClass()

            // game.ui.Image
            .deriveClass<UI::Image, UI::Base>("Image")
                .addStaticFunction("new", static_cast<UI::Image*(*)(State::State* state, const std::string& filename)>(&constructUi))
            .endClass()

            // game.ui.ImageButton
            .deriveClass<UI::ImageButton, UI::Base>("ImageButtonBase")
            .endClass()

            .deriveClass<Lua::ImageButton, UI::ImageButton>("ImageButton")
                //.addConstructor<void(*)(const std::string&, const std::string&, const std::string&, const std::string&, int, int)>()
                .addStaticFunction("new", static_cast<Lua::ImageButton*(*)(State::State*, const std::string&, const std::string&, const std::string&, const std::string&, int, int)>(&constructUi))
                .addFunction("subclass", &Lua::ImageButton::subclass)
            .endClass()

            // game.ui.TextArea
            .deriveClass<Lua::TextArea, UI::Base>("TextArea")
                .addStaticFunction("new", static_cast<Lua::TextArea*(*)(State::State*, const std::string&, int, int)>(&constructUi))
                .addProperty<Size, const Size&>
                    ("size", &TextArea::size, &TextArea::setSize)
                .addProperty<std::string, const std::string&>
                    ("text", &TextArea::text, &TextArea::setText)
                .addProperty
                    ("horizontalAlign", &Lua::TextArea::luaHorizontalAlign, &Lua::TextArea::setLuaHorizontalAlign)
                .addFunction("setFont", static_cast<void(Lua::TextArea::*)(const std::string&, unsigned int)>(&UI::TextArea::setFont))
            .endClass()
    ;
}

void Binder::_bindStates()
{
    _gameNamespace()
        .beginNamespace("state")
            .beginClass<State::State>("Base")
                .addProperty("position", &State::State::position, &State::State::setPosition)
                .addProperty("fullscreen", &State::State::fullscreen, &State::State::setFullscreen)
                .addProperty("modal", &State::State::modal, &State::State::setModal)
                .addFunction<void(State::State::*)(const std::string&, std::function<void(Event::Event*)>)>("addEventHandler", &State::State::addEventHandler)
                .addFunction<void(State::State::*)(const std::string&)>("removeEventHandlers", &State::State::removeEventHandlers)
            .endClass()
            // game.state.State
            .deriveClass<State::LuaState, State::State>("State")
                //.addConstructor<void(*)(luabridge::LuaRef)>()
                .addStaticFunction("pushNew", static_cast<State::LuaState*(*)(luabridge::LuaRef)>(&State::LuaState::pushNew))
                //.addFunction("addUI", &State::LuaState::addUI)
            .endClass()
            .deriveClass<State::NewGame, State::State>("NewGame")
                .addStaticFunction("pushNew", static_cast<State::NewGame*(*)()>(&State::LuaState::pushNew))
            .endClass()
            .deriveClass<State::Credits, State::State>("Credits")
                .addStaticFunction("pushNew", static_cast<State::Credits*(*)()>(&State::LuaState::pushNew))
            .endClass()
            .deriveClass<State::LoadGame, State::State>("LoadGame")
                .addStaticFunction("pushNew", static_cast<State::LoadGame*(*)()>(&State::LuaState::pushNew))
            .endClass()
            .deriveClass<State::Movie, State::State>("Movie")
                .addStaticFunction("pushNew", static_cast<State::Movie*(*)(int)>(&State::LuaState::pushNew))
            .endClass()
            .deriveClass<State::SettingsMenu, State::State>("SettingsMenu")
                .addStaticFunction("pushNew", static_cast<State::SettingsMenu*(*)()>(&State::LuaState::pushNew))
            .endClass()
        .endNamespace()
    ;
}

void Binder::_bindLib()
{
    // TODO?
}

}
}

