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

class LocationObject : public InteractiveSurface
{
protected:
    unsigned int _objectTypeId;
    unsigned int _objectSubtypeId;
    unsigned int _objectId;
    unsigned int _objectID1;
    unsigned int _objectID2;
    unsigned int _objectID3;

    unsigned int _frmTypeId;
    unsigned int _frmId;

public:
    LocationObject(int x = 0, int y = 0);
    ~LocationObject();

    unsigned int objectTypeId();
    void setObjectTypeId(unsigned int value);

    unsigned int objectSubtypeId();
    void setObjectSubtypeId(unsigned int value);

    unsigned int objectId();
    void setObjectId(unsigned int value);

    unsigned int objectID1();
    void setObjectID1(unsigned int value);

    unsigned int objectID2();
    void setObjectID2(unsigned int value);

    unsigned int objectID3();
    void setObjectID3(unsigned int value);

    unsigned int frmTypeId();
    void setFrmTypeId(unsigned int value);

    unsigned int frmId();
    void setFrmId(unsigned int value);

};

}

#endif // FALLTERGEIST_LOCATIONOBJECT_H
