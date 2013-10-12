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
#include "../Engine/Animation.h"
#include <iostream>

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
    switch(_objectTypeId)
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
    switch(_objectTypeId)
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

    libfalltergeist::MsgMessage * message = msg->message(_descriptionId + 1);
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

void LocationObject::x(int x)
{
    if (_animation == 0)
    {
        InteractiveSurface::x(x);
    }
    else
    {
        InteractiveSurface::x(x - _animation->surface()->x());
    }
}

void LocationObject::y(int y)
{
    if (_animation == 0)
    {
        InteractiveSurface::y(y);
    }
    else
    {
        InteractiveSurface::y(y - _animation->surface()->y());
    }
}

int LocationObject::x()
{
    if (_animation == 0)
    {
        return InteractiveSurface::x();
    }
    else
    {
        return InteractiveSurface::x() + _animation->surface()->x();
    }
}

int LocationObject::y()
{
    if (_animation == 0)
    {
        return InteractiveSurface::y();
    }
    else
    {
        return InteractiveSurface::y() + _animation->surface()->y();
    }
}

unsigned int LocationObject::objectTypeId() { return _objectTypeId; }
        void LocationObject::setObjectTypeId(unsigned int value) { _objectTypeId = value; }

unsigned int LocationObject::objectId() { return _objectId; }
        void LocationObject::setObjectId(unsigned int value) { _objectId = value; }

unsigned int LocationObject::descriptionId() { return _descriptionId; }
        void LocationObject::setDescriptionId(unsigned int value) { _descriptionId = value; }

}
