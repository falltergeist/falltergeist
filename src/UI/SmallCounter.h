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

#ifndef FALLTERGEIST_SMALLCOUNTER_H
#define FALLTERGEIST_SMALLCOUNTER_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
class Image;

class SmallCounter : public ActiveUI
{
protected:
    unsigned char _color = COLOR_WHITE;
    signed int _number = 0;
    unsigned int _length = 3;
public:
    enum {COLOR_WHITE = 1, COLOR_YELLOW, COLOR_RED};
    SmallCounter(int x = 0, int y = 0);
    ~SmallCounter();

    virtual std::shared_ptr<Texture> texture();

    void setColor(unsigned char color);
    unsigned char color();

    void setNumber(signed int number);
    signed int number();
};

}
#endif // FALLTERGEIST_SMALLCOUNTER_H
