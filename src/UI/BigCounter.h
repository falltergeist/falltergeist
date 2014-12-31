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

#ifndef FALLTERGEIST_BIGCOUNTER_H
#define FALLTERGEIST_BIGCOUNTER_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Graphics/ActiveUI.h"

// Third party includes

namespace Falltergeist
{
class Image;

class BigCounter : public ActiveUI
{
protected:
    unsigned char _color = COLOR_WHITE;
    unsigned int _number = 0;
    unsigned int _length = 2;
public:
    enum {COLOR_WHITE = 1, COLOR_RED};
    BigCounter(int x = 0, int y = 0);
    ~BigCounter();

    virtual Texture* texture();

    void setColor(unsigned char color);
    unsigned char color();

    void setNumber(unsigned int number);
    unsigned int number();
};

}
#endif // FALLTERGEIST_BIGCOUNTER_H
