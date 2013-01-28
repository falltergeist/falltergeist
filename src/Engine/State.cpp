/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#include "../Engine/State.h"
#include "../Engine/Surface.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/InteractiveSurface.h"

namespace Falltergeist
{

State::State(Game * game) : _game(game), _surfaces(), _isFullscreen(false), initialized(false)
{
}

State::~State()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        delete *i;
    }
}

void State::init()
{
    initialized = true;
}

void State::think()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->think();
    }
}

void State::blit()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->blit(_game->screen()->surface());
    }
}

bool State::isFullscreen()
{
    return _isFullscreen;
}

void State::add(Surface * surface)
{
    _surfaces.push_back(surface);
}

void State::handle(Event * event)
{
    for (std::vector<Surface *>::reverse_iterator i = _surfaces.rbegin(); i < _surfaces.rend(); i++)
    {
        InteractiveSurface * surface = dynamic_cast<InteractiveSurface *>(*i);
        if (surface != 0)
        {
            surface->handle(event,this);
        }
    }
}

}
