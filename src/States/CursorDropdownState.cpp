/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <iostream>

// Falltergeist includes
#include "../States/CursorDropdownState.h"
#include "../Engine/Game.h"
#include "../Engine/Location.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/Surface.h"
#include "../UI/HiddenMask.h"

// Third party includes

namespace Falltergeist
{

CursorDropdownState::CursorDropdownState(std::vector<int> icons) : State()
{
    _icons = icons;
    //_initialX = _game->mouse()->cursorX();
    //_initialY = _game->mouse()->cursorY();
    //_initialType = _game->mouse()->type();
}

CursorDropdownState::~CursorDropdownState()
{
}

void CursorDropdownState::init()
{
    if (_initialized) return;
    State::init();
    setFullscreen(false);
    /*
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
        _activeSurfaces.push_back(new Surface(ResourceManager::surface("art/intrface/" + activeSurface, 0, 40*i)));
        _inactiveSurfaces.push_back(new Surface(ResourceManager::surface("art/intrface/" + inactiveSurface, 0, 40*i)));
        i++;
    }

    _game->mouse()->setType(Mouse::NONE);

    _cursor = new Surface(ResourceManager::surface("art/intrface/actarrow.frm"));
    _cursor->setXOffset(0);
    _cursor->setYOffset(0);
    _cursor->setX(_initialX);
    _cursor->setY(_initialY);

    _surface = new Surface(40, 40*_icons.size(), _initialX + 29, _initialY);

    int deltaY = _surface->y() + _surface->height() - 480;
    int deltaX = _surface->x() + _surface->width() - 640;

    if (deltaY > 0)
    {
        _surface->setY(_surface->y() - deltaY);
        SDL_WarpMouse(_initialX, _surface->y());
    }

    if (deltaX > 0)
    {
        _surface->setX(_surface->x() - 40 - 29 - 29);
        delete _cursor;
        _cursor = new Surface(ResourceManager::surface("art/intrface/actarrom.frm"));
        _cursor->setXOffset(-29);
        _cursor->setYOffset(0);
        _cursor->setX(_initialX);
        _cursor->setY(_initialY);
    }


    _mask = new HiddenMask(640, 480);
    _mask->addEventHandler("mouseleftup", this, (EventRecieverMethod) &CursorDropdownState::onLeftButtonUp);
    _mask->setVisible(true);
    add(_cursor);
    add(_surface);
    add(_mask);
    */
}

void CursorDropdownState::blit()
{
    for (auto surface : _inactiveSurfaces)
    {
        surface->copyTo(_surface);
    }
    _activeSurfaces.at(_currentSurface)->copyTo(_surface);
    State::blit();
}

void CursorDropdownState::setObject(void* object)
{
    _object = object;
}

void CursorDropdownState::think()
{
    /*
    int currentSurface = (_game->mouse()->cursorY() - _surface->y())/40;
    if (currentSurface < 0)
    {
        SDL_WarpMouse(_initialX, _surface->y());
        currentSurface = 0;
    }
    if (currentSurface >= _icons.size())
    {
        SDL_WarpMouse(_initialX, _surface->y() + _surface->height());
        currentSurface = _icons.size() - 1;
    }
    _currentSurface = currentSurface;
    */
}

void CursorDropdownState::onLeftButtonUp(MouseEvent* event)
{
    /*
    SDL_WarpMouse(_initialX, _initialY);
    _game->mouse()->setType(_initialType);
    _game->popState();
    _game->location()->handleAction((GameObject*)_object, _icons.at(_currentSurface));
    */

}



}
