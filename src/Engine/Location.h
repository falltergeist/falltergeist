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

#ifndef FALLTERGEIST_LOCATION_H
#define FALLTERGEIST_LOCATION_H

// C++ standard includes

// Falltergeist includes

// Third party includes
#include "../../lib/libfalltergeist/libfalltergeist.h"

namespace Falltergeist
{
class Surface;
class LocationObject;
class LocationCamera;

class Location
{
protected:
    std::vector<LocationObject*>* _objects = 0;
    std::vector<LocationObject*>* _objectsToRender = 0;

    void _checkObjectsToRender();
    void _generateBackground();

    unsigned int _cols;
    unsigned int _rows;

    LocationCamera* _camera = 0;
    unsigned int _elevation;

    Surface* _tilesBackground;

    libfalltergeist::MapFileType* _mapFile;
    libfalltergeist::LstFileType* _tilesLst;


public:
    enum Tile { TILE_WIDTH = 80, TILE_HEIGHT = 36 };

    Location(libfalltergeist::MapFileType* mapFile);
    ~Location();
    void init();
    void think();
    bool scroll(bool up = false, bool down = false, bool left = false, bool right = false);
    int hexagonToX(unsigned int hexagon);
    int hexagonToY(unsigned int hexagon);
    unsigned int positionToHexagon(int x, int y);
    unsigned int tileToX(unsigned int tile);
    unsigned int tileToY(unsigned int tile);
    int width();
    int height();

    LocationCamera* camera();


    libfalltergeist::MapFileType* mapFile();
    Surface* tilesBackground();
    std::vector<LocationObject*>* objects();
    std::vector<LocationObject*>* objectsToRender();
};


}

#endif // FALLTERGEIST_LOCATION_H
