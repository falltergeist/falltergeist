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

// C++ standard includes
#include <map>

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"

// Third party includes

namespace Falltergeist
{
class Animation;
class VM;
class GameObject;

class LocationObject : public InteractiveSurface
{
protected:
    unsigned int _PID;
    unsigned int _FID;

    unsigned int _orientation;
    unsigned int _elevation;

    unsigned int _descriptionId;    

    Animation * _animation = 0;
    std::map<std::string, VM*> _scripts;
    GameObject* _gameObject = 0;

public:
    LocationObject(int x = 0, int y = 0);
    ~LocationObject();

    virtual SDL_Surface * sdl_surface();

    std::string name();
    std::string description();

    void setPID(unsigned int value);
    unsigned int PID();

    void setFID(unsigned int value);
    unsigned int FID();

    void setDescriptionId(unsigned int value);
    unsigned int descriptionId();

    void setOrientation(unsigned int value);
    unsigned int orientation();

    void setElevation(unsigned int value);
    unsigned int elevation();

    Animation * animation();
    void setAnimation(Animation * animation);

    virtual int xOffset();
    virtual int yOffset();
    virtual void think();

    VM* script(std::string name);
    std::map<std::string, VM*>* scripts();
    void addScript(std::string name, VM* script);
    void removeScript(std::string name);
    void removeScripts();

    GameObject* gameObject();
    void setGameObject(GameObject* value);

};

}

#endif // FALLTERGEIST_LOCATIONOBJECT_H
