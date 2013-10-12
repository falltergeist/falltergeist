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
