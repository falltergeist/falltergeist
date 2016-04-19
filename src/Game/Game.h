/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../Game/Time.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{
namespace Audio
{
    class Mixer;
}
namespace Event
{
    class Event;
    class Dispatcher;
    class Event;
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
namespace VFS
{
    class VFS;
}

class Exception;
class ResourceManager;
class Settings;

namespace Game
{
class DudeObject;

class Game
{
public:
    static Game* getInstance();

    void shutdown();
    /**
     * Returns pointer to a state at the top of stack.
     * @param offset optional offset (1 means second from the top, and so on)
     */
    State::State* topState(unsigned offset = 0) const;
    void pushState(State::State* state);
    void setState(State::State* state);
    void popState(bool doDelete = true);

    void run();
    void quit();
    void init(std::unique_ptr<Settings> settings);

    /**
     * @brief Handle all incoming events from OS (mouse, keyboard, etc.).
     */
    void handle();
    /**
     * @brief Process real-time logic.
     */
    void think();
    /**
     * @brief Render the game.
     */
    void render();

    void setPlayer(std::unique_ptr<DudeObject> player);
    DudeObject* player();
    Input::Mouse* mouse() const;
    Graphics::Renderer* renderer();
    Time* gameTime();
    State::Location* locationState();
    Audio::Mixer* mixer();
    Event::Dispatcher* eventDispatcher();

    void setGVAR(unsigned int number, int value);
    int GVAR(unsigned int number);

    Settings* settings() const;
    Graphics::AnimatedPalette* animatedPalette();

    unsigned int frame() const;

protected:
    std::vector<int> _GVARS;
    std::vector<std::unique_ptr<State::State>> _states;
    std::vector<std::unique_ptr<State::State>> _statesForDelete;

    Time _gameTime;

    unsigned int _frame = 0;

    std::unique_ptr<VFS::VFS> _vfs;
    std::unique_ptr<Graphics::Renderer> _renderer;
    std::unique_ptr<Audio::Mixer> _mixer;
    std::unique_ptr<Input::Mouse> _mouse;
    std::unique_ptr<Settings> _settings;
    std::unique_ptr<Graphics::AnimatedPalette> _animatedPalette;
    std::unique_ptr<Event::Dispatcher> _eventDispatcher;

    std::unique_ptr<UI::FpsCounter> _fpsCounter;
    std::unique_ptr<UI::TextArea> _mousePosition, _currentTime, _falltergeistVersion;

    std::unique_ptr<DudeObject> _player;

    bool _quit = false;
    bool _initialized = false;

    SDL_Event _event;

    std::vector<State::State*> _getVisibleStates();
    std::vector<State::State*> _getActiveStates();

private:
    friend class Base::Singleton<Game>;
    void _initGVARS();
    std::unique_ptr<Event::Event> _createEventFromSDL(const SDL_Event& sdlEvent);

    Game();
    ~Game();
    Game(Game const&) = delete;
    void operator=(Game const&) = delete;
};

Game* getInstance();

}
}

#endif // FALLTERGEIST_GAME_GAME_H
