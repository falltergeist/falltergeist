#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Helpers/GameLocationHelper.h"
#include "../PathFinding/Hexagon.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"

namespace Falltergeist
{
    namespace Helpers
    {
        GameLocationHelper::GameLocationHelper(std::shared_ptr<ILogger> logger)
        {
            this->logger = std::move(logger);
        }

        std::shared_ptr<Game::Location> GameLocationHelper::getInitialLocation() const
        {
            auto game = Game::Game::getInstance();
            auto initialLocation = getByName(game->settings()->initialLocation());
            if (!initialLocation) {
                auto defaultSettings = new Settings;
                Logger::warning("") << "No such map: `" << game->settings()->initialLocation() << "`; using default map" << std::endl;
                initialLocation = getByName(defaultSettings->initialLocation());
            }
            return initialLocation;
        }

        std::shared_ptr<Game::Location> GameLocationHelper::getByName(const std::string& name) const
        {
            std::string mapFileName = "maps/" + name + ".map";
            auto mapFile = ResourceManager::getInstance()->mapFileType(mapFileName);
            if (mapFile == nullptr) {
                return nullptr;
            }

            auto location = std::make_shared<Game::Location>(logger);
            location->loadFromMapFile(mapFile);
            return location;
        }
    }
}
