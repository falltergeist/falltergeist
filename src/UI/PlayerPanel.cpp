#include "../Audio/Mixer.h"
#include "../Event/Event.h"
#include "../Event/Keyboard.h"
#include "../Game/Defines.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Game/ItemObject.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../State/ExitConfirm.h"
#include "../State/GameMenu.h"
#include "../State/Inventory.h"
#include "../State/LoadGame.h"
#include "../State/PipBoy.h"
#include "../State/PlayerEdit.h"
#include "../State/SaveGame.h"
#include "../State/Skilldex.h"
#include "../State/WorldMap.h"
#include "../UI/Animation.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/ImageButton.h"
#include "../UI/PlayerPanel.h"
#include "../UI/ResourceManager.h"
#include "../UI/SmallCounter.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace UI
    {
        using ImageButtonType = UI::Factory::ImageButtonFactory::Type;
        using Point = Graphics::Point;

        PlayerPanel::PlayerPanel(
            std::shared_ptr<ILogger> logger
        ) : UI::Base(Point(0, 0)), _logger(logger) {
            auto game = Game::Game::getInstance();
            auto renderer = game->renderer();
            auto mouse = game->mouse();

            _resourceManager = std::make_shared<UI::ResourceManager>();
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);

            _background = std::shared_ptr<Image>(_resourceManager->getImage("art/intrface/iface.frm"));
            _ui.push_back(_background);

            setX((renderer->size().width() - 640) / 2);
            setY(renderer->size().height() - _background->size().height());

            _background->setPosition(position());

            mouseInHandler().add([=](Event::Event* event) {
                _previousCursor = mouse->cursor();
                mouse->setCursor(Input::Mouse::Cursor::BIG_ARROW);
            });

            mouseOutHandler().add([=](Event::Event* event) {
                mouse->setCursor(_previousCursor);
            });

            // Change hand button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::BIG_RED_CIRCLE, position() + Point(218, 5))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _changeHand();
            });

            // Inventory button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_INVENTORY, position() + Point(211, 40))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _openInventory();
            });

            // Options button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_OPTIONS, position() + Point(210, 61))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _openGameMenu();
            });

            // Attack button
            _isAttackBtnPressed = false;
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_ATTACK, position() + Point(267, 25))));

            _ui.back()->mouseDownHandler().add([this](Event::Event* event){
                if (auto mouse = dynamic_cast<Event::Mouse*>(event)) {
                    if (mouse->leftButton()) {
                        _isAttackBtnPressed = true;
                    }
                }
            });

            _ui.back()->mouseUpHandler().add([this](Event::Event* event){
                _isAttackBtnPressed = false;
            });


            // Hit points
            _hitPoints = std::make_shared<SmallCounter>(position() + Point(473, 40));
            _hitPoints->setType(SmallCounter::Type::SIGNED);
            _hitPoints->setNumber(game->player()->hitPoints());
            _ui.push_back(_hitPoints);

            // Armor class
            _armorClass = std::make_shared<SmallCounter>(position() + Point(473, 74));
            _armorClass->setType(SmallCounter::Type::SIGNED);
            _armorClass->setNumber(game->player()->armorClass());
            _ui.push_back(_armorClass);

            // Skilldex button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::BIG_RED_CIRCLE, position() + Point(523, 5))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _openSkilldex();
            });

            // MAP button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_MAP, position() + Point(526, 39))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _openMap();
            });

            // CHA button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_CHA, position() + Point(526, 58))));
            _ui.back()->mouseClickHandler().add([this](Event::Event* event){
                _openCharacterScreen();
            });

            // PIP button
            _ui.push_back(std::shared_ptr<ImageButton>(_imageButtonFactory->getByType(ImageButtonType::PANEL_PIP, position() + Point(526, 77))));
            _ui.back()->mouseClickHandler().add([=](Event::Event* event){
                _openPipBoy();
            });

            // Message log
            _messageLog = std::make_shared<UI::TextArea>(position() + Point(23, 24));
            _messageLog->setSize({165, 60});
            _messageLog->setWordWrap(true);
            _messageLog->setCustomLineShifts({0, 1, 2, 3, 4, 5});
            _ui.push_back(_messageLog);

            _messageLog->mouseDownHandler().add([this](Event::Mouse* event)
                {
                    _scrollingLog = 0;
                    Point relPos = event->position() - _messageLog->position();
                    if (relPos.y() < (_messageLog->size().height() / 2))
                    {
                        if (_messageLog->lineOffset() > 0)
                        {
                            _scrollingLog = -1;
                        }
                    }
                    else if (_messageLog->lineOffset() < _messageLog->numLines() - 6)
                    {
                        _scrollingLog = 1;
                    }
                    if (_scrollingLog != 0)
                    {
                        _messageLog->setLineOffset(_messageLog->lineOffset() + _scrollingLog);
                        _scrollingLogTimer = SDL_GetTicks();
                    }
                });

            _messageLog->mouseUpHandler().add([this](Event::Mouse* event)
                {
                    _scrollingLog = 0;
                    _scrollingLogTimer = 0;
                });

            _messageLog->mouseMoveHandler().add([this](Event::Mouse* event)
                {
                    auto mouse = Game::Game::getInstance()->mouse();
                    Point relPos = event->position() - _messageLog->position();

                    auto state = relPos.y() < (_messageLog->size().height() / 2)
                        ? Input::Mouse::Cursor::SMALL_UP_ARROW
                        : Input::Mouse::Cursor::SMALL_DOWN_ARROW;

                    if (mouse->state() != state)
                    {
                        mouse->setState(state);
                    }
                });

             _messageLog->mouseOutHandler().add([=](Event::Mouse* event)
                {
                    _scrollingLog = 0;
                    _scrollingLogTimer = 0;
                    mouse->setCursor(Input::Mouse::Cursor::BIG_ARROW);
                });

            keyDownHandler().add([this](Event::Event* event) {
                 this->_onKeyDown(dynamic_cast<Event::Keyboard*>(event));
            });
        }

        PlayerPanel::~PlayerPanel()
        {
        }

        const Graphics::Size& PlayerPanel::size() const
        {
            return _background->size();
        }

        void PlayerPanel::_renderHandSlot()
        {
            if (auto item = Game::Game::getInstance()->player()->currentHandSlot())
            {
                auto itemUi = item->inventoryDragUi();
                Point p = _isAttackBtnPressed ? Point(361, 58) : Point(360, 60);
                itemUi->setPosition(position() + p - itemUi->size() / 2);
                itemUi->render();
            }
        }

        void PlayerPanel::render(bool eggTransparency)
        {
            for (auto it = _ui.begin(); it != _ui.end(); ++it)
            {
                (*it)->render();
            }

            // object in hand
            _renderHandSlot();

        //    if (auto item = Game::getInstance()->player()->currentHandSlot())
        //    {
        //        auto itemUi = item->inventoryDragUi();
        //        itemUi->setPosition(position() + Point(360, 60) - itemUi->size() / 2);
        //        itemUi->render();
        //    }
        }

        void PlayerPanel::handle(Event::Event *event)
        {
            for (auto it = _ui.rbegin(); it != _ui.rend(); ++it) {
                if (event->isHandled()) {
                    return;
                }
                (*it)->handle(event);
            }

            UI::Base::handle(event);
        }

        void PlayerPanel::think(const float &deltaTime)
        {
            UI::Base::think(deltaTime);

            auto game = Game::Game::getInstance();

            for (auto it = _ui.begin(); it != _ui.end(); ++it) {
                (*it)->think(deltaTime);
            }

            // object in hand
            if (auto item = game->player()->currentHandSlot())
            {
                auto itemUi = item->inventoryDragUi();
                itemUi->think(deltaTime);
            }

            if (_scrollingLogTimer && (SDL_GetTicks() > _scrollingLogTimer + 150)
                && ((_scrollingLog < 0 && _messageLog->lineOffset() > 0)
                    || (_scrollingLog > 0 && _messageLog->lineOffset() < _messageLog->numLines() - 6)))
            {
                _messageLog->setLineOffset(_messageLog->lineOffset() + _scrollingLog);
                _scrollingLogTimer = SDL_GetTicks();
            }
        }

        void PlayerPanel::playWindowOpenSfx()
        {
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/ib1p1xx1.acm");
        }

        void PlayerPanel::_changeHand()
        {
            auto player = Game::Game::getInstance()->player();
            auto lastSlot = player->currentHandSlot();
            auto takeOut = [player](Event::Event* evt)
                {
                    if (player->currentHandSlot())
                    {
                        player->setWeaponAnimation(ANIM_TAKE_OUT);
                    }
                };
            if (lastSlot)
            {
                // put away
                auto anim = player->setWeaponAnimation(ANIM_PUT_AWAY);
                Event::Handler origHandler = anim->animationEndedHandler();
                anim->animationEndedHandler().clear();
                anim->animationEndedHandler().add(takeOut);
                anim->animationEndedHandler().add(origHandler);
            }
            player->setCurrentHand(player->currentHand() == HAND::RIGHT ? HAND::LEFT : HAND::RIGHT);
            if (!lastSlot)
            {
                takeOut(nullptr);
            }
            playWindowOpenSfx();

        }

        void PlayerPanel::_openGameMenu()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::GameMenu(_resourceManager, game->mouse(), _logger));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openInventory()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::Inventory(_resourceManager, game->mouse(), _logger));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openSkilldex()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::Skilldex(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openMap()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::WorldMap(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openCharacterScreen()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::PlayerEdit(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openPipBoy()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::PipBoy(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::_onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_a:
                    // @TODO: initiateCombat();
                    break;
                case SDLK_c:
                    _openCharacterScreen();
                    break;
                case SDLK_i:
                    _openInventory();
                    break;
                case SDLK_p:
                    if (event->controlPressed())
                    {
                        // @TODO: pause game
                    }
                    else
                    {
                        _openPipBoy();
                    }
                    break;
                case SDLK_z:
                    _openPipBoy(); // @TODO: go to clock
                    break;
                case SDLK_ESCAPE:
                case SDLK_o:
                    _openGameMenu();
                    break;
                case SDLK_b:
                    _changeHand();
                    break;
                // M button is handled in State::Location
                case SDLK_n:
                    // @TODO: toggleItemMode();
                    break;
                case SDLK_s:
                    if (event->controlPressed())
                    {
                        _openSaveGame();
                    }
                    else
                    {
                        _openSkilldex();
                    }
                    break;
                case SDLK_l:
                    if (event->controlPressed())
                    {
                        _openLoadGame();
                    }
                    break;
                case SDLK_x: {
                    if (event->controlPressed()) {
                        auto game = Game::Game::getInstance();
                        game->pushState(new State::ExitConfirm(_resourceManager, game->mouse(), _logger));
                        playWindowOpenSfx();
                    }
                    break;
                }
                case SDLK_SLASH:
                    // @TODO: printCurrentTime();
                    break;
                case SDLK_TAB:
                    _openMap();
                    break;
                case SDLK_F1:
                    // @TODO: help screen
                    break;
                case SDLK_F2:
                    // @TODO: volume down
                    break;
                case SDLK_F3:
                    // @TODO: volume up
                    break;
                case SDLK_F4:
                    if (!event->altPressed())
                    {
                        _openSaveGame();
                    }
                    break;
                case SDLK_F5:
                    _openLoadGame();
                    break;
                case SDLK_F6:
                    // @TODO: quick save logic
                    break;
                case SDLK_F7:
                    // @TODO: quick load logic
                    break;
                case SDLK_F10: {
                    auto game = Game::Game::getInstance();
                    game->pushState(new State::ExitConfirm(_resourceManager, game->mouse(), _logger));
                    playWindowOpenSfx();
                    break;
                }
                case SDLK_F12:
                    // @TODO: save screenshot
                    break;
            }
        }

        void PlayerPanel::_openSaveGame()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::SaveGame(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::_openLoadGame()
        {
            auto game = Game::Game::getInstance();
            game->pushState(new State::LoadGame(_resourceManager, game->mouse()));
            playWindowOpenSfx();
        }

        void PlayerPanel::displayMessage(const std::string& message)
        {
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/monitor.acm");
            std::string msg = "\n\x95";
            msg += message;
            *_messageLog << msg;
            _messageLog->setLineOffset(_messageLog->numLines() - 6);
        }

        bool PlayerPanel::opaque(const Graphics::Point &pos)
        {
            return _background->opaque(pos);
        }
    }
}
