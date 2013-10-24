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

#ifndef FALLTERGEIST_MULTISTATEIMAGEBUTTON_H
#define	FALLTERGEIST_MULTISTATEIMAGEBUTTON_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"

// Third party includes

namespace Falltergeist
{

class MultistateImageButton : public InteractiveSurface
{
protected:
    std::vector<Surface*> _states;
    unsigned int _currentState = 0;
    int _mode = MODE_PROGRESSION;
    int _modeFactor = 1; // or -1
public:
    enum {MODE_PROGRESSION = 1, MODE_CYCLIC};
    MultistateImageButton(int x = 0, int y = 0);
    virtual ~MultistateImageButton();
    virtual void leftButtonClick(Event* event, State* state);
    void addState(Surface * surface);
    int state();
    void setMode(int mode);    
    int mode();
    void setModeFactor(int factor);
    int modeFactor();
    virtual SDL_Surface* sdl_surface();
};

}
#endif	/* FALLTERGEIST_MULTISTATEIMAGEBUTTON_H */

