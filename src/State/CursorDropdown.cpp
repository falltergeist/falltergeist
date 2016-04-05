/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../State/CursorDropdown.h"

// C++ standard includes
#include "../Base/StlFeatures.h"

// Falltergeist includes
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

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        using Base::make_unique;

        CursorDropdown::CursorDropdown(std::vector<Input::Mouse::Icon>&& icons, bool onlyIcon) : State()
        {
            if (icons.size() == 0)
                throw Exception("CursorDropdown::CursorDropdown() - empty icons list!");
            _icons = icons;
            _onlyShowIcon = onlyIcon;
            if (onlyIcon && _icons.size() > 1)
            {
                _icons.resize(1);
            }
        }

        CursorDropdown::~CursorDropdown()
        {
        }

        void CursorDropdown::init()
        {
            if (_initialized) return;
            State::init();
            setFullscreen(false);
            if (!_onlyShowIcon)
            {
                setModal(true);
            }

            auto mouse = Game::getInstance()->mouse();
            _initialX = mouse->x();
            _initialY = mouse->y();

            showMenu();

            _mouseUpHandler.add([this](Event::Mouse* mouseEvent)
            {
                if (mouseEvent->leftButton())
                {
                    onLeftButtonUp(mouseEvent);
                }
            });
            auto moveHandler = [this](Event::Event* event)
            {
                if (active() && _onlyShowIcon)
                {
                    Game::getInstance()->popState();
                    event->setHandled(true);
                }
            };
            _mouseMoveHandler.add(moveHandler);
            _mouseDownHandler.add([this](Event::Mouse* event)
            {
                if (active() && !event->leftButton())
                {
                    Game::getInstance()->popState();
                }
            });
        }

        void CursorDropdown::showMenu()
        {
            int i = 0;
            for (auto icon : _icons)
            {
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
                _activeIcons.push_back(make_unique<UI::Image>("art/intrface/" + activeSurface));
                _activeIcons.back()->setY(40*i);
                _inactiveIcons.push_back(make_unique<UI::Image>("art/intrface/" + inactiveSurface));
                _inactiveIcons.back()->setY(40*i);
                i++;
            }

            auto game = Game::getInstance();

            _iconsPos = Point(_initialX + 29, _initialY);
            Point delta = Point(_initialX + 29, _initialY)
                          + Size(40, 40*_icons.size())
                          - game->renderer()->size()
                          + Point(0, game->locationState()->playerPanel()->size().height());

            int deltaX = delta.x();
            int deltaY = delta.y();
            if (deltaX > 0)
            {
                _iconsPos.setX(_iconsPos.x() - 40 - 29 - 29);
                _cursor = new UI::Image("art/intrface/actarrom.frm");
                _cursor->setOffset(-29, 0);
            }
            else
            {
                _cursor = new UI::Image("art/intrface/actarrow.frm");
                _cursor->setOffset(0, 0);
            }
            if (deltaY > 0)
            {
                _iconsPos.setY(_iconsPos.y() - deltaY);
            }
            _cursor->setPosition({_initialX, _initialY});
            addUI(_cursor);

            if (!_onlyShowIcon)
            {
                if (deltaY > 0)
                {
                    game->mouse()->setPosition({_initialX, _iconsPos.y()});
                }
                Game::getInstance()->mixer()->playACMSound("sound/sfx/iaccuxx1.acm");
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
            if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
            {
                // TODO: probably need to make invisible panel to catch all mouse events..

                if (mouseEvent->originalType() == Event::Mouse::Type::BUTTON_DOWN)
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseDownHandler);
                }
                else if (mouseEvent->originalType() == Event::Mouse::Type::BUTTON_UP)
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseUpHandler);
                }
                else if (mouseEvent->originalType() == Event::Mouse::Type::MOVE)
                {
                    emitEvent(make_unique<Event::Mouse>(*mouseEvent), _mouseMoveHandler);
                    event->setHandled(true);
                }
            }
        }

        void CursorDropdown::think()
        {
            State::think();

            auto game = Game::getInstance();

            const int mousePixelsForItem = 10;
            // select current icon
            _currentIcon = (game->mouse()->y() - _iconsPos.y())/mousePixelsForItem;

            if (_currentIcon < 0)
            {
                if (!_onlyShowIcon)
                {
                    game->mouse()->setY(_iconsPos.y());
                }
                _currentIcon = 0;
            }
            if ((unsigned int)_currentIcon >= _icons.size())
            {
                if (!_onlyShowIcon)
                {
                    game->mouse()->setY(_iconsPos.y() + _icons.size() * mousePixelsForItem);
                }
                _currentIcon = _icons.size() - 1;
            }
            if (!_onlyShowIcon)
            {
                int xDelta = game->mouse()->x() - _iconsPos.x();
                if (xDelta > 40 || xDelta < 0)
                {
                    game->mouse()->setX(_initialX);
                }
            }
        }

        void CursorDropdown::render()
        {
            if (!_deactivated)
            {
                for (unsigned int i = 0; i < _icons.size(); i++)
                {
                    if (i==(unsigned)_currentIcon)
                    {
                        _activeIcons.at(i)->setOffset(_iconsPos);
                        _activeIcons.at(i)->render();
                    }
                    else
                    {
                        _inactiveIcons.at(i)->setOffset(_iconsPos);
                        _inactiveIcons.at(i)->render();
                    }
                }
                State::render();
            }
        }

        void CursorDropdown::onStateActivate(Event::State* event)
        {
            if (_deactivated)
            {
                // TODO: why this kludge?
                Game::getInstance()->popState(); // remove when re-activated
                return;
            }

            auto mouse = Game::getInstance()->mouse();
            _initialMouseStack = mouse->states()->size();
            mouse->pushState(Input::Mouse::Cursor::NONE);
        }

        void CursorDropdown::onStateDeactivate(Event::State* event)
        {
            if (!_deactivated)
            {
                auto game = Game::getInstance();
                auto mouse = game->mouse();
                // workaround to get rid of cursor disappearing issues
                std::vector<Input::Mouse::Cursor> icons;
                while (mouse->states()->size() > _initialMouseStack)
                {
                    icons.push_back(mouse->state());
                    mouse->popState();
                }
                if (icons.size() > 0)
                {
                    icons.pop_back(); // remove empty icon from CursorDropdown state
                    // place only new icons back in stack
                    for (auto it = icons.rbegin(); it != icons.rend(); it++)
                    {
                        mouse->pushState(*it);
                    }
                }
                mouse->setPosition({_initialX, _initialY});
                _deactivated = true;
            }
        }

        void CursorDropdown::onLeftButtonUp(Event::Mouse* event)
        {
            auto game = Game::getInstance();
            game->popState();
            if (!_onlyShowIcon)
            {
                game->locationState()->handleAction(object(), _icons.at(_currentIcon));
                event->setHandled(true);
            }
        }
    }
}
