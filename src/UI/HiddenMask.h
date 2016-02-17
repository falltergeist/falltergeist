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

#ifndef FALLTERGEIST_UI_HIDDENMASK_H
#define FALLTERGEIST_UI_HIDDENMASK_H

// C++ standard includes

// Falltergeist includes
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
namespace UI
{

/**
 * Hidden mask is used to handle events in particular screen area
 * @todo Must be inherited from UI
 */
class HiddenMask : public Base//Image
{

public:
    HiddenMask(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);
    ~HiddenMask() override;

    void render(bool eggTransparency = false) override;

    virtual bool opaque(const Point &pos) override;

    void think() override;
};

}
}
#endif // FALLTERGEIST_UI_HIDDENMASK_H
