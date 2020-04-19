#include "src/Game/Game.h"
#include "src/Logger.h"
#include "src/Settings.h"
#include "src/State/Start.h"
#include "src/UI/ResourceManager.h"

#include <memory>

using namespace Falltergeist;

int main(int argc, char* argv[])
{
    auto uiResourceManager = std::make_shared<UI::ResourceManager>();

    auto game = Game::Game::getInstance();
    game->setUIResourceManager(uiResourceManager);
    game->init(std::make_unique<Settings>());
    game->setState(std::make_unique<State::Start>(uiResourceManager));
    game->run();
    game->shutdown();
    return 0;
}
