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

// C++ standard includes
#include <cmath>
#include <iostream>

// Falltergeist includes
#include "../Engine/LocationObject.h"
#include "../Engine/Animation.h"
#include "../Engine/Exception.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

LocationObject::LocationObject(int x, int y) : InteractiveSurface(0, 0, x, y)
{
    _animation = 0;
}

LocationObject::~LocationObject()
{
    delete _animation;
}

std::string LocationObject::name()
{
    libfalltergeist::MsgFileType * msg;
    std::string msgFile = "text/english/game/";
    unsigned int typeId = PID() >> 24;
    switch(typeId)
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
            msgFile += "pro_item.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_CRITTER:
            msgFile += "pro_crit.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_SCENERY:
            msgFile += "pro_scen.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_TILE:
            msgFile += "pro_tile.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_WALL:
            msgFile += "pro_wall.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_MISC:
            msgFile += "pro_misc.msg";
            break;
        default:
            return "UNKNOWN";
    }
    msg = ResourceManager::msgFileType(msgFile);
    if (msg == 0) return "UNKNOWN";

    libfalltergeist::MsgMessage * message = msg->message(_descriptionId);
    if (message == 0) return "UNKNOWN INDEX";

    return message->text();
}

std::string LocationObject::description()
{
    libfalltergeist::MsgFileType * msg;
    std::string msgFile = "text/english/game/";
    unsigned int typeId = PID() >> 24;
    switch(typeId)
    {
        case libfalltergeist::ProFileType::TYPE_ITEM:
            msgFile += "pro_item.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_CRITTER:
            msgFile += "pro_crit.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_SCENERY:
            msgFile += "pro_scen.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_TILE:
            msgFile += "pro_tile.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_WALL:
            msgFile += "pro_wall.msg";
            break;
        case libfalltergeist::ProFileType::TYPE_MISC:
            msgFile += "pro_misc.msg";
            break;
        default:
            return "UNKNOWN";
    }
    msg = ResourceManager::msgFileType(msgFile);
    if (msg == 0) return "UNKNOWN";

    libfalltergeist::MsgMessage * message = msg->message(_descriptionId);
    if (message == 0) return "UNKNOWN INDEX";

    return message->text();
}

void LocationObject::think()
{
    if (_animation)
    {
        _animation->think();
    }
}

Animation * LocationObject::animation()
{
    return _animation;
}

void LocationObject::setAnimation(Animation * animation)
{
    _animation = animation;
}

SDL_Surface * LocationObject::sdl_surface()
{
    if (_animation == 0) return InteractiveSurface::sdl_surface();

    return _animation->sdl_surface();
}

int LocationObject::xOffset()
{
    if (_animation == 0)
    {
        return InteractiveSurface::xOffset() - width()/2;
    }
    else
    {
        return InteractiveSurface::xOffset() - _animation->surfaces()->at(0)->width()/2 + _animation->xOffset();
    }
}

int LocationObject::yOffset()
{
    if (_animation == 0)
    {
        return InteractiveSurface::yOffset() - height();
    }
    else
    {
        return InteractiveSurface::yOffset() - _animation->surfaces()->at(0)->height() + _animation->yOffset();
    }
}


VM* LocationObject::script(std::string name)
{
    if (_scripts.find(name) != _scripts.end())
    {
        return _scripts.at(name);
    }
    return 0;
}

std::map<std::string, VM*>* LocationObject::scripts()
{
    return &_scripts;
}

void LocationObject::removeScript(std::string name)
{
    if (_scripts.find(name) != _scripts.end())
    {
        _scripts.erase(name);
    }
}

void LocationObject::removeScripts()
{
    _scripts.clear();
}

void LocationObject::addScript(std::string name, VM* script)
{
    _scripts.insert(std::make_pair(name, script));
}

unsigned int LocationObject::PID() { return _PID; }
        void LocationObject::setPID(unsigned int value) { _PID = value; }

unsigned int LocationObject::FID() { return _FID; }
        void LocationObject::setFID(unsigned int value) { _FID = value; }

