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

#ifndef FALLTERGEIST_LOCATION_H
#define FALLTERGEIST_LOCATION_H

// C++ standard includes
#include <memory>

// Falltergeist includes
#include "../../lib/libfalltergeist/libfalltergeist.h"

// Third party includes

namespace Falltergeist
{
class Surface;
class GameObject;
class GameDudeObject;
class LocationCamera;
class VM;
class VMStackValue;
class Image;
class Texture;

class Location
{
protected:
    unsigned int _scrollTicks = 0;
    unsigned int _scriptsTicks = 0;
    bool _scrollStatus = false;
    VM* _script = 0;
    std::shared_ptr<GameDudeObject> _player;
    std::vector<std::shared_ptr<GameObject>> _objects;
    std::vector<std::shared_ptr<GameObject>> _objectsToRender;
    std::vector<int> _MVARS;
    std::map<std::string, VMStackValue*> _EVARS;
    unsigned int _lastObjectsCheck = 0;


    unsigned int _cols;
    unsigned int _rows;

    std::shared_ptr<LocationCamera> _camera;
    unsigned int _elevation = 0;

    std::shared_ptr<Texture> _tilesFloor;
    std::shared_ptr<Texture> _tilesRoof;

    std::shared_ptr<libfalltergeist::MapFileType> _mapFile;
    std::shared_ptr<libfalltergeist::LstFileType> _tilesLst;
    bool _initialized = false;
    void _generateFloor();
    void _generateRoof();
public:
    enum Tile { TILE_WIDTH = 80, TILE_HEIGHT = 36 };
    Location(std::shared_ptr<libfalltergeist::MapFileType> mapFile);
    ~Location();
    void init();
    void think();
    static int hexagonToX(unsigned int hexagon);
    static int hexagonToY(unsigned int hexagon);
    static unsigned int positionToHexagon(int x, int y);
    unsigned int tileToX(unsigned int tile);
    unsigned int tileToY(unsigned int tile);
    int width();
    int height();
    void handleAction(GameObject* object, int action);
    void checkObjectsToRender();

    std::shared_ptr<Texture> tilesFloor();
    std::shared_ptr<Texture> tilesRoof();
    std::shared_ptr<LocationCamera> camera();

    std::shared_ptr<GameDudeObject> player();
    static std::shared_ptr<GameObject> createObject(int PID);

    std::shared_ptr<libfalltergeist::MapFileType> mapFile();
    std::vector<std::shared_ptr<GameObject>>* objects();
    std::vector<std::shared_ptr<GameObject>>* objectsToRender();

    void setMVAR(unsigned int number, int value);
    int MVAR(unsigned int number);
    std::map<std::string, VMStackValue*>* EVARS();

};


}

#endif // FALLTERGEIST_LOCATION_H
