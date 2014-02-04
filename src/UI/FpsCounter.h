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

#ifndef FALLTERGEIST_FPSCOUNTER_H
#define FALLTERGEIST_FPSCOUNTER_H

// C++ standard includes

// Falltergeist includes
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

class FpsCounter : public TextArea
{
protected:
    unsigned int _lastTicks;
    unsigned int _frames;
public:
    FpsCounter(int x = 598, int y = 2);

    virtual void think();
    unsigned int frames();
};

}
#endif // FALLTERGEIST_FPSCOUNTER_H
