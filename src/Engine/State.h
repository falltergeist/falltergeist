#ifndef FALLTERGEIST_STATE_H
#define FALLTERGEIST_STATE_H

#include <vector>

namespace Falltergeist
{
class Game;
class Surface;
class Event;

class State
{
protected:
    Game * _game;
    std::vector<Surface *> _surfaces;
    bool _isFullscreen;
public:
    State(Game * game);
    bool initialized;
    virtual ~State();
    void add(Surface * surface);
    void blit();
    bool isFullscreen();
    virtual void init();
    virtual void think();
    virtual void handle(Event * event);
};

}
#endif // FALLTERGEIST_STATE_H
