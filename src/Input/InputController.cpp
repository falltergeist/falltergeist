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

// Falltergeist includes
#include "../Input/InputController.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../Lua/Script.h"

// Third party includes

namespace Falltergeist
{

// static
void InputController::exportToLuaScript(Lua::Script* script)
{
    luabridge::getGlobalNamespace(script->luaState())
        .beginNamespace("game")
            .beginClass<InputController>("Input")
                .addProperty("mouseCursor", &InputController::mouseCursorType, &InputController::setMouseCursorType)
            .endClass()
        .endNamespace();
}

InputController::InputController(Mouse* mouse) : _mouse(mouse)
{}

unsigned int InputController::mouseCursorType() const
{
    return _mouse->state();
}

void InputController::setMouseCursorType(unsigned int type)
{
    // Filter only script allowed values.
    if (type != Mouse::BIG_ARROW &&
        type != Mouse::WAIT &&
        type != Mouse::NONE)
        return;

    Logger::debug("INPUT") << "Set mouse cursor to " << type << std::endl;
    _mouse->setState(type);
}
}
