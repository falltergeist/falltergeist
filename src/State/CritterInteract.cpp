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
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../Game/CritterObject.h"
#include "../State/CritterInteract.h"
#include "../State/CursorDropdown.h"
#include "../State/Location.h"
#include "../UI/Image.h"
#include "../Input/Mouse.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

CritterInteract::CritterInteract() : State()
{
}

CritterInteract::~CritterInteract()
{
    auto camera = Game::getInstance()->locationState()->camera();
    camera->setXPosition(_oldCameraX);
    camera->setYPosition(_oldCameraY);
}

void CritterInteract::onStateActivate(Event::State* event)
{
    Game::getInstance()->mouse()->pushState(Mouse::Cursor::BIG_ARROW);
}

void CritterInteract::onStateDeactivate(Event::State* event)
{
    Game::getInstance()->mouse()->popState();
}

void CritterInteract::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(true);

    setX((Game::getInstance()->renderer()->width() - 640)*0.5);
    setY((Game::getInstance()->renderer()->height() - 480)*0.5);

    addUI("background", new Image("art/intrface/alltlk.frm"));

    // Centering camera on critter position
    auto locationState = Game::getInstance()->locationState();
    _oldCameraX = locationState->camera()->xPosition();
    _oldCameraY = locationState->camera()->yPosition();

    locationState->camera()->setXPosition(critter()->hexagon()->x());
    locationState->camera()->setYPosition(critter()->hexagon()->y() + 100);
}

int CritterInteract::backgroundID()
{
    return _backgroundID;
}

void CritterInteract::setBackgroundID(int backgroundID)
{
    _backgroundID = backgroundID;
}

int CritterInteract::headID()
{
    return _headID;
}

void CritterInteract::setHeadID(int headID)
{
    _headID = headID;
}

int CritterInteract::mood()
{
    return _mood;
}

void CritterInteract::setMood(int mood)
{
    _mood = mood;
}

Game::CritterObject* CritterInteract::critter()
{
    return _critter;
}

void CritterInteract::setCritter(Game::CritterObject* critter)
{
    _critter = critter;
}

int CritterInteract::msgFileID()
{
    return _msgFileID;
}

void CritterInteract::setMsgFileID(int value)
{
    _msgFileID = value;
}

VM* CritterInteract::script()
{
    return _script;
}

void CritterInteract::setScript(VM* script)
{
    _script = script;
}

}
}
