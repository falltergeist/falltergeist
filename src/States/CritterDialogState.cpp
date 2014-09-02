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
    _question = new TextArea("", 140, 235);
    _question->setWidth(370);
    _question->setWordWrap(true);
}

CritterDialogState::~CritterDialogState()
{
    //delete _question;
    auto camera = Game::getInstance().location()->camera();
    camera->setXPosition(_oldCameraX);
    camera->setYPosition(_oldCameraY);
    Game::getInstance().location()->generateBackground();
    Game::getInstance().location()->checkObjectsToRender();
}

void CritterDialogState::init()
{
    if (_initialized) return;
    State::init();
    setFullscreen(false);

    auto camera = Game::getInstance().location()->camera();
    _oldCameraX = camera->xPosition();
    _oldCameraY = camera->yPosition();
    camera->setXPosition(Location::hexagonToX(critter()->position()));
    camera->setYPosition(Location::hexagonToY(critter()->position()) + 100);

    auto background = new Image("art/intrface/alltlk.frm");
    auto background2 = new Image("art/intrface/di_talk.frm");
    background2->setY(291);

    add(background);
    add(background2);
    add(_question);

}

void CritterDialogState::blit()
{

    /*
    int offset = 0;
    for (TextArea* answer : _answers)
    {
        answer->setY(345 + offset);
        offset += answer->height() + 5;
        answer->blit(_game->screen()->surface());
    }
    */

}

void CritterDialogState::onAnswerClick(Event* event)
{
    TextArea* sender = dynamic_cast<TextArea*>((TextArea*)event->emitter());

    int i = 0;
    for (auto answer : _answers)
    {
        if (answer == sender)
        {
            auto newOffset =  script()->script()->function(_functions.at(i));
            auto oldOffset = _script->programCounter() - 2;
            deleteAnswers();
            script()->pushDataInteger(0); // arguments counter;
            script()->pushReturnInteger(oldOffset); // return adrress
            script()->setProgramCounter(newOffset);
            script()->run();
            //script()->popDataInteger(); // remove function result
            //script()->setProgramCounter(oldOffset);
            return;
        }
        ++i;
    }
}

void CritterDialogState::onAnswerIn(Event* event)
{
    TextArea* sender = dynamic_cast<TextArea*>((TextArea*)event->emitter());
    auto font3_a0a0a0ff = _game->resourceManager()->font("font3.aaf", 0xa0a0a0ff);
    sender->setFont(font3_a0a0a0ff);
}

void CritterDialogState::onAnswerOut(Event* event)
{
    TextArea* sender = dynamic_cast<TextArea*>((TextArea*)event->emitter());
    auto font3_3ff800ff = _game->resourceManager()->font("font3.aaf", 0x3ff800ff);
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
    while (!_answers.empty())
    {
        delete _answers.back();
        _answers.back() = 0;
        _answers.pop_back();
    }
    _answers.clear();
    _functions.clear();
    _reactions.clear();
}

void CritterDialogState::addAnswer(std::string text)
{
    std::string line = "";
    line += 0x95;
    line += " ";
    line += text;

    auto answer = new TextArea(line, 140, 0);
    answer->setBackgroundColor(0x01000000);
    answer->setWordWrap(true);
    answer->setWidth(370);
    //answer->draw();
    answer->addEventHandler("mousein", this, (EventRecieverMethod)&CritterDialogState::onAnswerIn);
    answer->addEventHandler("mouseout", this, (EventRecieverMethod)&CritterDialogState::onAnswerOut);
    answer->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&CritterDialogState::onAnswerClick);
    _answers.push_back(answer);
}

void CritterDialogState::handle(Event *event)
{
    State::handle(event);
    for (auto answer : _answers)
    {
        if (answer)
        {
            //answer->draw();
            answer->handle(event);
        }
    }
}

bool CritterDialogState::hasAnswers()
{
    return _answers.size() > 0;
}


}
