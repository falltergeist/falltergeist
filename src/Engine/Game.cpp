#include "src/Engine/Game.h"
#include "src/Engine/Exception.h"
#include "src/Engine/State.h"
#include "src/Engine/Screen.h"
#include "src/Engine/Event.h"
#include "src/Engine/ResourceManager.h"
#include "src/Engine/Player.h"
#include "src/UI/TextArea.h"
#include "src/UI/FpsCounter.h"

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
    _fpsCounter = new FpsCounter();
    _quit = false;
    _states = new std::list<State *>;
    _deletedStates = new std::list<State *>;
    _player = 0;
}

Game::~Game()
{
    delete _screen; _screen = 0;
    delete _states; _states = 0;
    delete _deletedStates; _deletedStates = 0;
    delete _player; _player = 0;
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
    std::cout << "Starting main loop..." << std::endl;
    TextArea * falltergeistVersion = new TextArea("Falltergeist "VERSION, 3, 470);
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
                _states->back()->handle(&event);

            }
        }


        // Rendering
        _screen->clear();
        _states->back()->think();
        _fpsCounter->think();
        // render all states that is over the last fullscreen state
        std::list<State*>::iterator i = _states->end();
        do { --i; }
        while(i != _states->begin() && !(*i)->isFullscreen());
        for (; i != _states->end(); ++i) (*i)->blit();
        falltergeistVersion->blit(_screen->getSurface());
        _fpsCounter->blit(_screen->getSurface());
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

void Game::quit()
{
    _quit = true;
}

void Game::setPlayer(Player * player)
{
    _player = player;
}

Player * Game::getPlayer()
{
    return _player;
}

}
