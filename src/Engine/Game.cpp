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

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../Engine/CrossPlatform.h"
#include "../Engine/Event.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Player.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"
#include "../Engine/Screen.h"
#include "../Engine/Mouse.h"
#include "../Engine/State.h"
#include "../States/LocationState.h"
#include "../UI/FpsCounter.h"
#include "../UI/TextArea.h"
#include "../Engine/AnimatedPalette.h"

// Third patry includes

namespace Falltergeist
{

Game& Game::getInstance()
{
    static Game instance;
    instance._initialize();
    return instance;
}

void Game::_initialize()
{
    if (_initialized) return;
    _initialized = true;

    debug("[GAME] - " + CrossPlatform::getVersion(), DEBUG_INFO);
    debug("[GAME] - Opensource Fallout 2 game engine", DEBUG_INFO);

    _resourceManager = new ResourceManager();
    _screen = new Screen(640, 480, 32);
    _mouse = new Mouse();
    _fpsCounter = new FpsCounter();
}

Game::~Game()
{
    delete _player;
    delete _screen;
    delete _mouse;
}

/**
 * Pushes a new state into the state stack
 * @param state
 */
void Game::pushState(State* state)
{
    if (!state->initialized()) state->init();
    _states.push_back(state);
}

/**
 * Pops the last state from the state stack
 */
void Game::popState()
{
    _deletedStates.push_back(_states.back());
    _states.pop_back();
}

/**
 * Clears the state stack and adds new state
 * @param state
 */
void Game::setState(State * state)
{
    while (_states.size() > 0)
    {
        popState();
    }
    if (!state->initialized()) state->init();
    pushState(state);
}

void Game::run()
{
    debug("[GAME] - Starting main loop", DEBUG_INFO);
    TextArea* falltergeistVersion = new TextArea(CrossPlatform::getVersion(), 3, 470);
    while (!_quit)
    {
        // Clean up states
        while (!_deletedStates.empty())
        {
            delete _deletedStates.back();
            _deletedStates.pop_back();
        }

        while(SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                _quit = true;
            }
            else
            {
                Event event = Event(&_event);
                
                // Screenshot function
                if (event.isKeyboardEvent() && event.SDLEvent()->type == SDL_KEYUP && event.keyCode() == SDLK_F12) // F12
                {
                    std::stringstream ss;
                    ss << SDL_GetTicks() << ".bmp";
                    SDL_SaveBMP(_screen->surface()->sdl_surface(), ss.str().c_str());
                    debug("[GAME] - Screenshot saved to " + ss.str(), DEBUG_INFO);
                }
                _states.back()->handle(&event);
            }
        }


        // thinking
        _states.back()->think();
        _fpsCounter->think();
        _mouse->think();
        Surface::animatedPalette->think();
        
        // render all states that is over the last fullscreen state
        _screen->clear();
        
        auto it = _states.end();
        do
        {
            --it; 
        }
        while(it != _states.begin() && !(*it)->fullscreen());
        
        for (; it != _states.end(); ++it)
        {
            (*it)->blit();
        }
        falltergeistVersion->blit(_screen->surface());
        _fpsCounter->blit(_screen->surface());
        _mouse->blit(_screen->surface());
        _screen->flip();
        SDL_Delay(1);
    }

    debug("[GAME] - Stopping main loop", DEBUG_INFO);
}

Screen* Game::screen()
{
    return _screen;
}

ResourceManager* Game::resourceManager()
{
    return _resourceManager;
}

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(Player* player)
{
    _player = player;
}

Player* Game::player()
{
    return _player;
}

Mouse* Game::mouse()
{
    return _mouse;
}

void Game::setLocation(Location* location)
{
    _location = location;
}

Location* Game::location()
{
    return _location;
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
    auto gam = ResourceManager::gamFileType("data/vault13.gam");
    for (auto gvar : *gam->GVARS())
    {
        _GVARS.push_back(gvar.second);
    }
}

std::vector<State*>* Game::states()
{
    return &_states;
}

}
