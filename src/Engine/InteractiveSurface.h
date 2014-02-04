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

#ifndef FALLTERGEIST_INTERACTIVESURFACE_H
#define FALLTERGEIST_INTERACTIVESURFACE_H

// C++ standard includes

// Falltergeist includes
#include "../Engine/Surface.h"
#include "../Engine/Event/Event.h"
#include "../Engine/Event/EventReciever.h"
#include "../Engine/Event/EventEmitter.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Event/KeyboardEvent.h"


// Third party includes

namespace Falltergeist
{

class InteractiveSurface : public EventReciever, public EventEmitter, public Surface
{
protected:
    bool _hovered = false;
    bool _drag = false;
    bool _leftButtonPressed = false;
    bool _rightButtonPressed = false;
public:
    InteractiveSurface(libfalltergeist::FrmFileType* frm, unsigned int direction = 0, unsigned int frame = 0);
    InteractiveSurface(int width = 0, int height = 0, int x = 0, int y = 0);
    InteractiveSurface(Surface* other);
    virtual ~InteractiveSurface();
    virtual void handle(Event* event);
};

}
#endif // FALLTERGEIST_INTERACTIVESURFACE_H
