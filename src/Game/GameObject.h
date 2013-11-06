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

#ifndef FALLTERGEIST_GAMEOBJECT_H
#define FALLTERGEIST_GAMEOBJECT_H

// C++ standard includes
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class VM;
class Location;

class GameObject
{
protected:
    int _PID = -1;
    int _FID = -1;
    int _position = -1;
    int _elevation = 0;
    int _orientation = 0;
    std::vector<VM*> _scripts;
    Location* _location = 0;
public:
    GameObject();
    virtual ~GameObject();

    int PID();
    void setPID(int value);

    int FID();
    void setFID(int value);

    int position();
    void setPosition(int value);

    int elevation();
    void setElevation(int value);

    int orientation();
    void setOrientation(int value);

    std::vector<VM*>* scripts();

    Location* location();
    void setLocation(Location* value);

};

}
#endif // FALLTERGEIST_GAMEOBJECT_H
