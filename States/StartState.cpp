#include "States/StartState.h"
#include "States/MainMenuState.h"
#include "Engine/Game.h"

namespace Falltergeist
{

StartState::StartState(Game * game) : State(game)
{
}

StartState::~StartState()
{
}

void StartState::think()
{
    _game->setState(new MainMenuState(_game));
}

}

