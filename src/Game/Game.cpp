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

// Related headers
#include "../Game/Game.h"

// C++ standard includes
#include <algorithm>
#include <sstream>

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Base/StlFeatures.h"
#include "../CrossPlatform.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Game/Time.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../Lua/Script.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/State.h"
#include "../State/Location.h"
#include "../UI/FpsCounter.h"
#include "../UI/TextArea.h"

// Third patry includes
#include <libfalltergeist/Gam/File.h>
#include <SDL_image.h>

namespace Falltergeist
{
namespace Game
{

using namespace Base;

Game* getInstance()
{
    return ::Falltergeist::Game::Game::getInstance();
}

Game::Game()
{
}

Game* Game::getInstance()
{
    return Base::Singleton<Game>::get();
}

void Game::init(std::unique_ptr<Settings> settings)
{
    if (_initialized) return;
    _initialized = true;

    _settings = std::move(settings);

    _renderer = make_unique<Graphics::Renderer>(_settings->screenWidth(), _settings->screenHeight());

    Logger::info("GAME") << CrossPlatform::getVersion() << std::endl;
    Logger::info("GAME") << "Opensource Fallout 2 game engine" << std::endl;

    SDL_setenv("SDL_VIDEO_CENTERED", "1", 1);

    // Force ResourceManager to initialize instance.
    (void)ResourceManager::getInstance();

    renderer()->init();

    std::string version = CrossPlatform::getVersion();
    renderer()->setCaption(version.c_str());

    _mixer = make_unique<Audio::Mixer>();
    _mouse = make_unique<Input::Mouse>();
    _fpsCounter = make_unique<UI::FpsCounter>(renderer()->width() - 42, 2);

    version += " " + to_string(renderer()->size());
    version += " " + renderer()->name();

    _falltergeistVersion = make_unique<UI::TextArea>(version, 3, renderer()->height() - 10);
    _mousePosition = make_unique<UI::TextArea>("", renderer()->width() - 55, 14);
    _animatedPalette = make_unique<Graphics::AnimatedPalette>();
    _currentTime = make_unique<UI::TextArea>("", renderer()->size() - Point(150, 10));

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

Game::~Game()
{
    shutdown();
}

void Game::shutdown()
{
    _mixer.reset();
    ResourceManager::getInstance()->shutdown();
    while (!_states.empty()) popState();
    _settings.reset();
}

void Game::pushState(State::State* state)
{
    _states.push_back(std::unique_ptr<State::State>(state));
    if (!state->initialized()) state->init();
}

void Game::popState()
{
    if (_states.size() == 0) return;

    auto& state = _states.back();
    auto findIt = std::find(_activeStates.rbegin(), _activeStates.rend(), state.get());
    if (findIt != _activeStates.rend())
    {
        _activeStates.erase(findIt.base() - 1);
    }
    auto event = new Event::State("deactivate");
    state->emitEvent(event);
    delete event;

    _statesForDelete.emplace_back(std::move(state));
    _states.pop_back();
}

void Game::setState(State::State* state)
{
    while (!_states.empty()) popState();
    pushState(state);
}

void Game::run()
{
    Logger::info("GAME") << "Starting main loop" << std::endl;
    while (!_quit)
    {
        _activeStates = _getActiveStates();
        handle();
        think();
        render();
        SDL_Delay(1);
        _statesForDelete.clear();
    }
    Logger::info("GAME") << "Stopping main loop" << std::endl;
}

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(DudeObject* player)
{
    _player = player;
}

DudeObject* Game::player()
{
    return _player;
}

Input::Mouse* Game::mouse() const
{
    return _mouse.get();
}

State::Location* Game::locationState()
{
    for (auto& state : _states)
    {
        auto location = dynamic_cast<State::Location*>(state.get());
        if (location)
        {
            return location;
        }
    }
    return 0;
}

void Game::setGVAR(unsigned int number, int value)
{
    _initGVARS();
    if (number >= _GVARS.size())
    {
        throw Exception("Game::setGVAR(num, value) - num out of range: " + std::to_string(number));
    }
    _GVARS.at(number) = value;
}

int Game::GVAR(unsigned int number)
{
    _initGVARS();
    if (number >= _GVARS.size())
    {
        throw Exception("Game::GVAR(num) - num out of range: " + std::to_string(number));
    }
    return _GVARS.at(number);
}

void Game::_initGVARS()
{
    if (_GVARS.size() > 0) return;
    auto gam = ResourceManager::getInstance()->gamFileType("data/vault13.gam");
    for (auto gvar : *gam->GVARS())
    {
        _GVARS.push_back(gvar.second);
    }
}

State::State* Game::topState(unsigned offset) const
{
    return (_states.rbegin() + offset)->get();
}

std::vector<State::State*> Game::_getVisibleStates()
{
    std::vector<State::State*> subset;
    // we must render all states from last fullscreen state to the top of stack
    auto it = _states.end();
    do
    {
        --it;
    }
    while (it != _states.begin() && !(*it)->fullscreen());

    for (; it != _states.end(); ++it)
    {
        subset.push_back((*it).get());
    }
    return subset;
}

std::vector<State::State*> Game::_getActiveStates()
{
    // we must handle all states from top to bottom of stack
    std::vector<State::State*> subset;

    auto it = _states.rbegin();
    // active states
    for (; it != _states.rend(); ++it)
    {
        auto& state = *it;
        if (!state->active())
        {
            auto event = new Event::State("activate");
            state->emitEvent(event);
            state->setActive(true);
            delete event;
        }
        subset.push_back(state.get());
        if (state->modal() || state->fullscreen())
        {
            ++it;
            break;
        }
    }
    // not active states
    for (; it != _states.rend(); ++it)
    {
        auto& state = *it;
        if (state->active())
        {
            auto event = new Event::State("deactivate");
            state->emitEvent(event);
            state->setActive(false);
            delete event;
        }
    }
    return subset;
}

Graphics::Renderer* Game::renderer()
{
    return _renderer.get();
}

Settings* Game::settings() const
{
    return _settings.get();
}

void Game::handle()
{
    if (_renderer->fading()) return;

    while (SDL_PollEvent(&_event))
    {
        if (_event.type == SDL_QUIT)
        {
            _quit = true;
        }
        else
        {
            Event::Mouse* mouseEvent = nullptr;
            Event::Keyboard* keyboardEvent = nullptr;
            switch (_event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                {
                    SDL_Keymod mods = SDL_GetModState();
                    mouseEvent = new Event::Mouse((_event.type == SDL_MOUSEBUTTONDOWN) ? "mousedown" : "mouseup");
                    mouseEvent->setPosition({_event.button.x, _event.button.y});
                    mouseEvent->setLeftButton(_event.button.button == SDL_BUTTON_LEFT);
                    mouseEvent->setRightButton(_event.button.button == SDL_BUTTON_RIGHT);
                    mouseEvent->setShiftPressed(mods & KMOD_SHIFT);
                    mouseEvent->setControlPressed(mods & KMOD_CTRL);
                    for (auto state : _activeStates) state->handle(mouseEvent);
                    break;
                }
                case SDL_MOUSEMOTION:
                {
                    mouseEvent = new Event::Mouse("mousemove");
                    mouseEvent->setPosition({_event.motion.x, _event.motion.y});
                    mouseEvent->setOffset({_event.motion.xrel,_event.motion.yrel});
                    for (auto state : _activeStates) state->handle(mouseEvent);
                    break;
                }
                case SDL_KEYDOWN:
                {
                    keyboardEvent = new Event::Keyboard("keydown");
                    keyboardEvent->setKeyCode(_event.key.keysym.sym);
                    keyboardEvent->setAltPressed(_event.key.keysym.mod & KMOD_ALT);
                    keyboardEvent->setShiftPressed(_event.key.keysym.mod & KMOD_SHIFT);
                    keyboardEvent->setControlPressed(_event.key.keysym.mod & KMOD_CTRL);
                    for (auto state : _activeStates) state->handle(keyboardEvent);
                    break;
                }
                case SDL_KEYUP:
                {
                    keyboardEvent = new Event::Keyboard("keyup");
                    keyboardEvent->setKeyCode(_event.key.keysym.sym);
                    keyboardEvent->setAltPressed(_event.key.keysym.mod & KMOD_ALT);
                    keyboardEvent->setShiftPressed(_event.key.keysym.mod & KMOD_SHIFT);
                    keyboardEvent->setControlPressed(_event.key.keysym.mod & KMOD_CTRL);;
                    for (auto state : _activeStates) state->handle(keyboardEvent);

                    if (keyboardEvent->keyCode() == SDLK_F12)
                    {
                        auto texture = renderer()->screenshot();
                        std::string name = std::to_string(SDL_GetTicks()) +  ".bmp";
                        SDL_SaveBMP(texture->sdlSurface(), name.c_str());
                        Logger::info("GAME") << "Screenshot saved to " + name << std::endl;
                    }
                    break;
                }
            }
            delete keyboardEvent;
            delete mouseEvent;
        }
    }
}

void Game::think()
{
    _fpsCounter->think();
    _mouse->think();

    _animatedPalette->think();

    *_mousePosition = "";
    *_mousePosition << mouse()->position().x() << " : " << mouse()->position().y();

    *_currentTime = "";
    *_currentTime << _gameTime.year()  << "-" << _gameTime.month()   << "-" << _gameTime.day() << " "
                  << _gameTime.hours() << ":" << _gameTime.minutes() << ":" << _gameTime.seconds() << " " << _gameTime.ticks();

    if (_renderer->fading())
    {
        return;
    }

    for (auto state : _activeStates)
    {
        state->think();
    }
}

void Game::render()
{
    renderer()->beginFrame();

    for (auto state : _getVisibleStates())
    {
        state->render();
    }

    if (settings()->displayFps())
    {
        _fpsCounter->render();
    }

    _falltergeistVersion->render();

    if (settings()->displayMousePosition())
    {
        _mousePosition->render();
    }

    _currentTime->render();
    _mouse->render();
    renderer()->endFrame();
}

Graphics::AnimatedPalette* Game::animatedPalette()
{
    return _animatedPalette.get();
}

Time* Game::gameTime()
{
    return &_gameTime;
}

Audio::Mixer* Game::mixer()
{
    return _mixer.get();
}

}
}
