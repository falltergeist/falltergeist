#include "StartState.h"
#include "MainMenuState.h"
#include "Game.h"

namespace Falltergeist
{

StartState::StartState(Game * game) : State(game)
{
}

void StartState::init()
{
    State::init();
}

void StartState::think()
{
    _game->setState(new MainMenuState(_game));
}

}

