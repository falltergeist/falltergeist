﻿#pragma once

// Project includes

// Third-party includes

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Map
        {
            class Object
            {
                public:
                    Object();
                    Object(const Object&) = delete;
                    Object& operator= (const Object&) = delete;

                    unsigned int ammount();
                    void setAmmount(unsigned int value);

                    unsigned int OID();
                    void setOID(unsigned int value);

                    int hexPosition();
                    void setHexPosition(int value);

                    unsigned int x();
                    void setX(unsigned int value);

                    unsigned int y();
                    void setY(unsigned int value);

                    unsigned int sx();
                    void setSx(unsigned int value);

                    unsigned int sy();
                    void setSy(unsigned int value);

                    unsigned int frameNumber();
                    void setFrameNumber(unsigned int value);

                    unsigned int orientation();
                    void setOrientation(unsigned int value);

                    unsigned int FID();
                    unsigned int frmTypeId();
                    void setFrmTypeId(unsigned int value);
                    unsigned int frmId();
                    void setFrmId(unsigned int value);

                    unsigned int flags();
                    void setFlags(unsigned int value);

                    unsigned int elevation();
                    void setElevation(unsigned int value);

                    unsigned int PID();
                    unsigned int objectTypeId();

                    void setObjectTypeId(unsigned int value);
                    unsigned int objectId();

                    void setObjectId(unsigned int value);
                    unsigned int objectSubtypeId();
                    void setObjectSubtypeId(unsigned int value);

                    unsigned int objectID1();
                    void setObjectID1(unsigned int value);

                    unsigned int objectID2();
                    void setObjectID2(unsigned int value);

                    unsigned int objectID3();
                    void setObjectID3(unsigned int value);

                    unsigned int combatId();
                    void setCombatId(unsigned int value);

                    unsigned int lightRadius();
                    void setLightRadius(unsigned int value);

                    unsigned int lightIntensity();
                    void setLightIntensity(unsigned int value);

                    unsigned int outline();
                    void setOutline(unsigned int value);

                    int scriptId();
                    void setScriptId(int value);
                    int mapScriptId();
                    void setMapScriptId(int value);

                    unsigned int inventorySize();
                    void setInventorySize(unsigned int value);

                    unsigned int maxInventorySize();
                    void setMaxInventorySize(unsigned int value);

                    unsigned int unknown12();
                    void setUnknown12(unsigned int value);

                    unsigned int unknown13();
                    void setUnknown13(unsigned int value);

                    int exitMap();
                    void setExitMap(int value);

                    int exitPosition();
                    void setExitPosition(int value);

                    int exitElevation();
                    void setExitElevation(int value);

                    int exitOrientation();
                    void setExitOrientation(int value);

                    int elevatorType();
                    void setElevatorType(int type);

                    int elevatorLevel();
                    void setElevatorLevel(int level);

                    bool opened();
                    void setOpened(bool opened);

                    int AIPacket();
                    void setAIPacket(int packet);

                    int ammo();
                    void setAmmo(int ammo);

                    int ammoPID();
                    void setAmmoPID(int PID);

                    std::vector<std::unique_ptr<Object>>& children();

                private:
                    unsigned int _ammount = 0;
                    unsigned int _unknown1;
                    unsigned int _unknown2;
                    unsigned int _unknown3;
                    unsigned int _unknown4;
                    unsigned int _unknown5;
                    unsigned int _frameNumber;
                    unsigned int _orientation;
                    unsigned int _frmTypeId;
                    unsigned int _frmId;
                    unsigned int _flags;
                    unsigned int _elevation;
                    unsigned int _objectTypeId = 0;
                    unsigned int _objectId = 0;
                    unsigned int _objectSubtypeId = 0;
                    unsigned int _objectID1 = 0;
                    unsigned int _objectID2 = 0;
                    unsigned int _objectID3 = 0;
                    unsigned int _unknown7;
                    unsigned int _lightRadius;
                    unsigned int _lightIntensity;
                    unsigned int _unknown10;
                    unsigned int _inventorySize;
                    unsigned int _unknown11;
                    unsigned int _unknown12;
                    unsigned int _unknown13;
                    int _exitPosition;
                    int _exitOrientation;
                    int _exitElevation;
                    int _exitMap;

                    int _elevatorType = 0;
                    int _elevatorLevel = 0;
                    bool _opened = false;
                    int _AIPacket = 0;
                    int _ammo = 0;
                    int _ammoPID = 0;

                    int _mapScriptId = -1;
                    int _scriptId = -1;
                    int _hexPosition = -1;
                    std::vector<std::unique_ptr<Object>> _children;
            };
        }
    }
}
