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
#include <algorithm>

// Falltergeist includes
#include "../../Exception.h"
#include "../Map/File.h"
#include "../Map/Elevation.h"
#include "../Map/Object.h"
#include "../Map/Script.h"
#include "../Pro/File.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Map
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
}

File::~File()
{
    for (auto elevation : _elevations)
    {
        delete elevation;
    }

    for (auto script : _scripts)
    {
        delete script;
    }
}

void File::_initialize()
{
    if (_initialized) return;
    if (_proFileTypeLoaderCallback == 0) throw Exception("File::_initialize() - proto loader callback not defined");
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    _version = uint32();

    uint8_t name[16];
    this->readBytes(name, 16);
    _name = (char*)name;
    std::transform(_name.begin(),_name.end(),_name.begin(), ::tolower);

    _defaultPosition   = uint32();
    _defaultElevation  = uint32();
    _defaultOrientaion = uint32();
    _LVARsize          = uint32();
    _scriptId          = int32();
    _elevationFlags    = uint32();

    unsigned elevations = 0;
    if ((_elevationFlags & 2) == 0) elevations++;
    if ((_elevationFlags & 4) == 0) elevations++;
    if ((_elevationFlags & 8) == 0) elevations++;

    _unknown1       = int32();
    _MVARsize       = uint32();
    _mapId          = uint32();
    _timeSinceEpoch = uint32();

    this->skipBytes(4*44); // unkonwn

    // MVAR AND SVAR SECTION
    for (unsigned int i = 0; i != _MVARsize; ++i)
    {
        _MVARS.push_back(int32());
    }

    for (unsigned int i = 0; i != _LVARsize; ++i)
    {
        _LVARS.push_back(int32());
    }

    // TILES SECTION
    for (unsigned int i = 0; i < elevations; i++)
    {
        _elevations.push_back(new Elevation);

        for (unsigned i = 0; i < 10000; i++)
        {
            _elevations.back()->roofTiles()->push_back(uint16());
            _elevations.back()->floorTiles()->push_back(uint16());
        }
    }

    // SCRIPTS SECTION
    for (unsigned i = 0; i < 5; i++)
    {
        uint32_t count = uint32();
        if (count > 0)
        {
            uint32_t loop = count;
            if (count%16 > 0 )
            {
                loop += 16 - count%16;
            }

            uint32_t check = 0;
            for (unsigned j = 0; j < loop; j++)
            {

                auto script = new Script();
                script->setPID(int32());

                uint32(); // next script. unused

                switch ((script->PID() & 0xFF000000) >> 24)
                {
                    case 0:
                        script->setType(Script::Type::SYSTEM);
                        break;
                    case 1:
                        script->setType(Script::Type::SPATIAL);
                        script->setSpatialTile(uint32());
                        script->setSpatialRadius(uint32());
                        break;
                    case 2:
                        script->setType(Script::Type::TIMER);
                        script->setTimerTime(uint32());
                        break;
                    case 3:
                        script->setType(Script::Type::ITEM);
                        break;
                    case 4:
                        script->setType(Script::Type::CRITTER);
                        break;
                    default:
                        break;
                }
                uint32(); //flags
                script->setScriptId(int32());
                uint32(); //unknown 5
                uint32(); //oid == object->OID
                uint32(); //local var offset
                uint32(); //loal var cnt
                uint32(); //unknown 9
                uint32(); //unknown 10
                uint32(); //unknown 11
                uint32(); //unknown 12
                uint32(); //unknown 13
                uint32(); //unknown 14
                uint32(); //unknown 15
                uint32(); //unknown 16

                if (j < count)
                {
                    _scripts.push_back(script);
                }
                else
                {
                    delete script;
                }

                if ((j % 16) == 15)
                {
                    check += uint32();
                    uint32();
                }
            }
            if (check != count)
            {
                throw Exception("File::open() - error reading scripts: check is incorrect");
            }
        }
    }

    //OBJECTS SECTION
    uint32(); // objects total
    for (unsigned i = 0; i != elevations; ++i)
    {
        unsigned objectsOnElevation = uint32();
        for (unsigned j = 0; j != objectsOnElevation; ++j)
        {
            auto object = _readObject();
            _elevations.at(i)->objects()->push_back(object);

            if (object->inventorySize() > 0)
            {
                for (unsigned int i = 0; i != object->inventorySize(); ++i)
                {
                    uint32_t ammount = uint32();
                    auto subobject = _readObject();
                    subobject->setAmmount(ammount);
                    object->children()->push_back(subobject);
                }
            }
        }
    }
}

