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
#include <iostream>

// Falltergeist includes

#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameCritterObject.h"
#include "../States/CritterDialogState.h"
#include "../States/CritterTalkState.h"
#include "../States/LocationState.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

CritterDialogState::CritterDialogState() : State()
{
    auto backgroundX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - 480)*0.5;
    _question = std::shared_ptr<TextArea>(new TextArea("", backgroundX+140, backgroundY+235));
    _question->setWidth(370);
    _question->setWordWrap(true);

    _talk = std::shared_ptr<CritterTalkState>(new CritterTalkState());
}

CritterDialogState::~CritterDialogState()
{
}

void CritterDialogState::init()
{
    if (_initialized) return;
    State::init();
    setFullscreen(false);
    setModal(true);

    auto locationState = Game::getInstance()->locationState();
    _oldCameraX = locationState->camera()->xPosition();
    _oldCameraY = locationState->camera()->yPosition();

    locationState->camera()->setXPosition(Location::hexagonToX(critter()->position()));
    locationState->camera()->setYPosition(Location::hexagonToY(critter()->position()) + 100);
    locationState->checkObjectsToRender();
    locationState->generateUi();

    auto background = std::shared_ptr<Image>(new Image("art/intrface/alltlk.frm"));

    auto backgroundX = static_cast<int>((Game::getInstance()->renderer()->width() - background->width())*0.5);
    auto backgroundY = static_cast<int>((Game::getInstance()->renderer()->height() - background->height())*0.5);
    background->setX(backgroundX);
    background->setY(backgroundY);

    add(background);
    add(_question);

    _talk->setOffsetX(backgroundX);
    _talk->setOffsetY(backgroundY + 291);

    Game::getInstance()->pushState(_talk);
}

void CritterDialogState::think()
{
}

void CritterDialogState::close()
{
    // Pop CritterTalkState
    Game::getInstance()->popState();
    // Restore original camera position
    auto camera = Game::getInstance()->locationState()->camera();
    camera->setXPosition(_oldCameraX);
    camera->setYPosition(_oldCameraY);
}

void CritterDialogState::setCritter(std::shared_ptr<GameCritterObject> critter)
{
    _critter = critter;
}

std::shared_ptr<GameCritterObject> CritterDialogState::critter()
{
    return _critter;
}

VM* CritterDialogState::script()
{
    return _script;
}

void CritterDialogState::setScript(VM* value)
{
    _script = value;
}

void CritterDialogState::setQuestion(std::string value)
{
    _question->setText(value);
}

std::shared_ptr<CritterTalkState> CritterDialogState::talk()
{
    return _talk;
}

}
