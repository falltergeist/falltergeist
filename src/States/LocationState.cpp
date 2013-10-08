#include "../States/LocationState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Location.h"

namespace Falltergeist
{

LocationState::LocationState(Game * game) : State(game)
{
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    State::init();

    _game->resourceManager()->mapFileType("maps/artemple.map");

}


}