Object* File::_readObject()
{
    auto object =new Object();

    object->setOID(uint32());
    object->setHexPosition(int32());
    object->setX(uint32());
    object->setY(uint32());
    object->setSx(uint32());
    object->setSy(uint32());
    object->setFrameNumber(uint32());
    object->setOrientation(uint32());
    uint32_t FID = uint32();
    object->setFrmTypeId(FID >> 24);
    object->setFrmId(0x00FFFFFF & FID);
    object->setFlags(uint32());
    object->setElevation(uint32());
    uint32_t PID = uint32();
    object->setObjectTypeId(PID >> 24);
    object->setObjectId(0x00FFFFFF & PID);
    object->setCombatId(uint32());
    object->setLightRadius(uint32());
    object->setLightIntensity(uint32());
    object->setOutline(uint32());

    int32_t SID = int32();
    if (SID != -1)
    {
        for (auto it = _scripts.begin(); it != _scripts.end(); ++it)
        {
            if ((*it)->PID() == SID)
            {
                object->setMapScriptId((*it)->scriptId());
            }
        }
    }

    SID = int32();
    if (SID != -1)
    {
        object->setScriptId(SID);
    }

    object->setInventorySize(uint32());
    object->setMaxInventorySize(uint32());
    object->setUnknown12(uint32());
    object->setUnknown13(uint32());

    switch ((OBJECT_TYPE)object->objectTypeId())
    {
        case OBJECT_TYPE::ITEM:
            object->setObjectSubtypeId(callback()(PID)->subtypeId());
            switch((ITEM_TYPE)object->objectSubtypeId())
            {
                case ITEM_TYPE::AMMO:
                    object->setAmmo(uint32()); // bullets
                    break;
                case ITEM_TYPE::KEY:
                    uint32(); // keycode = -1 in all maps. saves only? ignore for now
                    break;
                case ITEM_TYPE::MISC:
                    object->setAmmo(uint32()); //charges - have strangely high values, or negative.
                    break;
                case ITEM_TYPE::WEAPON:
                    object->setAmmo(uint32()); // ammo
                    object->setAmmoPID(uint32()); // ammo pid
                    break;
                case ITEM_TYPE::ARMOR:
                    break;
                case ITEM_TYPE::CONTAINER:
                    break;
                case ITEM_TYPE::DRUG:
                    break;
                default:
                    throw Exception("File::_readObject() - unknown item type");
            }
            break;
        case OBJECT_TYPE::CRITTER:
            uint32(); //reaction to player - saves only
            uint32(); //current mp - saves only
            uint32(); //combat results - saves only
            uint32(); //damage last turn - saves only
            object->setAIPacket(uint32()); // AI packet - is it different from .pro? well, it can be
            uint32(); // team - always 1? saves only?
            uint32(); // who hit me - saves only
            uint32(); // hit points - saves only, otherwise = value from .pro
            uint32(); // rad - always 0 - saves only
            uint32(); // poison - always 0 - saves only
            object->setFrmId(FID & 0x00000FFF);
            object->setObjectID1((FID & 0x0000F000) >> 12);
            object->setObjectID2((FID & 0x00FF0000) >> 16);
            object->setFrmTypeId((FID & 0x0F000000) >> 24);
            object->setObjectID3((FID & 0xF0000000) >> 28);
            break;
        case OBJECT_TYPE::SCENERY:
            object->setObjectSubtypeId(callback()(PID)->subtypeId());
            uint32_t elevhex;  // elev+hex
            uint32_t hex;
            uint32_t elev;
            switch((SCENERY_TYPE)object->objectSubtypeId())
            {
                case SCENERY_TYPE::LADDER_TOP:
                case SCENERY_TYPE::LADDER_BOTTOM:
                case SCENERY_TYPE::STAIRS:
                    elevhex = uint32();  // elev+hex
                    hex = elevhex & 0xFFFF;
                    elev = ((elevhex >> 28) & 0xf) >> 1;
                    object->setExitMap(int32()); // map id
                    object->setExitPosition(hex);
                    object->setExitElevation(elev);
                    break;
                case SCENERY_TYPE::ELEVATOR:
                    object->setElevatorType(uint32()); // elevator type - sometimes -1
                    object->setElevatorLevel(uint32()); // current level - sometimes -1
                    break;
                case SCENERY_TYPE::DOOR:
                    object->setOpened(uint32()!=0);// is opened;
                    break;
                case SCENERY_TYPE::GENERIC:
                    break;
                default:
                    throw Exception("File::_readObject() - unknown scenery type");
            }
            break;
        case OBJECT_TYPE::WALL:
            break;
        case OBJECT_TYPE::TILE:
            break;
        case OBJECT_TYPE::MISC:
            switch(object->objectId())
            {
                case 12:
                    break;
                // Exit Grids
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                    object->setExitMap(int32());
                    object->setExitPosition(int32());
                    object->setExitElevation(int32());
                    object->setExitOrientation(int32());
                    break;
                default:
                    uint32();
                    uint32();
                    uint32();
                    uint32();
                    break;
            }
            break;
        default:
            throw Exception("File::_readObject() - unknown type");
    }
    return object;
}

std::vector<Elevation*>* File::elevations()
{
    return &_elevations;
}

File* File::setCallback(ProFileTypeLoaderCallback callback)
{    
    _proFileTypeLoaderCallback = callback;
    _initialize();
    return this;
}

ProFileTypeLoaderCallback File::callback() const
{
    return _proFileTypeLoaderCallback;
}

unsigned int File::version() const
{
    return _version;
}

unsigned int File::defaultPosition() const
{
    return _defaultPosition;
}

unsigned int File::defaultElevation() const
{
    return _defaultElevation;
}

unsigned int File::defaultOrientation() const
{
    return _defaultOrientaion;
}

int File::scriptId() const
{
    return _scriptId;
}

std::string File::name() const
{
    return _name;
}

unsigned int File::elevationFlags() const
{
    return _elevationFlags;
}

int File::unknown1() const
{
    return _unknown1;
}

unsigned int File::mapId() const
{
    return _mapId;
}

unsigned int File::timeSinceEpoch() const
{
    return _timeSinceEpoch;
}

std::vector<int>* File::LVARS()
{
    return &_LVARS;
}

std::vector<int>* File::MVARS()
{
    return &_MVARS;
}

std::vector<Script*>* File::scripts()
{
    return &_scripts;
}

}
}
}