unsigned int LocationObject::descriptionId() { return _descriptionId; }
        void LocationObject::setDescriptionId(unsigned int value) { _descriptionId = value; }

unsigned int LocationObject::orientation() { return _orientation; }

void LocationObject::setOrientation(unsigned int value)
{
    _orientation = value;

    libfalltergeist::FrmFileType * frm = 0;
    unsigned int id = PID() & 0x00000FFF;
    unsigned int frmId = FID() & 0x00000FFF;
    unsigned int typeId = PID() >> 24;
    unsigned int ID1 = (FID() & 0x0000F000) >> 12;
    unsigned int ID2 = (FID() & 0x00FF0000) >> 16;
    unsigned int ID3 = (FID() & 0xF0000000) >> 28;

    if (typeId == 1)
    {
        std::cout << " >>> " << std::hex << FID() << std::endl;
        auto lst = ResourceManager::lstFileType("art/critters/critters.lst");
        std::string frmName = lst->strings()->at(frmId);
        std::string frmBase = frmName.substr(0, 6);

        if (ID2 >= 0x26 && ID2 <= 0x2F)
        {
            if (ID1 >= 0x0B || ID1 == 0)
            {
                throw Exception("Critter ID1 unsupported value");
            }
            else
            {
                frmBase += ID1 + 0x63;
                frmBase += ID2 + 0x3D;
            }
        }
        else if (ID2 == 0x24)
        {
            frmBase += "ch";
        }
        else if (ID2 == 0x25)
        {
            frmBase += "cj";
        }
        else if (ID2 == 0x40)
        {
            frmBase += "na";
        }
        else if (ID2 >= 0x30)
        {
            frmBase += "r";
            frmBase += ID2 + 0x31;
        }
        else if (ID2 >= 0x14)
        {
            frmBase += "b";
            frmBase += ID2 + 0x4d;
        }
        else if (ID2 == 0x12)
        {
            if (ID1 == 0x01)
            {
                frmBase += "dm";
            }
            else if (ID1 == 0x04)
            {
                frmBase += "gm";
            }
            else
            {
                frmBase += "as";
            }
        }
        else if (ID2 == 0x0D)
        {
            if (ID1 > 0)
            {
                frmBase += ID1 + 0x63;
                frmBase += "e";
            }
            else
            {
                frmBase += "an";
            }
        }
        else if (ID2 <= 0x01 && ID1 > 0)
        {
            frmBase += ID1 + 0x63;
            frmBase += ID2 + 0x61;
        }
        else
        {
            frmBase += "a";
            frmBase += ID2 + 0x61;
        }

        std::string extensions[] = {"frm", "frm0", "frm1", "frm2", "fr3", "frm4", "frm5", "frm6"};
        frmBase += "." + extensions[ID3];

        //std::cout << frmBase << std::endl;


        frm = ResourceManager::frmFileType("art/critters/" + frmBase);
        //std::cout << "Frm: " << frm << std::endl;
    }
    else if(typeId == 5)
    {
            if (id == 12) // какая то хрень выстроенная форму прямоугольника
            {
                //frm = ResourceManager::frmFileType("art/intrface/msef000.frm");
            }
            else if (id >= 16 && id <= 23) // exit
            {
                frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
            }
            else
            {
                //std::cout << std::dec << object->objectTypeId() << " - " << object->objectId() << " - " << object->descriptionId() << " : ";
                //std::cout << object->name() << " | " << object->description() << std::endl;
                //continue; // SKIP MISC for now
            }

    }
    else
    {
        frm = ResourceManager::frmFileType(FID());
    }

    if (!frm)
    {
        loadFromSurface(new Surface());
    }
    else if (frm->framesPerDirection() > 1)
    {
        delete _animation;
        setAnimation(new Animation(frm));
        if (typeId == 1) // critters
        {
            if (ID3 == 0)
            {
                animation()->setCurrentSurfaceSet(orientation());
            }
        }
    }
    else
    {
        loadFromSurface(new Surface(frm));
    }

}

unsigned int LocationObject::elevation() { return _elevation; }
        void LocationObject::setElevation(unsigned int value) { _elevation = value; }

}
