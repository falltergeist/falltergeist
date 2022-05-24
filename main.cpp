// Project includes
#include "src/Exception.h"
#include "src/Game/Game.h"
#include "src/Logger.h"
#include "src/Settings.h"
#include "src/State/Start.h"
#include "src/UI/ResourceManager.h"

// Third-party includes

// stdlib
#include <memory>

using namespace Falltergeist;

int main(int argc, char* argv[])
{
    std::shared_ptr<ILogger> logger = std::make_shared<Logger>();

    try
    {
        auto game = Game::Game::getInstance(logger);
        auto uiResourceManager = std::make_shared<UI::ResourceManager>();
        game->setUIResourceManager(uiResourceManager);
        game->init(std::unique_ptr<Settings>(new Settings()));
        game->setState(new State::Start(uiResourceManager, logger));
        game->run();
        game->shutdown();
        return 0;
    }
    catch(const Exception &e)
    {
        logger->critical() << e.what() << std::endl;

#if defined(_WIN32) || defined(WIN32)
        system("PAUSE");
#endif
    }
    return 1;
}

