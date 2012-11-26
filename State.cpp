#include "State.h"
#include "Surface.h"
#include "Game.h"
#include "Screen.h"
#include "InteractiveSurface.h"

namespace Falltergeist
{

State::State(Game * game) : _game(game), _surfaces(), _isFullscreen(false), initialized(false)
{
}

State::~State()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        delete *i;
    }
}

void State::init()
{
    initialized = true;
}

void State::think()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->think();
    }
}

void State::blit()
{
    for (std::vector<Surface *>::iterator i = _surfaces.begin(); i < _surfaces.end(); i++)
    {
        (*i)->blit(_game->getScreen()->getSurface());
    }
}

bool State::isFullscreen()
{
    return _isFullscreen;
}

void State::add(Surface * surface)
{
    _surfaces.push_back(surface);
}

void State::handle(Event * event)
{
    for (std::vector<Surface *>::reverse_iterator i = _surfaces.rbegin(); i < _surfaces.rend(); i++)
    {
        InteractiveSurface * surface = dynamic_cast<InteractiveSurface *>(*i);
        if (surface != 0)
        {
            surface->handle(event,this);
        }
    }
}

}
