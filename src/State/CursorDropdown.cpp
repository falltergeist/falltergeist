/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// C++ standard includes

// Falltergeist includes
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../State/CursorDropdown.h"
#include "../State/Location.h"
#include "../UI/HiddenMask.h"
#include "Audio/AudioMixer.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

CursorDropdown::CursorDropdown(std::vector<int> icons, bool onlyIcon) : State()
{
    _icons = icons;
    _onlyShowIcon = onlyIcon;
}

CursorDropdown::~CursorDropdown()
{
    while (!_activeIcons.empty())
    {
        delete _activeIcons.back();
        delete _inactiveIcons.back();
        _activeIcons.pop_back();
        _inactiveIcons.pop_back();
    }
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
    showMenu();
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
                throw Exception("CursorDropdown::init() - unknown icon type");

        }
        _activeIcons.push_back(new Image("art/intrface/" + activeSurface));
        _activeIcons.back()->setY(40*i);
        _inactiveIcons.push_back(new Image("art/intrface/" + inactiveSurface));
        _inactiveIcons.back()->setY(40*i);
        if (_onlyShowIcon)
        {
            break;
        }
        i++;
    }

    auto game = Game::getInstance();

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
        _cursor = new Image("art/intrface/actarrom.frm");
        _cursor->setXOffset(-29);
        _cursor->setYOffset(0);
    }
    else
    {
        _cursor = new Image("art/intrface/actarrow.frm");
        _cursor->setXOffset(0);
        _cursor->setYOffset(0);
    }
    _mask = new HiddenMask(game->renderer()->width(), game->renderer()->height());
    _cursor->setX(_initialX);
    _cursor->setY(_initialY);
    addUI(_cursor);
    _mask->addEventHandler("mouseleftup", [this](Event* event){ this->onLeftButtonUp(dynamic_cast<MouseEvent*>(event)); });
    if (_onlyShowIcon)
    {
        _mask->addEventHandler("mousemove", [this](Event* event) {
            auto game = Game::getInstance();
            game->mouse()->popState();
            game->popState();
        });
    }
    else
    {
        Game::getInstance()->mixer()->playACMSound("sound/sfx/iaccuxx1.acm");
    }
    _mask->setVisible(true);
    addUI(_mask);
    addUI(_surface);
}

Game::GameObject* CursorDropdown::object()
{
    return _object;
}

void CursorDropdown::setObject(Game::GameObject* object)
{
    _object = object;
}

void CursorDropdown::think()
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
        game->mouse()->setY(_surface->y());
        _currentSurface = 0;
    }
    if ((unsigned int)_currentSurface >= _icons.size())
    {
        game->mouse()->setY(_surface->y() + _surface->height());
        _currentSurface = _icons.size() - 1;
    }

    int xDelta = game->mouse()->x() - _surface->x();
    if ( xDelta > 40 || xDelta < 0)
    {
        game->mouse()->setX(_initialX);
    }
    if (!_onlyShowIcon)
    {
        auto activeIcon = _activeIcons.at(_currentSurface);
        activeIcon->texture()->copyTo(_surface->texture(), activeIcon->x(), activeIcon->y());
    }
}

void CursorDropdown::onStateActivate(StateEvent* event)
{
    auto mouse = Game::getInstance()->mouse();
    _initialX = mouse->x();
    _initialY = mouse->y();
    mouse->pushState(Mouse::NONE);
}

void CursorDropdown::onStateDeactivate(StateEvent* event)
{
    auto game = Game::getInstance();
    game->mouse()->setX(_initialX);
    game->mouse()->setY(_initialY);
    game->mouse()->popState();
}

void CursorDropdown::onLeftButtonUp(MouseEvent* event)
{
    auto game = Game::getInstance();
    game->popState();
    if (!_onlyShowIcon)
    {
        game->locationState()->handleAction(object(), _icons.at(_currentSurface));
    }
}

}
}
