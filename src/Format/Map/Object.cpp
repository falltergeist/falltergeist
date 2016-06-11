/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// C++ standard includes

// Falltergeist includes
#include "../Map/Object.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Map
{

Object::Object()
{
}

Object::~Object()
{
    for (auto child : _children)
    {
        delete child;
    }
}

std::vector<Object*>* Object::children()
{
    return &_children;
}

unsigned int Object::OID()
{
    return _unknown1;
}

void Object::setOID(unsigned int value)
{
    _unknown1 = value;
}

int Object::hexPosition()
{
    return _hexPosition;
}

void Object::setHexPosition(int value)
{
    _hexPosition = value;
}

unsigned int Object::x()
{
    return _unknown2;
}

void Object::setX(unsigned int value)
{
    _unknown2 = value;
}

unsigned int Object::y()
{
    return _unknown3;
}

void Object::setY(unsigned int value)
{
    _unknown3 = value;
}

unsigned int Object::sx()
{
    return _unknown4;
}

void Object::setSx(unsigned int value)
{
    _unknown4 = value;
}

unsigned int Object::frameNumber()
{
    return _frameNumber;
}

void Object::setFrameNumber(unsigned int value)
{
    _frameNumber = value;
}

unsigned int Object::orientation()
{
    return _orientation;
}

void Object::setOrientation(unsigned int value)
{
    _orientation = value;
}

unsigned int Object::FID()
{
    return (_frmTypeId << 24) | _frmId;
}

unsigned int Object::frmTypeId()
{
    return _frmTypeId;
}

void Object::setFrmTypeId(unsigned int value)
{
    _frmTypeId = value;
}

unsigned int Object::frmId()
{
    return _frmId;
}

void Object::setFrmId(unsigned int value)
{
    _frmId = value;
}

unsigned int Object::sy()
{
    return _unknown5;
}

void Object::setSy(unsigned int value)
{
    _unknown5 = value;
}

unsigned int Object::elevation()
{
    return _elevation;
}

void Object::setElevation(unsigned int value)
{
    _elevation = value;
}

unsigned int Object::PID()
{
    return (_objectID3 << 28) |(_objectTypeId << 24) | (_objectID2 << 16) | (_objectID1 << 12) | _objectId;
}

unsigned int Object::objectTypeId()
{
    return _objectTypeId;
}

void Object::setObjectTypeId(unsigned int value)
{
    _objectTypeId = value;
}

unsigned int Object::objectId()
{
    return _objectId;
}

void Object::setObjectId(unsigned int value)
{
    _objectId = value;
}

unsigned int Object::objectID1()
{
    return _objectID1;
}

void Object::setObjectID1(unsigned int value)
{
    _objectID1 = value;
}

unsigned int Object::objectID2()
{
    return _objectID2;
}

void Object::setObjectID2(unsigned int value)
{
    _objectID2 = value;
}

unsigned int Object::objectID3()
{
    return _objectID3;
}

void Object::setObjectID3(unsigned int value)
{
    _objectID3 = value;
}

unsigned int Object::objectSubtypeId()
{
    return _objectSubtypeId;
}

void Object::setObjectSubtypeId(unsigned int value)
{
    _objectSubtypeId = value;
}

unsigned int Object::flags()
{
    return _flags;
}

void Object::setFlags(unsigned int value)
{
    _flags = value;
}

unsigned int Object::combatId()
{
    return _unknown7;
}

void Object::setCombatId(unsigned int value)
{
    _unknown7 = value;
}

unsigned int Object::lightRadius()
{
    return _lightRadius;
}

void Object::setLightRadius(unsigned int value)
{
    _lightRadius = value;
}

unsigned int Object::lightIntensity()
{
    return _lightIntensity;
}

void Object::setLightIntensity(unsigned int value)
{
    _lightIntensity = value;
}

int Object::scriptId()
{
    return _scriptId;
}

void Object::setScriptId(int value)
{
    _scriptId = value;
}

int Object::mapScriptId()
{
    return _mapScriptId;
}

void Object::setMapScriptId(int value)
{
    _mapScriptId = value;
}

unsigned int Object::outline()
{
    return _unknown10;
}

void Object::setOutline(unsigned int value)
{
    _unknown10 = value;
}

unsigned int Object::inventorySize()
{
    return _inventorySize;
}

void Object::setInventorySize(unsigned int value)
{
    _inventorySize = value;
}

unsigned int Object::maxInventorySize()
{
    return _unknown11;
}

void Object::setMaxInventorySize(unsigned int value)
{
    _unknown11 = value;
}

unsigned int Object::unknown12()
{
    return _unknown12;
}

void Object::setUnknown12(unsigned int value)
{
    _unknown12 = value;
}

unsigned int Object::unknown13()
{
    return _unknown13;
}

void Object::setUnknown13(unsigned int value)
{
    _unknown13 = value;
}

int Object::exitMap()
{
    return _exitMap;
}

void Object::setExitMap(int value)
{
    _exitMap = value;
}

int Object::exitPosition()
{
    return _exitPosition;
}

void Object::setExitPosition(int value)
{
    _exitPosition = value;
}

int Object::exitElevation()
{
    return _exitElevation;
}

void Object::setExitElevation(int value)
{
    _exitElevation = value;
}

int Object::exitOrientation()
{
    return _exitOrientation;
}

void Object::setExitOrientation(int value)
{
    _exitOrientation = value;
}

unsigned int Object::ammount()
{
    return _ammount;
}

void Object::setAmmount(unsigned int value)
{
    _ammount = value;
}


int Object::elevatorType()
{
    return _elevatorType;
}

void Object::setElevatorType(int type)
{
    _elevatorType = type;
}

int Object::elevatorLevel()
{
    return _elevatorLevel;
}

void Object::setElevatorLevel(int level)
{
    _elevatorLevel = level;
}

bool Object::opened()
{
    return _opened;
}

void Object::setOpened(bool opened)
{
    _opened = opened;
}

int Object::AIPacket()
{
    return _AIPacket;
}

void Object::setAIPacket(int packet)
{
    _AIPacket = packet;
}

int Object::ammo()
{
    return _ammo;
}

void Object::setAmmo(int ammo)
{
    _ammo = ammo;
}

int Object::ammoPID()
{
    return _ammoPID;
}

void Object::setAmmoPID(int PID)
{
    _ammoPID = PID;
}


}
}
}
