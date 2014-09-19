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
#include "../Engine/ResourceManager.h"
#include "../States/CritterBarterState.h"
#include "../States/CritterDialogReviewState.h"
#include "../States/CritterDialogState.h"
#include "../States/CritterTalkState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../VM/VM.h"

// Third party includes

namespace Falltergeist
{

CritterTalkState::CritterTalkState() : CritterTalkState(0, 0)
{
}

CritterTalkState::CritterTalkState(int offsetX, int offsetY)
        : State(), _offsetX(offsetX), _offsetY(offsetY)
{
}

CritterTalkState::~CritterTalkState()
{
}

void CritterTalkState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(false);
    setModal(false);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/di_talk.frm"));
    background->setX(_offsetX);
    background->setY(_offsetY);

    // Interface buttons
    auto reviewButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_REVIEW_BUTTON, _offsetX+13, _offsetY+154));
    reviewButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterTalkState::onReviewButtonClick);

    auto barterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, _offsetX+593, _offsetY+40));
    barterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterTalkState::onBarterButtonClick);

    add(background);
    add(reviewButton);
    add(barterButton);
}

void CritterTalkState::setOffsetX(int offsetX)
{
    _offsetX = offsetX;
}

void CritterTalkState::setOffsetY(int offsetY)
{
    _offsetY = offsetY;
}

void CritterTalkState::onAnswerClick(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto dialog = Game::getInstance()->dialog();

    int i = 0;
    for (auto answer : _answers)
    {
        if (answer.get() == sender)
        {
            auto newOffset =  dialog->script()->script()->function(_functions.at(i));
            auto oldOffset = dialog->script()->programCounter() - 2;
            deleteAnswers();
            dialog->script()->pushDataInteger(0); // arguments counter;
            dialog->script()->pushReturnInteger(oldOffset); // return adrress
            dialog->script()->setProgramCounter(newOffset);
            dialog->script()->run();
            //script()->popDataInteger(); // remove function result
            //script()->setProgramCounter(oldOffset);
            return;
        }
        ++i;
    }
}

void CritterTalkState::onAnswerIn(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto font3_a0a0a0ff = ResourceManager::font("font1.aaf", 0xa0a0a0ff);
    sender->setFont(font3_a0a0a0ff);
}

void CritterTalkState::onAnswerOut(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());
    auto font3_3ff800ff = ResourceManager::font("font1.aaf", 0x3ff800ff);
    sender->setFont(font3_3ff800ff);
}

std::vector<int>* CritterTalkState::functions()
{
    return &_functions;
}

std::vector<int>* CritterTalkState::reactions()
{
    return &_reactions;
}

void CritterTalkState::deleteAnswers()
{
    while(!_answers.empty())
    {
        _ui.pop_back();
        _answers.pop_back();
    }
    _functions.clear();
    _reactions.clear();
}

void CritterTalkState::addAnswer(std::string text)
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
        y += answer->height() + 5;
    }

    auto answer = std::shared_ptr<TextArea>(new TextArea(line, backgroundX+140, y));
    answer->setBackgroundColor(0x00000001);
    answer->setWordWrap(true);
    answer->setWidth(370);

    answer->addEventHandler("mousein", this, (EventRecieverMethod)&CritterTalkState::onAnswerIn);
    answer->addEventHandler("mouseout", this, (EventRecieverMethod)&CritterTalkState::onAnswerOut);
    answer->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&CritterTalkState::onAnswerClick);
    _answers.push_back(answer);
    add(answer);
}

bool CritterTalkState::hasAnswers()
{
    return _answers.size() > 0;
}

void CritterTalkState::onReviewButtonClick(std::shared_ptr<Event> event)
{
    // FIXME : don't create new state each time the button is clicked
    auto critterReviewDialogState = std::shared_ptr<CritterDialogReviewState>(new CritterDialogReviewState());
    Game::getInstance()->pushState(critterReviewDialogState);
}

void CritterTalkState::onBarterButtonClick(std::shared_ptr<Event> event)
{
    // FIXME : don't create new state each time the button is clicked
    auto critterBarterState = std::shared_ptr<CritterBarterState>(new CritterBarterState(_offsetX, _offsetY));
    Game::getInstance()->popState();
    Game::getInstance()->pushState(critterBarterState);
}

}
