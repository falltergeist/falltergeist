#include "SaveMenuState.h"
#include "Game.h"
#include "ResourceManager.h"

namespace Falltergeist
{

SaveMenuState::SaveMenuState(Game * game) : State(game)
{
    _isFullscreen = true;

}

void SaveMenuState::think()
{

}

void SaveMenuState::init()
{

}

void SaveMenuState::onButton2Click()
{
    _game->popState();
}

}
