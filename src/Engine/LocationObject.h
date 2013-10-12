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
