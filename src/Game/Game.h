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
#include <list>

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

class Game : public Event::Dispatcher
{
public:
    static Game* getInstance();
    static void exportToLuaScript(Lua::Script* script);

    void shutdown();
    std::vector<State::State*>* states();
    std::vector<State::State*>* statesForRender();
    const std::vector<State::State*>& statesForThinkAndHandle();
    void pushState(State::State* state);
    void setState(State::State* state);
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

protected:
    std::vector<int> _GVARS;
    std::vector<State::State*> _states;
    std::vector<State::State*> _statesForRender;
    std::vector<State::State*> _statesForThinkAndHandle;
    std::vector<State::State*> _statesForDelete;

    DudeObject* _player = nullptr;
    Time* _gameTime = nullptr;
    Graphics::Renderer* _renderer = nullptr;
    Input::Mouse* _mouse = nullptr;
    std::unique_ptr<Audio::Mixer> _mixer;
    UI::FpsCounter* _fpsCounter =  nullptr;
    UI::TextArea* _mousePosition = nullptr;
    UI::TextArea* _currentTime = nullptr;
    UI::TextArea* _falltergeistVersion = nullptr;
    std::unique_ptr<Settings> _settings;
    Graphics::AnimatedPalette* _animatedPalette = nullptr;
    bool _quit = false;
    SDL_Event _event;
    bool _initialized = false;
    std::list<std::pair<Event::Emitter*, Event::Event*>> _scheduledEvents;

private:
    friend class Base::Singleton<Game>;
    void _initGVARS();

    void postEventHandler(Event::Emitter* emitter, Event::Event* event) override final;
    void removeEventHandler(Event::Emitter* emitter) override final;

    Game();
    ~Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};

Game* getInstance();

}
}

#endif // FALLTERGEIST_GAME_GAME_H
