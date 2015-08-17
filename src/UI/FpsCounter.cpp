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
#include <sstream>

// Falltergeist includes
#include "../Game/Game.h"
#include "../ResourceManager.h"
#include "../UI/FpsCounter.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

FpsCounter::FpsCounter(int x, int y) : TextArea(x,y)
{
    _lastTicks = SDL_GetTicks();
    setText("0");
    setWidth(40);
    setHorizontalAlign(TextArea::HorizontalAlign::RIGHT);
}

void FpsCounter::think()
{
    if (_lastTicks + 1000 > SDL_GetTicks())
    {
        _frames++;
    }
    else
    {
        setText(std::to_string(_frames));
        _frames = 0;
        _lastTicks = SDL_GetTicks();
    }
}

unsigned int FpsCounter::frames()
{
    return _frames;
}

}
