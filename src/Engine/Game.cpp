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
#include "../Engine/Screen.h"
#include "../Engine/Mouse.h"
#include "../Engine/State.h"
#include "../UI/FpsCounter.h"
#include "../UI/TextArea.h"
#include "../Engine/AnimatedPalette.h"

// Third patry includes

namespace Falltergeist
{

Game::Game(unsigned int width, unsigned int height, unsigned int bpp)
{
    debug(CrossPlatform::getVersion() + "\n", DEBUG_INFO);
    debug("Opensource Fallout 2 game engine\n", DEBUG_INFO);

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        debug("Initializing video - [FAIL]\n", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
    debug("Initializing video - [OK]\n", DEBUG_INFO);

    std::string caption = CrossPlatform::getVersion();

    SDL_WM_SetCaption(caption.c_str(), 0);
    putenv(strdup("SDL_VIDEO_CENTERED=1"));

    _resourceManager = new ResourceManager();
    _screen = new Screen(width, height,bpp);
    _mouse = new Mouse();
    _fpsCounter = new FpsCounter();
    _quit = false;
    _states = new std::vector<State *>;
    _deletedStates = new std::vector<State *>;
    _player = 0;
}

Game::~Game()
{
    delete _player;
    delete _screen;
    delete _mouse;

    while (!_states->empty())
    {
        delete _states->back();
        _states->pop_back();;
    }
    delete _states;

    while (!_deletedStates->empty())
    {
        delete _deletedStates->back();
        _deletedStates->pop_back();;
    }
    delete _deletedStates;
}

/**
 * Pushes a new state into the state stack
 * @param state
 */
void Game::pushState(State * state)
{
    _states->push_back(state);
}

/**
 * Pops the last state from the state stack
 */
void Game::popState()
{
    _deletedStates->push_back(_states->back());
    _states->pop_back();
}

/**
 * Clears the state stack and adds new state
 * @param state
 */
void Game::setState(State * state)
{
    while (_states->size() > 0)
    {
        popState();
    }
    pushState(state);
}

void Game::run()
{

    debug("Starting main loop...\n", DEBUG_INFO);
    TextArea * falltergeistVersion = new TextArea(CrossPlatform::getVersion(), 3, 470);
    while (!_quit)
    {
        // Clean up states
        while (!_deletedStates->empty())
        {
            delete _deletedStates->back();
            _deletedStates->pop_back();
        }

        // Init current state
        if (!_states->back()->initialized) _states->back()->init();

        while(SDL_PollEvent(&_event))
        {
            if (_event.type == SDL_QUIT)
            {
                _quit = true;
            }
            else
            {
                Event event = Event(&_event);
                //_screen->handle(&event);
                //_cursor->handle(&event);
                //_fpsCounter->handle(&event);

                // Screenshot function
                if (event.isKeyboardEvent() && event.SDLEvent()->type == SDL_KEYUP && event.keyCode() == 96)
                {
                    std::stringstream ss;
                    ss << SDL_GetTicks() << ".bmp";
                    SDL_SaveBMP(_screen->surface()->sdl_surface(), ss.str().c_str());
                    debug("Screenshot saved to " + ss.str() + "\n", DEBUG_INFO);
                }

                _states->back()->handle(&event);

            }
        }


        // Rendering
        _states->back()->think();
        _fpsCounter->think();
        _mouse->think();
        Surface::animatedPalette->think();

        // render all states that is over the last fullscreen state
        _screen->clear();
        std::vector<State*>::iterator i = _states->end();
        do { --i; }
        while(i != _states->begin() && !(*i)->isFullscreen());
        for (; i != _states->end(); ++i) (*i)->blit();
        falltergeistVersion->blit(_screen->surface());
        _fpsCounter->blit(_screen->surface());
        _mouse->blit(_screen->surface());
        _screen->flip();
        SDL_Delay(1);
    }

    debug("Stopping main loop...[OK]\n", DEBUG_INFO);
}

Screen * Game::screen()
{
    return _screen;
}

ResourceManager * Game::resourceManager()
{
    return _resourceManager;
}

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(Player * player)
{
    _player = player;
}

Player * Game::player()
{
    return _player;
}

Mouse * Game::mouse()
{
    return _mouse;
}

}
