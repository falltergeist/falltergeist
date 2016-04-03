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

// Related headers
#include "../Game/SpatialObject.h"

// C++ standard includes

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Logger.h"
#include "../PathFinding/Hexagon.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
namespace Game
{

SpatialObject::SpatialObject(unsigned int radius) : Object(), _radius(radius)
{
}

void SpatialObject::spatial_p_proc(Object *source)
{
    if (_script && _script->hasFunction("spatial_p_proc"))
    {
        _script
                ->setSourceObject(source)
                ->call("spatial_p_proc");
    }
}

unsigned int SpatialObject::radius()
{
    return _radius;
}

}
}
