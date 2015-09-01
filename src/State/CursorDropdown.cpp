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

// Related headers
#include "../State/CursorDropdown.h"

// C++ standard includes

// Falltergeist includes
#include "../Audio/Mixer.h"
#include "../Exception.h"
#include "../Game/CritterObject.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../State/Location.h"
#include "../UI/HiddenMask.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

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
    auto mouse = Game::getInstance()->mouse();
    _initialMouseStack = mouse->states()->size();
    mouse->pushState(Input::Mouse::Cursor::NONE);
    _initialX = mouse->x();
    _initialY = mouse->y();
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
        _activeIcons.push_back(new UI::Image("art/intrface/" + activeSurface));
        _activeIcons.back()->setY(40*i);
        _inactiveIcons.push_back(new UI::Image("art/intrface/" + inactiveSurface));
        _inactiveIcons.back()->setY(40*i);
        i++;
    }

    auto game = Game::getInstance();
    _surface = new UI::Image(40, 40*_icons.size());
    _surface->setX(_initialX + 29);
    _surface->setY(_initialY);
    int deltaX = _surface->x() + _surface->width() - game->renderer()->width();
    int deltaY = _surface->y() + _surface->height() - game->renderer()->height() + game->locationState()->playerPanelState()->height();
    if (deltaX > 0)
    {
        _surface->setX(_surface->x() - 40 - 29 - 29);
        _cursor = new UI::Image("art/intrface/actarrom.frm");
        _cursor->setXOffset(-29);
        _cursor->setYOffset(0);
    }
    else
    {
        _cursor = new UI::Image("art/intrface/actarrow.frm");
        _cursor->setXOffset(0);
        _cursor->setYOffset(0);
    }
    if (deltaY > 0)
    {
        _surface->setY(_surface->y() - deltaY);
    }
    _cursor->setX(_initialX);
    _cursor->setY(_initialY);
    addUI(_cursor);
    addUI(_surface);
    // draw icons on the surface for the first time
    for (auto ui : _inactiveIcons)
    {
        ui->texture()->copyTo(_surface->texture(), ui->x(), ui->y());
    }
    if (!_onlyShowIcon)
    {
        if (deltaY > 0)
        {
            game->mouse()->setX(_initialX);
            game->mouse()->setY(_surface->y());
        }
        Game::getInstance()->mixer()->playACMSound("sound/sfx/iaccuxx1.acm");
        _activeIcons.at(0)->texture()->copyTo(_surface->texture(), 0,  0); // highlight first item
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
        if (mouseEvent->name() == "mouseup" && mouseEvent->leftButton())
        {
            onLeftButtonUp(mouseEvent);
        }
        else if (mouseEvent->name() == "mousemove" && _onlyShowIcon)
        {
            Game::getInstance()->popState();
            event->setHandled(true);
        }
        else if (mouseEvent->name() == "mousedown" && !mouseEvent->leftButton())
        {
            Game::getInstance()->popState();
        }
    }
}

void CursorDropdown::think()
{
    State::think();

    auto game = Game::getInstance();
    
    const int mousePixelsForItem = 10;
    // select current icon
    _previousIcon = _currentIcon;
    _currentIcon = (game->mouse()->y() - _surface->y())/mousePixelsForItem;
    if (_currentIcon < 0)
    {
        if (!_onlyShowIcon)
            game->mouse()->setY(_surface->y());
        _currentIcon = 0;
    }
    if ((unsigned int)_currentIcon >= _icons.size())
    {
        if (!_onlyShowIcon)
            game->mouse()->setY(_surface->y() + _icons.size()*mousePixelsForItem);
        _currentIcon = _icons.size() - 1;
    }
    if (!_onlyShowIcon)
    {
        int xDelta = game->mouse()->x() - _surface->x();
        if ( xDelta > 40 || xDelta < 0)
        {
            game->mouse()->setX(_initialX);
        }
    }
}

void CursorDropdown::render()
{
    if (!_deactivated)
    {
        if (_currentIcon != _previousIcon) 
        {
            auto inactiveIcon = _inactiveIcons.at(_previousIcon);
            inactiveIcon->texture()->copyTo(_surface->texture(), inactiveIcon->x(), inactiveIcon->y());
            auto activeIcon = _activeIcons.at(_currentIcon);
            activeIcon->texture()->copyTo(_surface->texture(), activeIcon->x(), activeIcon->y());
        }
        State::render();
    }
}

void CursorDropdown::onStateActivate(Event::State* event)
{
    if (_deactivated)
    {
        Game::getInstance()->popState(); // remove when re-activated
    }
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
        mouse->setX(_initialX);
        mouse->setY(_initialY);
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
