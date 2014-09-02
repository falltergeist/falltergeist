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
    Game* _game;
    std::vector<UI*> _ui;
    std::vector<ActiveUI*> _activeUi;

    bool _fullscreen = true;
    bool _initialized = false;
    bool _scrollable = false;
public:
    State();
    virtual ~State();

    void add(UI* ui);
    void add(ActiveUI* ui);
    void add(std::vector<UI*> uis);
    bool fullscreen();
    void setFullscreen(bool value);
    bool initialized();
    virtual void init();
    virtual void think();
    virtual void handle(Event* event);
    bool scrollable();
    void setScrollable(bool value);
    std::vector<UI*>* ui();
};

}
#endif // FALLTERGEIST_STATE_H
