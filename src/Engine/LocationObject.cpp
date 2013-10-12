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

#include "../Engine/LocationObject.h"

namespace Falltergeist
{

LocationObject::LocationObject(int x, int y) : InteractiveSurface(0, 0, x, y)
{
}

LocationObject::~LocationObject()
{
}

unsigned int LocationObject::objectTypeId() { return _objectTypeId; }
        void LocationObject::setObjectTypeId(unsigned int value) { _objectTypeId = value; }

unsigned int LocationObject::objectSubtypeId() { return _objectSubtypeId; }
        void LocationObject::setObjectSubtypeId(unsigned int value) { _objectSubtypeId = value; }

unsigned int LocationObject::objectId() { return _objectId; }
        void LocationObject::setObjectId(unsigned int value) { _objectId = value; }

unsigned int LocationObject::objectID1() { return _objectID1; }
        void LocationObject::setObjectID1(unsigned int value) { _objectID1 = value; }

unsigned int LocationObject::objectID2() { return _objectID2; }
        void LocationObject::setObjectID2(unsigned int value) { _objectID2 = value; }

unsigned int LocationObject::objectID3() { return _objectID3; }
        void LocationObject::setObjectID3(unsigned int value) { _objectID3 = value; }

}
