/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef FALLTERGEIST_STATE_H
#define FALLTERGEIST_STATE_H

// C++ standard includes
#include <vector>
#include <memory>

// Falltergeist includes
#include "../Engine/Event/EventReciever.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Event/KeyboardEvent.h"

// Third party includes

namespace Falltergeist
{
class Game;
class Surface;
class Event;
class UI;
class ActiveUI;

class State : public EventReciever
{
protected:
    std::vector<std::shared_ptr<UI>> _ui;

    bool _fullscreen = true;
    bool _initialized = false;
public:
    State();
    virtual ~State();

    void add(std::shared_ptr<UI> ui);
    void add(std::vector<std::shared_ptr<UI>> uis);
    bool fullscreen();
    void setFullscreen(bool value);
    bool initialized();
    virtual void init();
    virtual void think();
    virtual void handle(std::shared_ptr<Event> event);
    std::vector<std::shared_ptr<UI>>* ui();
};

}
#endif // FALLTERGEIST_STATE_H
