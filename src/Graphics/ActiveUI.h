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

#ifndef FALLTERGEIST_ACTIVEUI_H
#define FALLTERGEIST_ACTIVEUI_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Event/Event.h"
#include "../Event/MouseEvent.h"
#include "../Event/KeyboardEvent.h"
#include "../Graphics/UI.h"

// Third party includes

namespace Falltergeist
{

class ActiveUI : public EventEmitter, public UI
{
public:
    ActiveUI(int x = 0, int y = 0);
    virtual ~ActiveUI();

    virtual void handle(Event* event);
    static void export_to_lua_script(Lua::Script* script);

protected:
    std::string _downSnd = "";
    std::string _upSnd = "";
};

}
#endif // FALLTERGEIST_ACTIVEUI_H
