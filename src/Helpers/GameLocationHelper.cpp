#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Helpers/GameLocationHelper.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"

namespace Falltergeist
{
    namespace Helpers
    {
        std::unique_ptr<Game::Location> GameLocationHelper::getInitialLocation() const
        {
            auto game = Game::getInstance();
            auto initialLocation = getByName(game->settings()->initialLocation());
            if (!initialLocation) {
                auto defaultSettings = new Settings;
                Logger::warning() << "No such map: `" << game->settings()->initialLocation() << "`; using default map" << std::endl;
                initialLocation = getByName(defaultSettings->initialLocation());
            }
            return initialLocation;
        }

        std::unique_ptr<Game::Location> GameLocationHelper::getByName(const std::string& name) const
        {
            std::string mapFileName = "maps/" + name + ".map";
            auto mapFile = ResourceManager::getInstance()->mapFileType(mapFileName);
            if (mapFile == nullptr) {
                return nullptr;
            }

            auto location = std::make_unique<Game::Location>();
            location->loadFromMapFile(mapFile);
            return location;
        }
    }
}
