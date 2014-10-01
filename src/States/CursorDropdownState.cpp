/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Graphics/Texture.h"
#include "../Engine/Input/Mouse.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDudeObject.h"
#include "../States/CursorDropdownState.h"
#include "../States/LocationState.h"
#include "../UI/HiddenMask.h"

// Third party includes

namespace Falltergeist
{

CursorDropdownState::CursorDropdownState(std::vector<int> icons) : State()
{
    _icons = icons;
    auto mouse = Game::getInstance()->mouse();
    _initialX = mouse->x();
    _initialY = mouse->y();
    mouse->pushState(Mouse::NONE);
}

CursorDropdownState::~CursorDropdownState()
{
    while (!_activeIcons.empty())
    {
        delete _activeIcons.back();
        delete _inactiveIcons.back();
        _activeIcons.pop_back();
        _inactiveIcons.pop_back();
    }
}

void CursorDropdownState::init()
{
    if (_initialized) return;
    State::init();
    setFullscreen(false);
    setModal(true);


    int i = 0;
    for (auto icon : _icons)
    {
        std::string activeSurface;
        std::string inactiveSurface;
        switch (icon)
        {
            case Mouse::ICON_INVENTORY:
                activeSurface = "invenh.frm";
                inactiveSurface = "invenn.frm";
                break;
            case Mouse::ICON_CANCEL:
                activeSurface = "cancelh.frm";
                inactiveSurface = "canceln.frm";
                break;
            case Mouse::ICON_ROTATE:
                activeSurface = "rotateh.frm";
                inactiveSurface = "rotaten.frm";
                break;
            case Mouse::ICON_SKILL:
                activeSurface = "skillh.frm";
                inactiveSurface = "skilln.frm";
                break;
            case Mouse::ICON_LOOK:
                activeSurface = "lookh.frm";
                inactiveSurface = "lookn.frm";
                break;
            case Mouse::ICON_TALK:
                activeSurface = "talkh.frm";
                inactiveSurface = "talkn.frm";
                break;
            case Mouse::ICON_PUSH:
                activeSurface = "pushh.frm";
                inactiveSurface = "pushn.frm";
                break;
            case Mouse::ICON_UNLOAD:
                activeSurface = "unloadh.frm";
                inactiveSurface = "unloadn.frm";
                break;
            case Mouse::ICON_USE:
                activeSurface = "usegeth.frm";
                inactiveSurface = "usegetn.frm";
                break;
            default:
                throw Exception("CursorDropdownState::init() - unknown icon type");

        }
        _activeIcons.push_back(new Image("art/intrface/" + activeSurface));
        _activeIcons.back()->setY(40*i);
        _inactiveIcons.push_back(new Image("art/intrface/" + inactiveSurface));
        _inactiveIcons.back()->setY(40*i);
        i++;
    }

    auto game = Game::getInstance();


    _cursor = new Image("art/intrface/actarrow.frm");
    _cursor->setXOffset(0);
    _cursor->setYOffset(0);
    _cursor->setX(_initialX);
    _cursor->setY(_initialY);

    _surface = new Image(40, 40*_icons.size());
    _surface->setX(_initialX + 29);
    _surface->setY(_initialY);

    int deltaX = _surface->x() + _surface->width() - game->renderer()->width();
    int deltaY = _surface->y() + _surface->height() - game->renderer()->height();

    if (deltaY > 0)
    {
        _surface->setY(_surface->y() - deltaY);
        game->mouse()->setX(_initialX);
        game->mouse()->setY(_surface->y());
    }

    if (deltaX > 0)
    {
        _surface->setX(_surface->x() - 40 - 29 - 29);
        delete _cursor;
        _cursor = new Image("art/intrface/actarrom.frm");
        _cursor->setXOffset(-29);
        _cursor->setYOffset(0);
        _cursor->setX(_initialX);
        _cursor->setY(_initialY);
    }

    _mask = new HiddenMask(game->renderer()->width(), game->renderer()->height());
    _mask->addEventHandler("mouseleftup", this, (EventRecieverMethod) &CursorDropdownState::onLeftButtonUp);
    _mask->setVisible(true);
    addUI(_cursor);
    addUI(_surface);
    addUI(_mask);

}

void CursorDropdownState::setObject(GameObject* object)
{
    _object = object;
}

void CursorDropdownState::think()
{
    State::think();

    auto game = Game::getInstance();


    for (auto ui : _inactiveIcons)
    {
        ui->texture()->copyTo(_surface->texture(), ui->x(), ui->y());
    }

    _currentSurface= (game->mouse()->y() - _surface->y())/40;
    if (_currentSurface < 0)
    {
        //game->mouse()->setX(_initialX);
        game->mouse()->setY(_surface->y());
        _currentSurface = 0;
    }
    if ((unsigned int)_currentSurface >= _icons.size())
    {
        //game->mouse()->setX(_initialX);
        game->mouse()->setY(_surface->y() + _surface->height());
        _currentSurface = _icons.size() - 1;
    }

    int xDelta = game->mouse()->x() - _surface->x();
    if ( xDelta > 40 || xDelta < 0)
    {
        game->mouse()->setX(_initialX);
    }

    auto activeIcon = _activeIcons.at(_currentSurface);

    activeIcon->texture()->copyTo(_surface->texture(), activeIcon->x(), activeIcon->y());

}

void CursorDropdownState::onLeftButtonUp(std::shared_ptr<MouseEvent> event)
{
    auto state = dynamic_cast<CursorDropdownState*>(event->reciever());
    auto game = Game::getInstance();
    game->mouse()->setX(state->_initialX);
    game->mouse()->setY(state->_initialY);
    game->mouse()->popState();
    game->popState();
    game->locationState()->handleAction(state->_object, state->_icons.at(state->_currentSurface));
}



}
