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

#include <list>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#define VERSION "0.0.3"

namespace Falltergeist
{
class State;
class Exception;
class Screen;
class ResourceManager;
class Player;
class FpsCounter;

class Game
{
protected:
    ResourceManager * _resourceManager;
    std::list<State *> * _states;
    std::list<State *> * _deletedStates;
    Player * _player;
    Screen * _screen;
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
};

}
#endif // FALLTERGEIST_GAME_H
