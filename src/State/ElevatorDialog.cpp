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
    namespace State
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Helpers::StateLocationHelper;
        using Helpers::GameLocationHelper;
        using Point = Graphics::Point;

        ElevatorDialog::ElevatorDialog(
            std::shared_ptr<UI::IResourceManager> resourceManager,
            std::shared_ptr<Input::Mouse> mouse,
            std::shared_ptr<ILogger> logger,
            uint32_t elevatorType,
            uint32_t elevatorLevel
        ) : State(mouse), _logger(logger), _resourceManager(resourceManager), _elevatorType(elevatorType), _elevatorLevel(elevatorLevel) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
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

            _logger->info() << "[ELEVATOR] panel called: type = " << this->_elevatorType  << " level = " << this->_elevatorLevel << std::endl;

            auto elevatorHelper = Helpers::StateElevatorHelper(_logger);
            this->_elevator = elevatorHelper.getByType(this->_elevatorType);

            auto panelFrmLstId = 143;
            auto labelsFrmLstId = -1;
            uint8_t elevatorPosition = 0;
            uint8_t elevatorScale = 0;

            if (_elevator->size() > 1) {
                elevatorScale = (uint8_t)(12 / (_elevator->size() - 1));
            }

            if (_elevator->size() == 2 && _elevatorLevel >= 2) {
                auto level = _elevatorLevel - _elevator->size();
                if (level == 1) {
                    elevatorPosition = elevatorScale;
                }
            } else {
                elevatorPosition = _elevatorLevel * elevatorScale;
            }

            if (this->_elevator->panelFID() < 100000000) {
                panelFrmLstId = this->_elevator->panelFID();
            }

            if (this->_elevator->labelsFID() < 100000000) {
                labelsFrmLstId = this->_elevator->labelsFID();
            }

            _logger->debug() << "loaded elevator frm=" << panelFrmLstId  << std::endl;
            _logger->debug() << "loaded elevator labels frm=" << labelsFrmLstId << std::endl;

            int totalButtons = this->_elevator->size();
            auto bgfid = ((unsigned int)FRM_TYPE::INTERFACE << 24) | panelFrmLstId;
            auto bgfrmFilename = ResourceManager::getInstance()->FIDtoFrmName(bgfid);
            _logger->debug() << "bgfrmFilename = " << bgfrmFilename << std::endl;

            auto background = _resourceManager->getImage(bgfrmFilename);
            auto panelHeight = Game::Game::getInstance()->locationState()->playerPanel()->size().height();
            auto backgroundPos = (Game::Game::getInstance()->renderer()->size() - background->size() - Point(0, panelHeight)) / 2;

            for (int i = 0; i < totalButtons; i++) {
                auto ypos = i * 60 + 42;
                auto button = _imageButtonFactory->getByType(ImageButtonType::ELEVATOR_CIRCLE, backgroundPos + Point(10, ypos));
                button->mouseClickHandler().add(std::bind(&ElevatorDialog::doElevate, this, i));
                _buttons.push_back(button);
            }

            background->setPosition(backgroundPos);
            addUI(background);

            if (labelsFrmLstId != -1)
            {
                auto labelsfid = ((unsigned int)FRM_TYPE::INTERFACE << 24) | labelsFrmLstId;
                auto labelsfrmFilename = ResourceManager::getInstance()->FIDtoFrmName(labelsfid);
                _logger->debug() << "labelsfrmFilename = " << labelsfrmFilename << std::endl;
                auto labels = _resourceManager->getImage(labelsfrmFilename);
                labels->setPosition(backgroundPos + Point(0, 36));
                addUI(labels);
            }

            auto elevatorProgress = new UI::ElevatorProgress(
                static_cast<uint8_t>(elevatorPosition), // 0..12
                backgroundPos + Point(122, 42)
            );

            addUI(elevatorProgress);

            for (int i = 0; i < totalButtons; i++) {
                addUI(_buttons.at(i));
            }
        }

        void ElevatorDialog::doElevate(int pressedButtonIndex)
        {
            _logger->info() << "[ELEVATOR] button pressed = " << pressedButtonIndex << std::endl;
            if (pressedButtonIndex >= 0) {
                auto floors  = _elevator->floors();
                auto destination = floors.at(pressedButtonIndex);
                auto mapsFile = ResourceManager::getInstance()->mapsTxt();
                std::string mapName = mapsFile->maps().at(destination->mapId).name;

                _logger->info() << "[ELEVATOR] destination map = " << destination->mapId << " elevation=" << destination->elevation << " position=" << destination->position << std::endl;
                _logger->info() << "[ELEVATOR] destination map file = " << mapName << std::endl;
                Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/elevato1.acm");
                //Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/elevator.acm");
                Game::Game::getInstance()->popState();

                if (Game::Game::getInstance()->locationState()->currentMapIndex() == destination->mapId) {
                    _logger->info() << "[ELEVATOR] same location";
                    Game::Game::getInstance()->locationState()->setElevation(destination->elevation);
                    Game::Game::getInstance()->locationState()->setPosition(Hexagon(destination->position).position());
                } else {
                    _logger->info() << "[ELEVATOR] loading map...";
                    Helpers::GameLocationHelper gameLocationHelper(_logger);
                    Helpers::StateLocationHelper stateLocationHelper(_logger);

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
            _previousCursor = mouse()->cursor();
            mouse()->setCursor(Input::Mouse::Cursor::BIG_ARROW);
        }

        void ElevatorDialog::onStateDeactivate(Event::State* event) {
            mouse()->setCursor(_previousCursor);
        }
    }
}
