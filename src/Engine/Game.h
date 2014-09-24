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
class FpsCounter;
class Mouse;
class LocationState;
class AudioMixer;
class Renderer;
class UI;
class TextArea;
class EngineSettings;

class Game
{
protected:
    std::vector<int> _GVARS;
    std::shared_ptr<ResourceManager> _resourceManager;
    std::vector<std::shared_ptr<State>> _states;
    std::shared_ptr<GameDudeObject> _player;
    std::shared_ptr<Renderer> _renderer;
    std::shared_ptr<Mouse> _mouse;
    std::shared_ptr<AudioMixer> _mixer;
    std::shared_ptr<FpsCounter> _fpsCounter;
    std::shared_ptr<TextArea> _mousePosition;
    std::shared_ptr<TextArea> _falltergeistVersion;
    std::shared_ptr<EngineSettings> _engineSettings;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    void _initialize();
    void _initGVARS();
    std::vector<std::shared_ptr<UI>> _ui;
private:
    Game() {}
    Game(Game const&);
    void operator=(Game const&);
    static Game* _instance;
    static bool _instanceFlag;
public:
    ~Game();
    static Game* getInstance();

    std::shared_ptr<ResourceManager> resourceManager();

    std::vector<std::shared_ptr<State>>* states();
    std::vector<std::shared_ptr<State>> statesForRender();
    std::vector<std::shared_ptr<State>> statesForThinkAndHandle();
    void pushState(std::shared_ptr<State> state);
    void setState(std::shared_ptr<State> state);
    void popState();
    void run();
    void quit();    

    void handle();
    void think();
    void render();

    void setPlayer(std::shared_ptr<GameDudeObject> player);
    std::shared_ptr<GameDudeObject> player();
    std::shared_ptr<Mouse> mouse();
    std::shared_ptr<Renderer> renderer();

    std::shared_ptr<LocationState> locationState();

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    std::shared_ptr<EngineSettings> engineSettings();

};

}
#endif // FALLTERGEIST_GAME_H
