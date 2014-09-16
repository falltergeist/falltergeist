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
#include "../Engine/Screen.h"
#include "../Engine/Surface.h"
#include "../Game/GameCritterObject.h"
#include "../States/CritterDialogState.h"
#include "../States/LocationState.h"
#include "../UI/Image.h"
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

    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    background2->setX(backgroundX);
    background2->setY(backgroundY+291);

    // review button
    auto reviewButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_REVIEW_BUTTON, backgroundX+13, backgroundY+445));

    // barter button
    auto barterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, backgroundX+593, backgroundY+331));

    add(background);
    add(background2);
    add(reviewButton);
    add(barterButton);
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
    line += 0x95;
    line += " ";
    line += text;

    auto backgroundX = (Game::getInstance()->renderer()->width() - 640)*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - 480)*0.5;

    int y = 345 + backgroundY;
    for (auto answer : _answers)
    {
        y += answer->height() + 12;
    }

    auto answer = std::shared_ptr<TextArea>(new TextArea(line, backgroundX+140, y));
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
