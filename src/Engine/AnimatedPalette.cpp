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

// C++ standard includes
#include <iostream>

// Falltergeist includes
#include "../Engine/AnimatedPalette.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{

AnimatedPalette::AnimatedPalette()
{
    _monitorsPalette = new unsigned int[5];
    _monitorsPalette[0] = 0xFF6B6B6F; _monitorsPalette[1] = 0xFF63677F; _monitorsPalette[2] = 0xFF576B8F; _monitorsPalette[3] = 0xFF0093A3; _monitorsPalette[4] = 0xFF6BBBFF;
    _monitorsCounter = 0;
    _monitorsTicks = 0;

    _slimePalette = new unsigned int[4];
    _slimePalette[0] = 0xFF006C00; _slimePalette[1] = 0xFF0B7307; _slimePalette[2] = 0xFF1B7B0F; _slimePalette[3] = 0xFF2B831B;
    _slimeCounter = 0;
    _slimeTicks = 0;

    _shorePalette = new unsigned int[6];
    _shorePalette[0] = 0xFF533F2B; _shorePalette[1] = 0xFF4B3B2B; _shorePalette[2] = 0xFF433727; _shorePalette[3] = 0xFF3F3327; _shorePalette[4] = 0xFF372F23; _shorePalette[5] = 0xFF332B23;
    _shoreCounter = 0;
    _shoreTicks = 0;

    _fireSlowPalette = new unsigned int[5];
    _fireSlowPalette[0] = 0xFFFF0000; _fireSlowPalette[1] = 0xFFD70000; _fireSlowPalette[2] = 0xFF932B0B; _fireSlowPalette[3] = 0xFFFF7700; _fireSlowPalette[4] = 0xFFFF3B00;
    _fireSlowCounter = 0;
    _fireSlowTicks = 0;

    _fireFastPalette = new unsigned int[5];
    _fireFastPalette[0] = 0xFF470000; _fireFastPalette[1] = 0xFF7B0000; _fireFastPalette[2] = 0xFFB30000; _fireFastPalette[3] = 0xFF7B0000; _fireFastPalette[4] = 0xFF470000;
    _fireFastCounter = 0;
    _fireFastTicks = 0;

    _blinkingRed = 252;
    _blinkingRedTicks = 0;
    _blinkingRedCounter = 0;
}

AnimatedPalette::~AnimatedPalette()
{
    delete [] _monitorsPalette;
    delete [] _slimePalette;
    delete [] _shorePalette;
    delete [] _fireSlowPalette;
    delete [] _fireFastPalette;
}


void AnimatedPalette::think()
{
    if (_monitorsTicks + 100 < SDL_GetTicks())
    {
        _monitorsTicks = SDL_GetTicks();

        _monitorsCounter++;
        if (_monitorsCounter == 5) _monitorsCounter = 0;
    }

    if (_slimeTicks + 200 < SDL_GetTicks())
    {
        _slimeTicks = SDL_GetTicks();

        _slimeCounter++;
        if (_slimeCounter == 4) _slimeCounter = 0;
    }

    if (_shoreTicks + 200 < SDL_GetTicks())
    {
        _shoreTicks = SDL_GetTicks();

        _shoreCounter++;
        if (_shoreCounter == 6) _slimeCounter = 0;
    }

    if (_fireSlowTicks + 200 < SDL_GetTicks())
    {
        _fireSlowTicks = SDL_GetTicks();

        _fireSlowCounter++;
        if (_fireSlowCounter == 5) _fireSlowCounter = 0;
    }

    if (_fireFastTicks + 142 < SDL_GetTicks())
    {
        _fireFastTicks = SDL_GetTicks();

        _fireFastCounter++;
        if (_fireFastCounter == 5) _fireFastCounter = 0;
    }

    if (_blinkingRedTicks + 33 < SDL_GetTicks())
    {
        _blinkingRedTicks = SDL_GetTicks();

        if ((_blinkingRedCounter == 0) || (_blinkingRedCounter == 60))
        {
          _blinkingRed = -_blinkingRed;
        }

         _blinkingRedCounter = _blinkingRed + _blinkingRedCounter;
    }

}

unsigned int AnimatedPalette::color(unsigned char index)
{
    if (index >= 233 && index <= 237) // monitors
    {
        unsigned int newIndex = (index - 233 + _monitorsCounter)%5;
        return _monitorsPalette[newIndex];
    }

    if (index >= 229 && index <= 232) // slime
    {
        unsigned int newIndex = (index - 229 + _slimeCounter)%4;
        return _slimePalette[newIndex];
    }

    if (index >= 248 && index <= 253) // shore
    {
        unsigned int newIndex = (index - 248 + _shoreCounter)%6;
        return _shorePalette[newIndex];
    }

    if (index >= 238 && index <= 242) // slow fire
    {
        unsigned int newIndex = (index - 348 + _fireSlowCounter)%5;
        return _fireSlowPalette[newIndex];
    }

    if (index >= 243 && index <= 247) // fast fire
    {
        unsigned int newIndex = (index - 243 + _fireFastCounter)%5;
        return _fireFastPalette[newIndex];
    }

    if (index == 254) // blinking red
    {
        return (0x00FF0000 && ((_blinkingRed + _blinkingRedCounter) << 16)) | 0xFF000000;
    }

    return 0xFF00FF00;
}


}
