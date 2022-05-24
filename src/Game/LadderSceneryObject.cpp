// Project includes
#include "../Game/LadderSceneryObject.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"
#include "../Logger.h"
#include "../Game/Game.h"
#include "../Game/Location.h"
#include "../State/Location.h"
#include "../PathFinding/Hexagon.h"
#include "../PathFinding/HexagonGrid.h"
#include "../Helpers/GameLocationHelper.h"
#include "../UI/ResourceManager.h"
#include "../Format/Txt/MapsFile.h"
#include "../ResourceManager.h"
#include "../State/WorldMap.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        LadderSceneryObject::LadderSceneryObject() : SceneryObject()
        {
            _subtype = Subtype::LADDER;
        }

        void LadderSceneryObject::use_p_proc(CritterObject* usedBy)
        {
            Object::use_p_proc(usedBy);
            if (script() && script()->overrides()) {
                return;
            }

            auto game = Game::getInstance();
            auto logger = std::make_shared<Logger>();

            Logger::info("LADDER") << "mapId=" << this->exitMapNumber() << " position=" << this->exitHexagonNumber() << " elevation=" << this->exitElevationNumber()  << std::endl;
            Logger::info("LADDER") << "current map: " << game->locationState()->location()->name() << std::endl;

            game->player()->stopMovement();

            if (this->exitMapNumber() != -1) {
                std::string mapName;

                if (this->exitMapNumber() > 0) {
                    auto mapsFile = ResourceManager::getInstance()->mapsTxt();
                    mapName = mapsFile->maps().at(this->exitMapNumber()).name;
                } else {
                    mapName = game->locationState()->location()->name();
                }

                auto locationState = new State::Location(
                    game->player(),
                    game->mouse(),
                    game->settings(),
                    game->renderer(),
                    game->mixer(),
                    game->gameTime(),
                    std::make_shared<UI::ResourceManager>(),
                    logger
                );
                locationState->setElevation(this->exitElevationNumber());

                Helpers::GameLocationHelper gameLocationHelper(logger);
                auto location = gameLocationHelper.getByName(mapName);
                location->setDefaultPosition(this->exitHexagonNumber());
                location->setDefaultElevationIndex(this->exitElevationNumber());
                locationState->setLocation(location);
                game->setState(locationState);

            } else {
                auto resourceManager = std::make_shared<UI::ResourceManager>();
                auto worldMapState = new State::WorldMap(resourceManager);
                game->setState(worldMapState);
            }
        }

        int LadderSceneryObject::exitMapNumber() const
        {
            return _exitMapNumber;
        }

        void LadderSceneryObject::setExitMapNumber(int value)
        {
            _exitMapNumber = value;
        }

        int LadderSceneryObject::exitElevationNumber() const
        {
            return _exitElevationNumber;
        }

        void LadderSceneryObject::setExitElevationNumber(int value)
        {
            _exitElevationNumber = value;
        }

        int LadderSceneryObject::exitHexagonNumber() const
        {
            return _exitHexagonNumber;
        }

        void LadderSceneryObject::setExitHexagonNumber(int value)
        {
            _exitHexagonNumber = value;
        }

    }
}
