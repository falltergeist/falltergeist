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

#ifndef FALLTERGEIST_GAME_GAME_H
#define FALLTERGEIST_GAME_GAME_H

// C++ standard includes
#include <memory>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Base/Singleton.h"
#include "../Event/Dispatcher.h"

// Third party includes
#include "SDL.h"

namespace Falltergeist
{
namespace Audio
{
    class Mixer;
}
namespace Graphics
{
    class AnimatedPalette;
    class Renderer;
}
namespace Input
{
    class Mouse;
}
namespace Lua
{
    class Script;
}
namespace State
{
    class Location;
    class State;
}
namespace UI
{
    class FpsCounter;
    class TextArea;
}
class Exception;
class ResourceManager;
class Settings;

namespace Game
{
class DudeObject;
class Time;

class Game
{
public:
    static Game* getInstance();
    static void exportToLuaScript(Lua::Script* script);

    void shutdown();
    std::vector<std::shared_ptr<State::State>>* states();
    std::vector<std::shared_ptr<State::State>>* statesForRender();
    const std::vector<std::shared_ptr<State::State>>& statesForThinkAndHandle();
    void pushState(std::shared_ptr<State::State>);
    void setState(std::shared_ptr<State::State>);
    void popState();
    void run();
    void quit();
    void init(std::unique_ptr<Settings> settings);

    void handle();
    void think();
    void render();

    void setPlayer(DudeObject* player);
    DudeObject* player();
    Input::Mouse* mouse() const;
    Graphics::Renderer* renderer();
    Time* gameTime();
    State::Location* locationState();
    Audio::Mixer* mixer();

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    Settings* settings() const;
    Graphics::AnimatedPalette* animatedPalette();

    Event::Dispatcher* eventDispatcher();

protected:
    std::vector<int> _GVARS;
    std::vector<std::shared_ptr<State::State>> _states;
    std::vector<std::shared_ptr<State::State>> _statesForRender;
    std::vector<std::shared_ptr<State::State>> _statesForThinkAndHandle;
    std::vector<std::shared_ptr<State::State>> _statesForDelete;

    DudeObject* _player = nullptr;
    Time* _gameTime = nullptr;
    Graphics::Renderer* _renderer = nullptr;
    Input::Mouse* _mouse = nullptr;
    std::unique_ptr<Audio::Mixer> _mixer;
    UI::FpsCounter* _fpsCounter =  nullptr;
    std::shared_ptr<UI::TextArea> _mousePosition;
    std::shared_ptr<UI::TextArea> _currentTime;
    std::shared_ptr<UI::TextArea> _falltergeistVersion;
    std::unique_ptr<Settings> _settings;
    Graphics::AnimatedPalette* _animatedPalette = nullptr;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    Event::Dispatcher _eventDispatcher;

private:
    friend class Base::Singleton<Game>;
    void _initGVARS();

    Game();
    ~Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};

Game* getInstance();

}
}

#endif // FALLTERGEIST_GAME_GAME_H
