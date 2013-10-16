/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#ifndef FALLTERGEIST_IMAGEBUTTON_H
#define FALLTERGEIST_IMAGEBUTTON_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"

// Third party includes

namespace Falltergeist
{

class ImageButton : public InteractiveSurface
{
protected:
    char * _releasedImage;
    char * _pressedImage;
public:
    ImageButton(const char * releasedImage = 0, const char * pressedImage = 0, int x = 0, int y = 0);
    virtual void draw();
    void setReleasedImage(const char * releasedImage);
    void setPressedImage(const char * pressedImage);
    void mouseInHandler(Event * event);
    void mouseOutHandler(Event * event);
    void mouseDownHandler(Event * event);
    void mouseUpHandler(Event * event);

};

}
#endif // FALLTERGEIST_IMAGEBUTTON_H
