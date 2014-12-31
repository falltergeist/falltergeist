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
#include "../Event/StateEvent.h"
#include "../Game/Game.h"
#include "../Graphics/ActiveUI.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/UI.h"
#include "State.h"
#include "../UI/ImageList.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

State::State() : EventEmitter()
{
    addEventHandler("activate",   [this](Event* event){ this->onStateActivate(dynamic_cast<StateEvent*>(event)); });
    addEventHandler("deactivate", [this](Event* event){ this->onStateDeactivate(dynamic_cast<StateEvent*>(event)); });
}

State::~State()
{
    for (auto ui : _ui)
    {
        delete ui;
    }
}

void State::init()
{
    _initialized = true;
}

void State::think()
{
    for (auto ui : _ui)
    {
        ui->think();
    }
}

int State::x()
{
    return _x;
}

void State::setX(int x)
{
    _x = x;
}

int State::y()
{
    return _y;
}

void State::setY(int y)
{
    _y = y;
}

bool State::initialized()
{
    return _initialized;
}

bool State::fullscreen()
{
    return _fullscreen;
}

void State::setFullscreen(bool value)
{
    _fullscreen = value;
}

bool State::modal()
{
    return _modal;
}

void State::setModal(bool value)
{
    _modal = value;
}

ActiveUI* State::addUI(ActiveUI* ui)
{
    addUI((UI*)ui);
    return ui;
}

UI* State::addUI(UI* ui)
{
    // Add to UI state position
    if (x()) ui->setX(ui->x() + x());
    if (y()) ui->setY(ui->y() + y());

    _ui.push_back(ui);
    return ui;
}

UI* State::addUI(std::string name, UI* ui)
{
    addUI(ui);
    _labeledUI.insert(std::pair<std::string, UI*>(name, ui));
    return ui;
}

ActiveUI* State::addUI(std::string name, ActiveUI* ui)
{
    addUI(name, (UI*)ui);
    return ui;
}


void State::addUI(std::vector<UI*> uis)
{
    for (auto ui : uis)
    {
        addUI(ui);
    }
}

ActiveUI* State::getActiveUI(std::string name)
{
    return dynamic_cast<ActiveUI*>(getUI(name));
}

TextArea* State::getTextArea(std::string name)
{
    return dynamic_cast<TextArea*>(getUI(name));
}

ImageList* State::getImageList(std::string name)
{
    return dynamic_cast<ImageList*>(getUI(name));
}

SmallCounter* State::getSmallCounter(std::string name)
{
    return dynamic_cast<SmallCounter*>(getUI(name));
}

UI* State::getUI(std::string name)
{
    if (_labeledUI.find(name) != _labeledUI.end())
    {
        return _labeledUI.at(name);
    }
    return nullptr;
}

void State::handle(Event* event)
{
    for (auto it = _ui.rbegin(); it != _ui.rend(); ++it)
    {
        if (event->handled()) return;
        if (auto activeUI = dynamic_cast<ActiveUI*>(*it))
        {
            activeUI->handle(event);
        }
    }
}

void State::render()
{
    for (auto it = _ui.begin(); it != _ui.end(); ++it)
    {
        if ((*it)->visible())
        {
            (*it)->render();
        }
    }
    while (!_uiToDelete.empty())
    {
        delete _uiToDelete.back();
        _uiToDelete.pop_back();
    }
}

void State::popUI()
{
    if (_ui.size() == 0) return;
    _uiToDelete.push_back(_ui.back());
    _ui.pop_back();
}

void State::onStateActivate(StateEvent* event)
{
}

void State::onStateDeactivate(StateEvent* event)
{
}

bool State::active()
{
    return _active;
}

void State::setActive(bool value)
{
    _active = value;
}

}
}
