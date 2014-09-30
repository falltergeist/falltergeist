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
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/PathFinding/Hexagon.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameCritterObject.h"
#include "../States/CritterInteractState.h"
#include "../States/LocationState.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

CritterInteractState::CritterInteractState() : State()
{
}

CritterInteractState::~CritterInteractState()
{
    auto camera = Game::getInstance()->locationState()->camera();
    camera->setXPosition(_oldCameraX);
    camera->setYPosition(_oldCameraY);
}

void CritterInteractState::init()
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
    locationState->checkObjectsToRender();
    //locationState->generateUi();
}

int CritterInteractState::backgroundID()
{
    return _backgroundID;
}

void CritterInteractState::setBackgroundID(int backgroundID)
{
    _backgroundID = backgroundID;
}

int CritterInteractState::headID()
{
    return _headID;
}

void CritterInteractState::setHeadID(int headID)
{
    _headID = headID;
}

int CritterInteractState::mood()
{
    return _mood;
}

void CritterInteractState::setMood(int mood)
{
    _mood = mood;
}

GameCritterObject* CritterInteractState::critter()
{
    return _critter;
}

void CritterInteractState::setCritter(GameCritterObject* critter)
{
    _critter = critter;
}

int CritterInteractState::msgFileID()
{
    return _msgFileID;
}

void CritterInteractState::setMsgFileID(int value)
{
    _msgFileID = value;
}

VM* CritterInteractState::script()
{
    return _script;
}

void CritterInteractState::setScript(VM* script)
{
    _script = script;
}

}
