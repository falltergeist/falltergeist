#include <memory>
#include "src/Exception.h"
#include "src/Game/Game.h"
#include "src/Logger.h"
#include "src/Settings.h"
#include "src/State/Start.h"

using namespace Falltergeist;

int main(int argc, char* argv[])
{
    try
    {
        auto game = Game::Game::getInstance();
        game->init(std::unique_ptr<Settings>(new Settings()));
        game->setState(new State::Start());
        game->run();
        game->shutdown();
        return 0;
    }
    catch(const Exception &e)
    {
        Logger::critical() << e.what() << std::endl;

#if defined(_WIN32) || defined(WIN32)
        system("PAUSE");
#endif
    }
    /*
    catch (const std::exception &e)
    {
        Logger::critical() << e.what() << std::endl;
    }
    */
    return 1;
}

