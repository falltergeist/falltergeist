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
#include <vector>
#include <algorithm>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Hexagon.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameCritterObject.h"
#include "../States/CritterDialogState.h"
#include "../States/CritterDialogReviewState.h"
#include "../States/CritterInteractState.h"
#include "../States/CritterBarterState.h"
#include "../States/LocationState.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
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
    setModal(false);

    setX((Game::getInstance()->renderer()->width() - 640)*0.5);
    setY((Game::getInstance()->renderer()->height() - 480)*0.5 + 291);

    auto background = std::shared_ptr<Image>(new Image("art/intrface/di_talk.frm"));
    addUI("background", background);
    background->addEventHandler("keyup", this, (EventRecieverMethod) &CritterDialogState::onKeyboardUp);

    auto question = std::shared_ptr<TextArea>(new TextArea("question", 140, -55));
    question->setWidth(370);
    question->setWordWrap(true);
    addUI("question", question);

    // Interface buttons
    auto reviewButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_REVIEW_BUTTON, 13, 154));
    reviewButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterDialogState::onReviewButtonClick);
    addUI(reviewButton);

    auto barterButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_DIALOG_RED_BUTTON, 593, 40));
    barterButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &CritterDialogState::onBarterButtonClick);
    addUI(barterButton);
}

void CritterDialogState::think()
{
    State::think();
}

void CritterDialogState::setQuestion(std::string value)
{
    auto question = std::dynamic_pointer_cast<TextArea>(getUI("question"));
    question->setText(value);
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

void CritterDialogState::onReviewButtonClick(std::shared_ptr<Event> event)
{
    // FIXME : don't create new state each time the button is clicked
    auto critterReviewDialogState = new CritterDialogReviewState();
    Game::getInstance()->pushState(critterReviewDialogState);
}

void CritterDialogState::onBarterButtonClick(std::shared_ptr<Event> event)
{
    // FIXME : don't create new state each time the button is clicked
    auto critterBarterState = new CritterBarterState();
    Game::getInstance()->pushState(critterBarterState);
}

void CritterDialogState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    static std::vector<uint> numkeys = {
            SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
            SDLK_KP_1, SDLK_KP_2, SDLK_KP_3, SDLK_KP_4, SDLK_KP_5, SDLK_KP_6, SDLK_KP_7, SDLK_KP_8, SDLK_KP_9,
    };

    auto key = event->keyCode();

    if (key == SDLK_0 || key == SDLK_KP_0)
    {
        // Todo: end dialog
        return;
    }

    auto keyIt = std::find(numkeys.begin(), numkeys.end(), key);
    // Number key pressed
    if (keyIt != numkeys.end())
    {
        size_t keyOffset = keyIt - numkeys.begin();

        // If numpad key
        if (keyOffset > 8) keyOffset -= 9;

        if (keyOffset < _answers.size()) _selectAnswer(keyOffset);
        return;
    }
}

void CritterDialogState::_selectAnswer(size_t i)
{
    if (i >= _answers.size()) throw Exception("No answer with number " + std::to_string(i));

    auto game = Game::getInstance();
    auto dialog = dynamic_cast<CritterInteractState*>(game->states()->at(game->states()->size() - 2));

    auto newOffset = dialog->script()->script()->function(_functions.at(i));
    auto oldOffset = dialog->script()->programCounter() - 2;
    deleteAnswers();
    dialog->script()->pushDataInteger(0); // arguments counter;
    dialog->script()->pushReturnInteger(oldOffset); // return adrress
    dialog->script()->setProgramCounter(newOffset);
    dialog->script()->run();
}


void CritterDialogState::addAnswer(std::string text)
{
    std::string line = "";
    line += 0x95;
    line += " ";
    line += text;

    int y = 50;
    for (auto answer : _answers)
    {
        y += answer->height() + 5;
    }

    auto answer = std::shared_ptr<TextArea>(new TextArea(line, 140, y));
    answer->setBackgroundColor(0x00000001);
    answer->setWordWrap(true);
    answer->setWidth(370);

    answer->addEventHandler("mousein", this, (EventRecieverMethod)&CritterDialogState::onAnswerIn);
    answer->addEventHandler("mouseout", this, (EventRecieverMethod)&CritterDialogState::onAnswerOut);
    answer->addEventHandler("mouseleftclick", this, (EventRecieverMethod)&CritterDialogState::onAnswerClick);
    _answers.push_back(answer);
    addUI(answer);
}

bool CritterDialogState::hasAnswers()
{
    return _answers.size() > 0;
}



void CritterDialogState::onAnswerClick(std::shared_ptr<Event> event)
{
    auto sender = dynamic_cast<TextArea*>(event->emitter());

    size_t i = 0;
    for (auto answer : _answers)
    {
        if (answer.get() == sender)
        {
            _selectAnswer(i);
            return;
        }
        ++i;
    }
}


}
