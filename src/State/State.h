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

#ifndef FALLTERGEIST_STATE_H
#define FALLTERGEIST_STATE_H

// C++ standard includes
#include <map>
#include <memory>
#include <vector>

// Falltergeist includes
#include "../Event/MouseEvent.h"
#include "../Event/KeyboardEvent.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{
    class Game;
}
class ActiveUI;
class Event;
class ImageList;
class SmallCounter;
class StateEvent;
class Surface;
class TextArea;
class UI;

namespace State
{

class State : public EventEmitter
{
protected:
    std::vector<UI*> _ui;
    std::vector<UI*> _uiToDelete;
    std::map<std::string, UI*> _labeledUI;

    int _x = 0;
    int _y = 0;

    // prevents all states before this one to call think() method
    bool _modal = false;
    bool _active = false;
    // prevents render all states before this one
    bool _fullscreen = true;
    bool _initialized = false;
public:
    State();
    virtual ~State();

    ActiveUI* addUI(ActiveUI* ui);
    UI* addUI(UI* ui);
    ActiveUI* addUI(const std::string& name, ActiveUI* ui);
    UI* addUI(const std::string& name, UI* ui);
    void addUI(std::vector<UI*> uis);
    void popUI();

    UI* getUI(const std::string& name);
    ActiveUI* getActiveUI(const std::string& name);
    TextArea* getTextArea(const std::string& name);
    ImageList* getImageList(const std::string& name);
    SmallCounter* getSmallCounter(const std::string& name);

    int x();
    void setX(int x);

    int y();
    void setY(int y);

    virtual bool fullscreen();
    virtual void setFullscreen(bool value);

    virtual bool modal();
    virtual void setModal(bool value);

    virtual bool active();
    virtual void setActive(bool value);

    virtual bool initialized();
    virtual void init();

    virtual void think();
    virtual void handle(Event* event);
    virtual void render();

    virtual void onStateActivate(StateEvent* event);
    virtual void onStateDeactivate(StateEvent* event);
    virtual void onKeyDown(KeyboardEvent* event);
};

}
}

#endif // FALLTERGEIST_STATE_H
