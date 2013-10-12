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

#include <vector>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#define VERSION "0.0.6"

namespace Falltergeist
{
class State;
class Exception;
class Screen;
class ResourceManager;
class Player;
class FpsCounter;
class Mouse;

class Game
{
protected:
    ResourceManager * _resourceManager;
    std::vector<State *> * _states;
    std::vector<State *> * _deletedStates;
    Player * _player;
    Screen * _screen;
    Mouse * _mouse;
    FpsCounter * _fpsCounter;
    bool _quit;
    SDL_Event _event;

public:
    Game(int width, int height, int bpp);
    ~Game();

    Screen * screen();

    ResourceManager * resourceManager();

    void pushState(State * state);
    void setState(State * state);
    void popState();
    void run();
    void quit();

    void setPlayer(Player * player);
    Player * player();
    Mouse * mouse();
};

}
#endif // FALLTERGEIST_GAME_H
