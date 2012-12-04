#include "../States/StartState.h"
#include "../States/MainMenuState.h"
#include "../Engine/Game.h"


#include "../States/PlayerEditState.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Player.h"

namespace Falltergeist
{

StartState::StartState(Game * game) : State(game)
{
    std::cout << "StartState..." << std::endl;
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

