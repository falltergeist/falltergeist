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

#ifndef FALLTERGEIST_GRAPHICS_ANIMATEDPALETTE_H
#define FALLTERGEIST_GRAPHICS_ANIMATEDPALETTE_H

// C++ standard includes
#include <array>
#include <vector>

// Falltergeist includes
#include "../Format/Enums.h"
#include "../Graphics/Renderer.h"

// Third party includes
#include <glm/glm.hpp>

namespace Falltergeist
{
namespace Graphics
{

class AnimatedPalette
{
public:
    AnimatedPalette();
    ~AnimatedPalette();

    std::vector<GLuint> counters();
    void think();

protected:

    unsigned int _slimeTicks = 0;
    unsigned int _slimeCounter = 0;
    unsigned int _fireSlowTicks = 0;
    unsigned int _fireSlowCounter = 0;
    unsigned int _fireFastTicks = 0;
    unsigned int _fireFastCounter = 0;
    unsigned int _monitorsTicks = 0;
    unsigned int _monitorsCounter = 0;
    unsigned int _shoreTicks = 0;
    unsigned int _shoreCounter = 0;
    unsigned int _blinkingRedTicks = 0;
    unsigned char _blinkingRedCounter = 0;
    short _blinkingRed = -1;
};

}
}
#endif // FALLTERGEIST_GRAPHICS_ANIMATEDPALETTE_H
