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
#include "../States/CritterDialogState.h"
#include "../States/LocationState.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../Engine/Screen.h"
#include "../Engine/Game.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Game/GameCritterObject.h"
#include "../VM/VM.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{

CritterDialogState::CritterDialogState() : State()
{
    _question = std::shared_ptr<TextArea>(new TextArea("", 140, 235));
    _question->setWidth(370);
    _question->setWordWrap(true);
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
    _oldCameraX = locationState->location()->camera()->xPosition();
    _oldCameraY = locationState->location()->camera()->yPosition();

    locationState->location()->camera()->setXPosition(Location::hexagonToX(critter()->position()));
    locationState->location()->camera()->setYPosition(Location::hexagonToY(critter()->position()) + 100);
    locationState->location()->checkObjectsToRender();
    locationState->generateUi();

    auto background = std::shared_ptr<Image>(new Image("art/intrface/alltlk.frm"));
    auto background2 = std::shared_ptr<Image>(new Image("art/intrface/di_talk.frm"));
    background2->setY(291);

    add(background);
    add(background2);
    add(_question);

}

void CritterDialogState::think()
{
}

void CritterDialogState::close()
{
    auto camera = Game::getInstance()->location()->camera();
    camera->setXPosition(_oldCameraX);
    camera->setYPosition(_oldCameraY);
}

void CritterDialogState::onAnswerClick(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto state = dynamic_cast<CritterDialogState*>(event->reciever());

    int i = 0;
    for (auto answer : state->_answers)
    {
        if (answer.get() == sender)
        {
            auto newOffset =  state->_script->script()->function(state->_functions.at(i));
            std::cout << "NewOffset: " << newOffset << std::endl;
            auto oldOffset = state->_script->programCounter() - 2;
            std::cout << "OldOffset: " << oldOffset << std::endl;
            deleteAnswers();
            state->_script->pushDataInteger(0); // arguments counter;
            state->_script->pushReturnInteger(oldOffset); // return adrress
            state->_script->setProgramCounter(newOffset);
            state->_script->run();
            //script()->popDataInteger(); // remove function result
            //script()->setProgramCounter(oldOffset);
            return;
        }
        ++i;
    }
}

void CritterDialogState::onAnswerIn(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto font3_a0a0a0ff = ResourceManager::font("font1.aaf", 0xa0a0a0ff);
    sender->setFont(font3_a0a0a0ff);
}

void CritterDialogState::onAnswerOut(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto font3_3ff800ff = ResourceManager::font("font1.aaf", 0x3ff800ff);
    sender->setFont(font3_3ff800ff);
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

void CritterDialogState::setQuestion(std::string* value)
{
    _question->setText(*value);
}

std::vector<int>* CritterDialogState::functions()
{
    return &_functions;
}

std::vector<int>* CritterDialogState::reactions()
{
    return &_reactions;
}

void CritterDialogState::deleteAnswers()
{
    while(!_answers.empty())
    {
        _ui.pop_back();
        _answers.pop_back();
    }
    _functions.clear();
    _reactions.clear();
}

void CritterDialogState::addAnswer(std::string text)
{
    std::string line = "";
    //line += 0x95;
    line += "-";
    line += " ";
    line += text;

    int y = 345;
    for (auto answer : _answers)
    {
        y += answer->height() + 15;
    }

    auto answer = std::shared_ptr<TextArea>(new TextArea(line, 140, y));
    answer->setBackgroundColor(0x00000001);
    answer->setWordWrap(true);
    answer->setWidth(370);

    answer->addEventHandler("mousein", this, (EventRecieverMethod)&CritterDialogState::onAnswerIn);
    answer->addEventHandler("mouseout", this, (EventRecieverMethod)&CritterDialogState::onAnswerOut);
    answer->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&CritterDialogState::onAnswerClick);
    _answers.push_back(answer);
    add(answer);
}

bool CritterDialogState::hasAnswers()
{
    return _answers.size() > 0;
}


}
