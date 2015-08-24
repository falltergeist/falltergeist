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

#ifndef FALLTERGEIST_EVENT_EMITTER_H
#define FALLTERGEIST_EVENT_EMITTER_H

// C++ standard includes
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Event
{
class Event;

class Emitter
{
protected:
    std::unordered_map<std::string, std::vector<std::function<void(Event*)>>> _eventHandlers;
public:
    Emitter();
    virtual ~Emitter();

    void addEventHandler(const std::string& eventName, std::function<void(Event*)> handler);
    void emitEvent(Event* event);
    void processEvent(Event* event);
    void removeEventHandlers(const std::string& eventName);
};

}
}
#endif // FALLTERGEIST_EVENT_EMITTER_H
