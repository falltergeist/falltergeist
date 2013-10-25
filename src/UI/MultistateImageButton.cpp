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

// C++ standard includes

// Falltergeist includes
#include "../UI/MultistateImageButton.h"
#include "../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

MultistateImageButton::MultistateImageButton(int x, int y) : InteractiveSurface(0, 0, x, y)
{
}

MultistateImageButton::MultistateImageButton(unsigned int type, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    Surface * surface;
    switch (type)
    {
        case BUTTON_BIG_SWITCH:
            surface = ResourceManager::surface("art/intrface/prfbknbs.frm");
            addSurface(surface->crop(0, 47*0, 46, 47));
            addSurface(surface->crop(0, 47*1, 46, 47));
            addSurface(surface->crop(0, 47*2, 46, 47));
            addSurface(surface->crop(0, 47*3, 46, 47));
            break;
        case BUTTON_SMALL_SWITCH:
            surface = ResourceManager::surface("art/intrface/prflknbs.frm");
            addSurface(surface->crop(0, 0, 22, 25));
            addSurface(surface->crop(0, 25, 22, 50));
            break;
        default:
            throw Exception("MultistateImageButton::MultistateImageButton(unsigned int type, x, y) - unsupported type");
    }
}


MultistateImageButton::MultistateImageButton(SurfaceSet surfaceSet, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    for (auto surface : *surfaceSet.surfaces()) _surfaceSet.addSurface(surface);
}

MultistateImageButton::MultistateImageButton(SurfaceSet* surfaceSet, int x, int y) : InteractiveSurface(0, 0, x, y)
{
    for (auto surface : *surfaceSet->surfaces()) _surfaceSet.addSurface(surface);
}


MultistateImageButton::~MultistateImageButton()
{
}

void MultistateImageButton::addSurface(Surface* surface)
{
    _surfaceSet.addSurface(surface);
}

int MultistateImageButton::state()
{
    return _currentState;
}

void MultistateImageButton::setState(int state)
{
    _currentState = state;
}

void MultistateImageButton::setMode(int mode)
{
    switch(mode)
    {
        case MODE_CYCLIC:
        case MODE_PROGRESSION:
                break;
        default:
            throw Exception("MultistateImageButton::setMode(int) - wrong mode number: " + std::to_string(mode));
    }
    _mode = mode;    
}

int MultistateImageButton::mode()
{
    return _mode;
}

void MultistateImageButton::leftButtonClick(Event* event, State* state)
{
    if (mode() == MODE_PROGRESSION)
    {
        if (modeFactor() > 0)
        {
            _currentState = (_currentState < _surfaceSet.surfaces()->size() - 1) ? _currentState + modeFactor() : 0;
        }
        else
        {
            _currentState = (_currentState > 0) ? _currentState + modeFactor() : _surfaceSet.surfaces()->size() - 1;
        }
    }        
    else // MODE_CYCLIC
    {
        if (modeFactor() > 0)
        {
            if (_currentState == _surfaceSet.surfaces()->size() - 1) setModeFactor(-modeFactor());
        }
        else
        {
            if (_currentState == 0) setModeFactor(-modeFactor());
        }
        _currentState += modeFactor();
    }
    InteractiveSurface::leftButtonClick(event, state);
}

SDL_Surface* MultistateImageButton::sdl_surface()
{
    return _surfaceSet.surfaces()->at(_currentState)->sdl_surface();
}

void MultistateImageButton::setModeFactor(int factor)
{
    _modeFactor = factor;
}

int MultistateImageButton::modeFactor()
{
    if (_modeFactor >= 0) return 1;
    return -1;
}

void MultistateImageButton::setMaxState(int value)
{
    _maxState = value;
}

int MultistateImageButton::maxState()
{
    return _maxState;
}

void MultistateImageButton::setMinState(int value)
{
    _minState = value;
}

int MultistateImageButton::minState()
{
    return _minState;
}


}
