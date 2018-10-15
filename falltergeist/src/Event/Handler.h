/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_EVENT_HANDLER_H
#define FALLTERGEIST_EVENT_HANDLER_H

// C++ standard includes

// Falltergeist includes
#include "../Base/Delegate.h"

namespace Falltergeist
{
namespace Event
{
class Event;
class Mouse;
class Keyboard;
class State;

// TODO: copy-pasting Base::Delegate code instead of using template might improve compilation speed

using Handler = Base::Delegate<Event*>;
using MouseHandler = Base::Delegate<Mouse*>;
using KeyboardHandler = Base::Delegate<Keyboard*>;
using StateHandler = Base::Delegate<State*>;

}
}

#endif //FALLTERGEIST_EVENT_HANDLER_H
