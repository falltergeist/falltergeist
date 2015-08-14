/*
 * Copyright 2012-2015 Falltergeist Developers.
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
#include <memory>

// Falltergeist includes

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
namespace Lua
{
    class Script;
}
namespace State
{
    class Location;
    class State;
}
class Exception;
class Screen;
class ResourceManager;
class FpsCounter;
class Mouse;
class AudioMixer;
class Renderer;
class UI;
class TextArea;
class AnimatedPalette;
class Settings;
class InputController;

namespace Game
{

class GameDudeObject;
class GameTime;

class Game
{
public:
    ~Game();
    static Game* getInstance();
    static void export_to_lua_script(Lua::Script* script);

    void shutdown();
    std::vector<State::State*>* states();
    std::vector<State::State*>* statesForRender();
    std::vector<State::State*>* statesForThinkAndHandle();
    void pushState(State::State* state);
    void setState(State::State* state);
    void popState();
    void run();
    void quit();

    void handle();
    void think();
    void render();

    void setPlayer(GameDudeObject* player);
    GameDudeObject* player();
    Mouse* mouse();
    Renderer* renderer();
    GameTime* gameTime();
    State::Location* locationState();
    AudioMixer* mixer();
    InputController* inputController() const;

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    Settings* settings();
    AnimatedPalette* animatedPalette();

protected:
    std::vector<int> _GVARS;
    std::vector<State::State*> _states;
    std::vector<State::State*> _statesForRender;
    std::vector<State::State*> _statesForThinkAndHandle;
    std::vector<State::State*> _statesForDelete;

    GameDudeObject* _player = 0;
    GameTime* _gameTime = 0;
    Renderer* _renderer = 0;
    Mouse* _mouse = 0;
    AudioMixer* _mixer = 0;
    FpsCounter* _fpsCounter = 0;
    TextArea* _mousePosition = 0;
    TextArea* _currentTime = 0;
    TextArea* _falltergeistVersion = 0;
    Settings* _settings = 0;
    AnimatedPalette* _animatedPalette = 0;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    std::unique_ptr<InputController> inputController_;
    void _initialize();
    void _initGVARS();
private:
    Game();
    Game(Game const&);
    void operator=(Game const&);
    static Game* _instance;
    static bool _instanceFlag;

};

Game* getInstance();

}
}

#endif // FALLTERGEIST_GAME_H
