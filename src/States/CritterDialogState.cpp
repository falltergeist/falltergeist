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
#include "../States/CritterDialogState.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Game.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameCritterObject.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

CritterDialogState::CritterDialogState() : State()
{
}

CritterDialogState::~CritterDialogState()
{
}

void CritterDialogState::init()
{
    if (_initialized) return;
    State::init();
    setFullscreen(false);

    auto camera = Game::getInstance().location()->camera();
    _oldCameraX = camera->xPosition();
    _oldCameraY = camera->xPosition();
    camera->setXPosition(Location::hexagonToX(critter()->position()));
    camera->setYPosition(Location::hexagonToY(critter()->position()) + 100);

    auto background = new Surface(ResourceManager::surface("art/intrface/alltlk.frm"));
    auto background2 = new Surface(ResourceManager::surface("art/intrface/di_talk.frm"));
    background2->setY(291);

    add(background);
    add(background2);

    std::cout << *_question << std::endl;
    for (auto answer : _answers)
    {
        std::cout << *answer << std::endl;
    }
}

void CritterDialogState::setCritter(GameCritterObject* critter)
{
    _critter = critter;
}

GameCritterObject* CritterDialogState::critter()
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

std::string* CritterDialogState::question()
{
    return _question;
}

void CritterDialogState::setQuestion(std::string* value)
{
    _question = value;
}

std::vector<int>* CritterDialogState::functions()
{
    return &_functions;
}

std::vector<int>* CritterDialogState::reactions()
{
    return &_reactions;
}

std::vector<std::string*>* CritterDialogState::answers()
{
    return &_answers;
}


}
