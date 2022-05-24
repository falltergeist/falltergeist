#include <memory>
#include "../State/CursorDropdown.h"
#include "../Audio/Mixer.h"
#include "../Exception.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../State/Location.h"
#include "../UI/HiddenMask.h"
#include "../UI/PlayerPanel.h"

namespace Falltergeist::State {
    using Point = Graphics::Point;
    using Size = Graphics::Size;

    CursorDropdown::CursorDropdown(
        std::shared_ptr<UI::IResourceManager> resourceManager,
        std::shared_ptr<Input::Mouse> mouse,
        std::vector<Input::Mouse::Icon>&& icons,
        bool onlyIcon
    ) : State(mouse), _resourceManager(resourceManager)
    {
        if (icons.size() == 0) {
            throw Exception("CursorDropdown::CursorDropdown() - empty icons list!");
        }
        _icons = icons;
        _onlyShowIcon = onlyIcon;
        if (onlyIcon && _icons.size() > 1) {
            _icons.resize(1);
        }
    }

    void CursorDropdown::init()
    {
        if (_initialized) {
            return;
        }
        State::init();
        setFullscreen(false);
        if (!_onlyShowIcon) {
            setModal(true);
        }

        auto mouse = Game::Game::getInstance()->mouse();
        _initialMousePosition = mouse->position();

        _showMenu();

        _mouseUpHandler.add([this](Event::Mouse* mouseEvent) {
            if (mouseEvent->leftButton()) {
                onLeftButtonUp(mouseEvent);
            }
        });
        auto moveHandler = [this](Event::Event* event) {
            if (active() && _onlyShowIcon) {
                Game::Game::getInstance()->popState();
                event->stopPropagation();
            }
        };
        _mouseMoveHandler.add(moveHandler);
        _mouseDownHandler.add([this](Event::Mouse* event) {
            if (active() && !event->leftButton()) {
                Game::Game::getInstance()->popState();
            }
        });
    }

    void CursorDropdown::_showMenu()
    {
        int i = 0;
        for (auto icon : _icons) {
            std::string activeSurface;
            std::string inactiveSurface;
            switch (icon)
            {
                case Input::Mouse::Icon::INVENTORY:
                    activeSurface = "invenh.frm";
                    inactiveSurface = "invenn.frm";
                    break;
                case Input::Mouse::Icon::CANCEL:
                    activeSurface = "cancelh.frm";
                    inactiveSurface = "canceln.frm";
                    break;
                case Input::Mouse::Icon::ROTATE:
                    activeSurface = "rotateh.frm";
                    inactiveSurface = "rotaten.frm";
                    break;
                case Input::Mouse::Icon::SKILL:
                    activeSurface = "skillh.frm";
                    inactiveSurface = "skilln.frm";
                    break;
                case Input::Mouse::Icon::LOOK:
                    activeSurface = "lookh.frm";
                    inactiveSurface = "lookn.frm";
                    break;
                case Input::Mouse::Icon::TALK:
                    activeSurface = "talkh.frm";
                    inactiveSurface = "talkn.frm";
                    break;
                case Input::Mouse::Icon::PUSH:
                    activeSurface = "pushh.frm";
                    inactiveSurface = "pushn.frm";
                    break;
                case Input::Mouse::Icon::UNLOAD:
                    activeSurface = "unloadh.frm";
                    inactiveSurface = "unloadn.frm";
                    break;
                case Input::Mouse::Icon::USE:
                    activeSurface = "usegeth.frm";
                    inactiveSurface = "usegetn.frm";
                    break;
                default:
                    throw Exception("CursorDropdown::init() - unknown icon type");

            }
            _activeIcons.push_back(std::unique_ptr<UI::Image>(_resourceManager->getImage("art/intrface/" + activeSurface)));
            _activeIcons.back()->setY(40*i);
            _inactiveIcons.push_back(std::unique_ptr<UI::Image>(_resourceManager->getImage("art/intrface/" + inactiveSurface)));
            _inactiveIcons.back()->setY(40*i);
            i++;
        }

        auto game = Game::Game::getInstance();

        _iconsPos = _initialMousePosition + Point(29, 0);
        Point delta = _iconsPos
                      + Size(40, 40 * static_cast<int>(_icons.size()))
                      - game->renderer()->size()
                      + Point(0, game->locationState()->playerPanel()->size().height());

        int deltaX = delta.x();
        int deltaY = delta.y();
        if (deltaX > 0) {
            _iconsPos.setX(_iconsPos.x() - 40 - 29 - 29);
            _cursor = _resourceManager->getImage("art/intrface/actarrom.frm");
            _cursor->setOffset(Point(-29, 0));
        } else {
            _cursor = _resourceManager->getImage("art/intrface/actarrow.frm");
            _cursor->setOffset(Point(0, 0));
        }
        if (deltaY > 0) {
            _iconsPos.setY(_iconsPos.y() - deltaY);
        }
        _cursor->setPosition(_initialMousePosition);
        addUI(_cursor);

        if (!_onlyShowIcon) {
            if (deltaY > 0) {
                game->mouse()->setPosition({_initialMousePosition.x(), _iconsPos.y()});
            }
            Game::Game::getInstance()->mixer()->playACMSound("sound/sfx/iaccuxx1.acm");
        }
    }

