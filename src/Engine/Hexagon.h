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
 */

#ifndef FALLTERGEIST_HEXAGON_H
#define FALLTERGEIST_HEXAGON_H

// C++ standard includes
#include <vector>
#include <list>
#include <memory>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
class GameObject;

class Hexagon
{
protected:
    bool _checked = false; // pathfinding flag
    std::shared_ptr<Hexagon> _cameFrom; // pathfinding flag
    std::vector<std::shared_ptr<Hexagon>> _neighbours;
    std::list<std::shared_ptr<GameObject>> _objects;
    unsigned int _number = 0; // position in hexagonal grid
    unsigned int _x = 0;
    unsigned int _y = 0;
public:
    Hexagon();
    Hexagon(unsigned int number);

    unsigned int x();
    void setX(unsigned int value);

    unsigned int y();
    void setY(unsigned int value);

    unsigned int number();
    void setNumber(unsigned int number);

    bool ckecked();
    void setChecked(bool value);

    std::shared_ptr<Hexagon> cameFrom();
    void setCameFrom(std::shared_ptr<Hexagon> cameFrom);

    std::vector<std::shared_ptr<Hexagon>>* neighbours();

    std::list<std::shared_ptr<GameObject>>* objects();
};

}
#endif // FALLTERGEIST_HEXAGON_H
