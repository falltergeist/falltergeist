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
#include "Base/Singleton.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
namespace Audio
{
    class Mixer;
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
class Renderer;
class UI;
class TextArea;
class AnimatedPalette;
class Settings;

namespace Game
{

class GameDudeObject;
class GameTime;

class Game
{
public:
    static Game* getInstance();

    void shutdown();
    std::vector<State::State*>* states();
    std::vector<State::State*>* statesForRender();
    std::vector<State::State*>* statesForThinkAndHandle();
    void pushState(State::State* state);
    void setState(State::State* state);
    void popState();
    void run();
    void quit();
    void init(std::unique_ptr<Settings> settings);

    void handle();
    void think();
    void render();

    void setPlayer(GameDudeObject* player);
    GameDudeObject* player();
    Mouse* mouse();
    Renderer* renderer();
    GameTime* gameTime();
    State::Location* locationState();
    Audio::Mixer* mixer();

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    Settings* settings() const;
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
    std::unique_ptr<Audio::Mixer> _mixer;
    FpsCounter* _fpsCounter = 0;
    TextArea* _mousePosition = 0;
    TextArea* _currentTime = 0;
    TextArea* _falltergeistVersion = 0;
    std::unique_ptr<Settings> _settings;
    AnimatedPalette* _animatedPalette = 0;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    void _initGVARS();
private:
    friend class Base::Singleton<Game>;

    Game();
    ~Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};

Game* getInstance();

}
}

#endif // FALLTERGEIST_GAME_H
