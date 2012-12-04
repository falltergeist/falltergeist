#include "src/States/StartState.h"
#include "src/States/MainMenuState.h"
#include "src/Engine/Game.h"


#include "src/States/PlayerEditState.h"
#include "src/Engine/ResourceManager.h"
#include "src/Engine/Player.h"

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
    _game->setPlayer(new Player(ResourceManager::getGcdFileType("premade/combat.gcd")));
    _game->setState(new PlayerEditState(_game));
    
    //_game->setState(new MainMenuState(_game));
}

}

