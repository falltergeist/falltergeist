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
#include <map>
#include <memory>
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
    std::vector<std::shared_ptr<UI>> _ui;
    std::map<std::string, std::shared_ptr<UI>> _labeledUI;

    int _x = 0;
    int _y = 0;

    // prevents all states before this one to call think() method
    bool _modal = false;
    // prevents render all states before this one
    bool _fullscreen = true;
    bool _initialized = false;
public:
    State();
    virtual ~State();

    std::shared_ptr<UI> addUI(std::shared_ptr<UI> ui);
    std::shared_ptr<UI> addUI(std::string name, std::shared_ptr<UI> ui);
    void addUI(std::vector<std::shared_ptr<UI>> uis);

    std::shared_ptr<UI> getUI(std::string name);

    int x();
    void setX(int x);

    int y();
    void setY(int y);

    virtual bool fullscreen();
    virtual void setFullscreen(bool value);

    virtual bool modal();
    virtual void setModal(bool value);

    virtual bool initialized();
    virtual void init();
    virtual void think();
    virtual void handle(std::shared_ptr<Event> event);
    std::vector<std::shared_ptr<UI>>* ui();
};

}
#endif // FALLTERGEIST_STATE_H
