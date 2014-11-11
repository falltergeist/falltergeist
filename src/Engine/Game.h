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
class State;
class Exception;
class Screen;
class ResourceManager;
class GameDudeObject;
class GameTime;
class FpsCounter;
class Mouse;
class LocationState;
class AudioMixer;
class Renderer;
class UI;
class TextArea;
class EngineSettings;
class AnimatedPalette;

class Game
{
protected:
    std::vector<int> _GVARS;
    std::vector<State*> _states;
    std::vector<State*> _statesForRender;
    std::vector<State*> _statesForThinkAndHandle;
    std::vector<State*> _statesForDelete;

    GameDudeObject* _player = 0;
    GameTime* _gameTime = 0;
    Renderer* _renderer = 0;
    ResourceManager* _resourceManager = 0;
    Mouse* _mouse = 0;
    AudioMixer* _mixer = 0;
    FpsCounter* _fpsCounter = 0;
    TextArea* _mousePosition = 0;
    TextArea* _currentTime = 0;
    TextArea* _falltergeistVersion = 0;
    EngineSettings* _engineSettings = 0;
    AnimatedPalette* _animatedPalette = 0;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    void _initialize();
    void _initGVARS();
private:
    Game() {}
    Game(Game const&);
    void operator=(Game const&);
    static Game* _instance;
    static bool _instanceFlag;
public:
    ~Game();
    static Game* getInstance();

    void shutdown();
    std::vector<State*>* states();
    std::vector<State*>* statesForRender();
    std::vector<State*>* statesForThinkAndHandle();
    void pushState(State* state);
    void setState(State* state);
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
    LocationState* locationState();
    AudioMixer* mixer();

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    EngineSettings* engineSettings();
    AnimatedPalette* animatedPalette();

};

}
#endif // FALLTERGEIST_GAME_H