    Game::Object* CursorDropdown::object()
    {
        return _object;
    }

    void CursorDropdown::setObject(Game::Object* object)
    {
        _object = object;
    }

    void CursorDropdown::handle(Event::Event* event)
    {
        if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event)) {
            // TODO: probably need to make invisible panel to catch all mouse events..

            if (mouseEvent->originalType() == Event::Mouse::Type::BUTTON_DOWN) {
                emitEvent(std::make_unique<Event::Mouse>(*mouseEvent), _mouseDownHandler);
            } else if (mouseEvent->originalType() == Event::Mouse::Type::BUTTON_UP) {
                emitEvent(std::make_unique<Event::Mouse>(*mouseEvent), _mouseUpHandler);
            } else if (mouseEvent->originalType() == Event::Mouse::Type::MOVE) {
                emitEvent(std::make_unique<Event::Mouse>(*mouseEvent), _mouseMoveHandler);
                event->stopPropagation();
            }
        }
    }

    void CursorDropdown::think(const float &deltaTime)
    {
        State::think(deltaTime);

        auto game = Game::Game::getInstance();

        const int mousePixelsForItem = 10;

        auto mouse = game->mouse();

        // select current icon
        _currentIcon = (mouse->position().y() - _iconsPos.y()) / mousePixelsForItem;

        if (_currentIcon < 0) {
            if (!_onlyShowIcon) {
                mouse->setPosition(Point(mouse->position().x(), _iconsPos.y()));
            }
            _currentIcon = 0;
        }
        if ((unsigned int)_currentIcon >= _icons.size()) {
            if (!_onlyShowIcon) {
                mouse->setPosition(Point(mouse->position().x(), _iconsPos.y() + static_cast<int>(_icons.size()) * mousePixelsForItem));
            }
            _currentIcon = static_cast<int>(_icons.size()) - 1;
        }
        if (!_onlyShowIcon) {
            int xDelta = mouse->position().x() - _iconsPos.x();
            if (xDelta > 40 || xDelta < 0) {
                mouse->setPosition(Point(_initialMousePosition.x(), mouse->position().y()));
            }
        }
    }

    void CursorDropdown::render()
    {
        if (!_deactivated) {
            for (unsigned int i = 0; i < _icons.size(); i++) {
                if (i==(unsigned)_currentIcon) {
                    _activeIcons.at(i)->setOffset(_iconsPos);
                    _activeIcons.at(i)->render();
                } else {
                    _inactiveIcons.at(i)->setOffset(_iconsPos);
                    _inactiveIcons.at(i)->render();
                }
            }
            State::render();
        }
    }

    void CursorDropdown::onStateActivate(Event::State* event)
    {
        if (_deactivated) {
            // TODO: why this kludge?
            Game::Game::getInstance()->popState(); // remove when re-activated
            return;
        }

        _previousCursor = mouse()->cursor();
        mouse()->setCursor(Input::Mouse::Cursor::NONE);
    }

    void CursorDropdown::onStateDeactivate(Event::State* event)
    {
        if (!_deactivated) {
            mouse()->setCursor(_previousCursor);
            mouse()->setPosition(_initialMousePosition);
            _deactivated = true;
        }
    }

    void CursorDropdown::onLeftButtonUp(Event::Mouse* event)
    {
        auto game = Game::Game::getInstance();
        game->popState();
        if (!_onlyShowIcon) {
            game->locationState()->handleAction(object(), _icons.at(_currentIcon));
            event->stopPropagation();
        }
    }
}
