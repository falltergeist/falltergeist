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

// Third party includes
#include <SDL.h>


namespace Falltergeist
{
namespace Graphics
{

const std::array<unsigned int, 5> AnimatedPalette::_monitorsPalette = {
    0x6B6B6FFF,
    0x63677FFF,
    0x576B8FFF,
    0x0093A3FF,
    0x6BBBFFFF
};

const std::array<unsigned int, 4> AnimatedPalette::_slimePalette = {
    0x006C00FF,
    0x0B7307FF,
    0x1B7B0FFF,
    0x2B831BFF
};

const std::array<unsigned int, 6> AnimatedPalette::_shorePalette = {
    0x533F2BFF,
    0x4B3B2BFF,
    0x433727FF,
    0x3F3327FF,
    0x372F23FF,
    0x332B23FF
};

const std::array<unsigned int, 5> AnimatedPalette::_fireSlowPalette = {
    0xFF0000FF,
    0xD70000FF,
    0x932B0BFF,
    0xFF7700FF,
    0xFF3B00FF
};

const std::array<unsigned int, 5> AnimatedPalette::_fireFastPalette = {
    0x470000FF,
    0x7B0000FF,
    0xB30000FF,
    0x7B0000FF,
    0x470000FF
};

AnimatedPalette::AnimatedPalette()
{
}

AnimatedPalette::~AnimatedPalette()
{
}

unsigned int AnimatedPalette::color(unsigned char index, unsigned char counter)
{
    if (index >= 233 && index <= 237) // monitors
    {
        unsigned int newIndex = (index - 233 + counter) % _monitorsPalette.size();
        return _monitorsPalette[newIndex];
    }

    if (index >= 229 && index <= 232) // slime
    {
        unsigned int newIndex = (index - 229 + counter) % _slimePalette.size();
        return _slimePalette[newIndex];
    }

    if (index >= 248 && index <= 253) // shore
    {
        unsigned int newIndex = (index - 248 + counter) % _shorePalette.size();
        return _shorePalette[newIndex];
    }

    if (index >= 238 && index <= 242) // slow fire
    {
        unsigned int newIndex = (index - 238 + counter) % _fireSlowPalette.size();
        return _fireSlowPalette[newIndex];
    }

    if (index >= 243 && index <= 247) // fast fire
    {
        unsigned int newIndex = (index - 243 + counter) % _fireFastPalette.size();
        return _fireFastPalette[newIndex];
    }

    if (index == 254) // blinking red
    {
        return ((((counter*4)) << 24)) | 0x000000FF;
    }

    return 0x00000000;
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
        if (_shoreCounter >= 6) _slimeCounter = 0;
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

}
}
