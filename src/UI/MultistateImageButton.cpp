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

MultistateImageButton::~MultistateImageButton()
{
}

void MultistateImageButton::addState(Surface* surface)
{
    _states.push_back(surface);
}

int MultistateImageButton::state()
{
    return _currentState;
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
            if (_currentState < _states.size() - 1)
            {
                _currentState+= modeFactor();
            }
            else
            {
                _currentState = 0;
            }
        }
        else
        {
            if (_currentState > 0)
            {
                _currentState+= modeFactor();
            }
            else
            {
                _currentState = _states.size() - 1;
            }            
        }
    }        
    InteractiveSurface::leftButtonClick(event, state);
}

SDL_Surface* MultistateImageButton::sdl_surface()
{
    return _states.at(_currentState)->sdl_surface();
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

}
