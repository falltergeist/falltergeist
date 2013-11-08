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
 */

#ifndef FALLTERGEIST_GAME_H
#define FALLTERGEIST_GAME_H

// C++ standard includes
#include <vector>
#include <string>

// Falltergeist includes

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
class State;
class Exception;
class Screen;
class ResourceManager;
class Player;
class FpsCounter;
class Mouse;
class Location;

class Game
{
protected:
    std::vector<int> _GVARS;
    std::string _version;
    ResourceManager* _resourceManager = 0;
    std::vector<State*> _states;
    std::vector<State*> _deletedStates;
    Player* _player = 0;
    Screen* _screen = 0;
    Mouse* _mouse = 0;
    Location* _location = 0;
    FpsCounter * _fpsCounter = 0;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    void _initialize();
    void _initGVARS();
private:
    Game() {}
    Game(Game const&);
    void operator=(Game const&);
public:
    ~Game();
    static Game& getInstance();

    Screen * screen();

    ResourceManager * resourceManager();

    std::vector<State*>* states();
    void pushState(State * state);
    void setState(State * state);
    void popState();
    void run();
    void quit();

    void setPlayer(Player * player);
    Player* player();
    Mouse* mouse();
    void setLocation(Location* location);
    Location* location();
    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);
};

}
#endif // FALLTERGEIST_GAME_H
