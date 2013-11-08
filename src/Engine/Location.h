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

class Location
{
protected:
    unsigned int _scrollTicks = 0;
    bool _scrollStatus = false;
    VM* _script = 0;
    GameDudeObject* _player = 0;
    std::vector<GameObject*> _objects;
    std::vector<GameObject*> _objectsToRender;
    std::vector<int> _MVARS;
    std::vector<int> _LVARS;
    std::map<std::string, VMStackValue*> _EVARS;
    int _scriptsTicks = 0;

    void _checkObjectsToRender();
    void _generateBackground();

    unsigned int _cols;
    unsigned int _rows;

    LocationCamera* _camera = 0;
    unsigned int _elevation;

    Surface* _tilesBackground;

    libfalltergeist::MapFileType* _mapFile = 0;
    libfalltergeist::LstFileType* _tilesLst = 0;
    bool _initialized = false;

public:
    enum Tile { TILE_WIDTH = 80, TILE_HEIGHT = 36 };
    Location(libfalltergeist::MapFileType* mapFile);
    ~Location();
    void init();
    void think();
    bool scroll(bool up = false, bool down = false, bool left = false, bool right = false);
    static int hexagonToX(unsigned int hexagon);
    static int hexagonToY(unsigned int hexagon);
    static unsigned int positionToHexagon(int x, int y);
    unsigned int tileToX(unsigned int tile);
    unsigned int tileToY(unsigned int tile);
    int width();
    int height();
    void handleAction(GameObject* object, int action);

    LocationCamera* camera();

    GameDudeObject* player();
    static GameObject* createObject(int PID);

    libfalltergeist::MapFileType* mapFile();
    Surface* tilesBackground();
    std::vector<GameObject*>* objects();
    std::vector<GameObject*>* objectsToRender();

    void setMVAR(unsigned int number, int value);
    int MVAR(unsigned int number);
    void setLVAR(unsigned int number, int value);
    int LVAR(unsigned int number);
    std::map<std::string, VMStackValue*>* EVARS();

};


}

#endif // FALLTERGEIST_LOCATION_H
