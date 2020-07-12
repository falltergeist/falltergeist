#include "../State/ElevatorDialog.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include "../State/MainMenu.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/ElevatorProgress.h"
#include "../UI/TextArea.h"
#include "../Audio/Mixer.h"
#include "../Format/Enums.h"
#include "../Game/Elevator.h"
#include "../Helpers/StateElevatorHelper.h"
#include "../Helpers/GameLocationHelper.h"
#include "../Helpers/StateLocationHelper.h"
#include "../Format/Txt/MapsFile.h"
#include "../PathFinding/Hexagon.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
    using Helpers::StateLocationHelper;
    using Helpers::GameLocationHelper;

    namespace State
    {
        ElevatorDialog::ElevatorDialog(std::shared_ptr<UI::IResourceManager> resourceManager, std::shared_ptr<ILogger> logger, uint32_t elevatorType, uint32_t elevatorLevel) : State()
        {
            this->resourceManager = std::move(resourceManager);
            this->logger = std::move(logger);
            this->_elevatorType = elevatorType;
            this->_elevatorLevel = elevatorLevel;
            imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(this->resourceManager);
        }

        void ElevatorDialog::init()
        {
            if (_initialized) {
                return;
            }
            State::init();
            this->_pressedButton = -1;

            setModal(true);
            setFullscreen(false);

            logger->info() << "[ELEVATOR] panel called: type = " << this->_elevatorType  << " level = " << this->_elevatorLevel << std::endl;

            //Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/elevator.acm");

            auto elevatorHelper = Helpers::StateElevatorHelper(logger);
            auto elevator = elevatorHelper.getByType(this->_elevatorType);
            this->_elevator = elevatorHelper.getByType(this->_elevatorType);

            auto panelFrmLstId = 143;
            auto labelsFrmLstId = -1;

            if (elevator->panelFID() < 100000000) {
                panelFrmLstId = elevator->panelFID();
            }

            if (elevator->labelsFID() < 100000000) {
                labelsFrmLstId = elevator->labelsFID();
            }

            logger->info() << "loaded elevator frm=" << panelFrmLstId  << std::endl;
            logger->info() << "loaded elevator labels frm=" << labelsFrmLstId << std::endl;

            int totalButtons = elevator->size();
            auto bgfid = ((unsigned int)FRM_TYPE::INTERFACE << 24) | panelFrmLstId;
            auto bgfrmFilename = ResourceManager::getInstance()->FIDtoFrmName(bgfid);
            logger->info() << "bgfrmFilename = " << bgfrmFilename << std::endl;

            //auto background = resourceManager->getImage("art/intrface/el_bos.frm");
            auto background = resourceManager->getImage(bgfrmFilename);

            auto panelHeight = Game::Game::getInstance()->locationState()->playerPanel()->size().height();
            auto backgroundPos = (Game::Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;

            for (int i = 0; i < totalButtons; i++) {
                auto ypos = i * 60 + 42;
                auto button = imageButtonFactory->getByType(ImageButtonType::ELEVATOR_CIRCLE, backgroundPos + Point(10, ypos));
                button->mouseClickHandler().add(std::bind(&ElevatorDialog::doElevate, this, i));
                _buttons.push_back(button);
            }

            background->setPosition(backgroundPos);
            addUI(background);

            if (labelsFrmLstId != -1)
            {
                auto labelsfid = ((unsigned int)FRM_TYPE::INTERFACE << 24) | labelsFrmLstId;
                auto labelsfrmFilename = ResourceManager::getInstance()->FIDtoFrmName(labelsfid);
                logger->info() << "labelsfrmFilename = " << labelsfrmFilename << std::endl;
                auto labels = resourceManager->getImage(labelsfrmFilename);
                labels->setPosition(backgroundPos + Point(0, 36));
                addUI(labels);
            }

            auto elevatorProgress = new UI::ElevatorProgress(
                static_cast<uint8_t>(12), // 0..12
                backgroundPos + Point(122, 42)
            );

            addUI(elevatorProgress);

            for (int i = 0; i < totalButtons; i++) {
                addUI(_buttons.at(i));
            }
        }

        void ElevatorDialog::doElevate(int pressedButtonIndex)
        {
            logger->info() << "[ELEVATOR] button pressed = " << pressedButtonIndex << std::endl;
            if (pressedButtonIndex >= 0) {
                auto floors  = _elevator->floors();
                auto destination = floors.at(pressedButtonIndex);
                auto mapsFile = ResourceManager::getInstance()->mapsTxt();
                std::string mapName = mapsFile->maps().at(destination->mapId).name;

                logger->info() << "[ELEVATOR] destination map = " << destination->mapId << " elevation=" << destination->elevation << " position=" << destination->position << std::endl;
                logger->info() << "[ELEVATOR] destination map file = " << mapName << std::endl;
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/elevato1.acm");
                Game::Game::getInstance()->popState();

                if (Game::Game::getInstance()->locationState()->currentMapIndex() == destination->mapId) {
                    logger->info() << "[ELEVATOR] same location";
                    Game::Game::getInstance()->locationState()->setElevation(destination->elevation);
                    Game::Game::getInstance()->locationState()->setPosition(Hexagon(destination->position).position());
                } else {
                    logger->info() << "[ELEVATOR] loading map...";
                    Helpers::GameLocationHelper gameLocationHelper(logger);
                    Helpers::StateLocationHelper stateLocationHelper(logger);

                    auto game = Game::Game::getInstance();
                    game->setState(stateLocationHelper.getCustomLocationState(mapName, destination->elevation, destination->position));
                }
            }
        }

        void ElevatorDialog::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                case SDLK_n:
                    Game::Game::getInstance()->popState();
                    break;
                case SDLK_RETURN:
                case SDLK_y:
                    doElevate(-1);
                    Game::Game::getInstance()->popState();
                    break;
            }
        }

        void ElevatorDialog::onStateActivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void ElevatorDialog::onStateDeactivate(Event::State* event)
        {
            Game::Game::getInstance()->mouse()->popState();
        }
    }
}
