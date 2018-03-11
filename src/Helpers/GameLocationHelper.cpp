/*
 * Copyright 2012-2018 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../Helpers/GameLocationHelper.h"

#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"

namespace Falltergeist
{
    namespace Helpers
    {
        std::shared_ptr<Game::Location> GameLocationHelper::getInitialLocation() const
        {
            auto game = Game::getInstance();
            auto initialLocation = getByName(game->settings()->initialLocation());
            if (!initialLocation) {
                Settings defaultSettings;
                Logger::warning() << "No such map: `" << game->settings()->initialLocation() << "`; using default map" << std::endl;
                initialLocation = getByName(defaultSettings.initialLocation());
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

            auto location = std::make_shared<Game::Location>();
            location->loadFromMapFile(mapFile);
            return location;
        }
    }
}
