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

#ifndef FALLTERGEIST_ANIMATEDPALETTE_H
#define FALLTERGEIST_ANIMATEDPALETTE_H

// C++ standard includes

// Falltergeist includes

// Third party includes


namespace Falltergeist
{

class AnimatedPalette
{
protected:
    unsigned int * _slimePalette;
    unsigned int _slimeTicks;
    unsigned int _slimeCounter;

    unsigned int * _fireSlowPalette;
    unsigned int _fireSlowTicks;
    unsigned int _fireSlowCounter;

    unsigned int * _fireFastPalette;
    unsigned int _fireFastTicks;
    unsigned int _fireFastCounter;

    unsigned int * _monitorsPalette;
    unsigned int _monitorsTicks;
    unsigned int _monitorsCounter;

    unsigned int * _shorePalette;
    unsigned int _shoreTicks;
    unsigned int _shoreCounter;

    unsigned char _blinkingRed;
    unsigned int _blinkingRedTicks;
    unsigned char _blinkingRedCounter;

public:
    AnimatedPalette();
    ~AnimatedPalette();
    void think();
    unsigned int color(unsigned char index);
};

}

#endif // FALLTERGEIST_ANIMATEDPALETTE_H
