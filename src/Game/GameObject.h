/*
 * Copyright 2012-2014 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAMEOBJECT_H
#define FALLTERGEIST_GAMEOBJECT_H

// C++ standard includes
#include <vector>
#include <string>

// Falltergeist includes
#include "../Engine/AnimationQueue.h"

// Third party includes

namespace Falltergeist
{
class VM;
class Location;
class InteractiveSurface;
class AnimationQueue;

class GameObject
{
protected:
    int _type = -1;
    int _subtype = -1;
    int _PID = -1;
    int _FID = -1;
    int _position = -1;
    int _elevation = 0;
    int _orientation = 0;
    std::string _name;
    std::string _description;
    std::vector<VM*> _scripts;
    Location* _location = 0;
    InteractiveSurface* _surface = 0;
    AnimationQueue _animationQueue;
public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC, TYPE_DUDE };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIRS, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER, TYPE_SCENERY_GENERIC };

    GameObject();
    virtual ~GameObject();

    int type();
    int subtype();

    int PID();
    void setPID(int value);

    int FID();
    void setFID(int value);

    int position();
    void setPosition(int value);

    int elevation();
    void setElevation(int value);

    int orientation();
    virtual void setOrientation(int value);

    std::string name();
    void setName(std::string value);

    std::string description();
    void setDescription(std::string value);

    std::vector<VM*>* scripts();

    Location* location();
    void setLocation(Location* value);

    AnimationQueue* animationQueue();
    InteractiveSurface* surface();
    void setSurface(InteractiveSurface* surface);

};

}
#endif // FALLTERGEIST_GAMEOBJECT_H
