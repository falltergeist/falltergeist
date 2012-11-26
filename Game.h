#ifndef FALLTERGEIST_GAME_H
#define FALLTERGEIST_GAME_H

#include <list>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#define VERSION "0.0.2"

namespace Falltergeist
{
class State;
class Exception;
class Screen;
class ResourceManager;

class Game
{
protected:
    ResourceManager * _resourceManager;
    std::list<State *> * _states;
    std::list<State *> * _deletedStates;
    Screen * _screen;
    bool _quit;
    SDL_Event _event;

public:
    Game(int width, int height, int bpp);
    ~Game();
    Screen * getScreen();
    ResourceManager * getResourceManager();
    void pushState(State * state);
    void setState(State * state);
    void popState();
    void run();
    void quit();
};

}
#endif // FALLTERGEIST_GAME_H
