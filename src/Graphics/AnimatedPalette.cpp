/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../Graphics/AnimatedPalette.h"

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Renderer.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{
namespace Graphics
{

AnimatedPalette::AnimatedPalette()
{
}

AnimatedPalette::~AnimatedPalette()
{
}

void AnimatedPalette::think()
{
    if (_monitorsTicks + 100 < SDL_GetTicks())
    {
        _monitorsTicks = SDL_GetTicks();

        _monitorsCounter++;
        if (_monitorsCounter >= 5) _monitorsCounter = 0;
    }

    if (_slimeTicks + 200 < SDL_GetTicks())
    {
        _slimeTicks = SDL_GetTicks();

        _slimeCounter++;
        if (_slimeCounter >= 4) _slimeCounter = 0;
    }

    if (_shoreTicks + 200 < SDL_GetTicks())
    {
        _shoreTicks = SDL_GetTicks();

        _shoreCounter++;
        if (_shoreCounter >= 6) _shoreCounter = 0;
    }

    if (_fireSlowTicks + 200 < SDL_GetTicks())
    {
        _fireSlowTicks = SDL_GetTicks();

        _fireSlowCounter++;
        if (_fireSlowCounter >= 5) _fireSlowCounter = 0;
    }

    if (_fireFastTicks + 142 < SDL_GetTicks())
    {
        _fireFastTicks = SDL_GetTicks();

        _fireFastCounter++;
        if (_fireFastCounter >= 5) _fireFastCounter = 0;
    }

    if (_blinkingRedTicks + 33 < SDL_GetTicks())
    {
        _blinkingRedTicks = SDL_GetTicks();

        if ((_blinkingRedCounter == 0) || (_blinkingRedCounter == 15))
        {
            _blinkingRed = -_blinkingRed;
        }

        _blinkingRedCounter = _blinkingRed + _blinkingRedCounter;
    }
}

std::vector<GLuint> AnimatedPalette::counters() {
    std::vector<GLuint> cnt;
    cnt.reserve(6);
    cnt.push_back(_slimeCounter);
    cnt.push_back(_monitorsCounter);
    cnt.push_back(_fireSlowCounter);
    cnt.push_back(_fireFastCounter);
    cnt.push_back(_shoreCounter);
    cnt.push_back(_blinkingRedCounter);
    return cnt;
}

}
}
