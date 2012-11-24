#include "Game.h"
#include "Exception.h"
#include "State.h"
#include "Screen.h"
#include "Event.h"
#include "ResourceManager.h"

namespace Falltergeist
{

Game::Game(int width, int height, int bpp) : _states()
{
    std::cout << "Falltergeist - version " << VERSION << std::endl;
    std::cout << "Opensource fallout 1/2 game engine" << std::endl;
    std::cout << "Initializing video...";

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "[FAIL]" << std::endl;
        throw Exception(SDL_GetError());
    }
    std::cout << "[OK]" << std::endl;

    // Window caption
    std::string caption = "Falltergeist ";
    caption.append(VERSION);
    SDL_WM_SetCaption(caption.c_str(), 0);

    std::cout << "Loading resource manager..." << std::endl;
    _resourceManager = new ResourceManager();

    _screen = new Screen(width, height,bpp);
    _quit = false;
    _initialized = false;
}

Game::~Game()
{
    delete _screen;
}

/**
 * Pushes a new state into the state stack
 * @param state
 */
void Game::pushState(State * state)
{
    _states.push_back(state);
}

/**
 * Pops the last state from the state stack
 */
void Game::popState()
{
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
    pushState(state);
}

void Game::run()
{
    std::cout << "Starting main loop..." << std::endl;

    while (!_quit)
    {
        if (!_initialized)
        {
            _states.back()->init();
            _initialized = true;
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
                //_screen->handle(&event);
                //_cursor->handle(&event);
                //_fpsCounter->handle(&event);
                _states.back()->handle(&event);

            }
        }

        _states.back()->think();

        // Rendering
        if (_initialized)
        {
            _screen->clear();
            // render all states that is over the last fullscreen state
            std::list<State*>::iterator i = _states.end();
            do
            {
                --i;
            }
            while(i != _states.begin() && !(*i)->isFullscreen());

            for (; i != _states.end(); ++i)
            {
                (*i)->blit();
            }
            //_fpsCounter->blit(_screen->getSurface());
            //_cursor->blit(_screen->getSurface());
        }
        _screen->flip();

        SDL_Delay(1);
    }

    std::cout << "Stopping main loop...[OK]" << std::endl;
}

Screen * Game::getScreen()
{
    return _screen;
}

ResourceManager * Game::getResourceManager()
{
    return _resourceManager;
}

}
