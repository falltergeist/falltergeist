#ifndef FALLTERGEIST_GAME_H
#define FALLTERGEIST_GAME_H

#include <list>
#include <string>
#include <iostream>
#include <SDL/SDL.h>
#define VERSION "0.0.1"

namespace Falltergeist
{
class State;
class Exception;
class Screen;

class Game
{
protected:
    std::list<State*> _states;
    Screen * _screen;
    bool _quit;
    bool _initialized;
    SDL_Event _event;

public:
    Game(int width, int height, int bpp);
    ~Game();
    Screen * getScreen();
    void pushState(State * state);
    void setState(State * state);
    void popState();
    void run();
};

}
#endif // FALLTERGEIST_GAME_H
