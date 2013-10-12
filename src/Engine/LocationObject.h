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
 *
 */

#ifndef FALLTERGEIST_LOCATIONOBJECT_H
#define FALLTERGEIST_LOCATIONOBJECT_H

#include "../Engine/InteractiveSurface.h"

namespace Falltergeist
{
class Animation;

class LocationObject : public InteractiveSurface
{
protected:
    unsigned int _objectId;
    unsigned int _objectTypeId;
    unsigned int _descriptionId;
    Animation * _animation;

public:
    LocationObject(int x = 0, int y = 0);
    ~LocationObject();

    virtual SDL_Surface * sdl_surface();

    std::string name();
    std::string description();

    void setObjectId(unsigned int value);
    unsigned int objectId();
    void setObjectTypeId(unsigned int value);
    unsigned int objectTypeId();
    void setDescriptionId(unsigned int value);
    unsigned int descriptionId();
    Animation * animation();
    void setAnimation(Animation * animation);

    int x();
    int y();
    void x(int x);
    void y(int y);
    virtual void think();
};

}

#endif // FALLTERGEIST_LOCATIONOBJECT_H
