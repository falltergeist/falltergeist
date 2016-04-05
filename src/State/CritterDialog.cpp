/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include "../State/CritterDialog.h"

// C++ standard includes
#include <algorithm>
#include <vector>

// Falltergeist includes
#include "../Exception.h"
#include "../Format/Int/File.h"
#include "../Format/Int/Procedure.h"
#include "../Game/CritterObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/CritterBarter.h"
#include "../State/CritterDialogReview.h"
#include "../State/CritterInteract.h"
#include "../State/Location.h"
#include "../UI/Image.h"
#include "../UI/TextArea.h"
#include "../VM/Script.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        CritterDialog::CritterDialog() : State()
        {
        }

        CritterDialog::~CritterDialog()
        {
        }

        void CritterDialog::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(false);

            setPosition((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2 + Point(0, 291));

            auto background = new UI::Image("art/intrface/di_talk.frm");
            addUI("background", background);

            auto question = new UI::TextArea("question", 140, -62);
            question->setSize({375, 53});
            // TODO: maybe padding properties should be removed from TextArea to simplify it. Use invisible panel for mouse interactions.
            question->setPadding({0, 5}, {0, 5});
            question->setWordWrap(true);
            addUI("question", question);

            // TODO: maybe move text scrolling into separate UI? Though it is only in two places and works slightly differently...
            question->mouseClickHandler().add([this, question](Event::Mouse* event)
                {
                    Point relPos = event->position() - question->position();
                    if (relPos.y() < (question->size().height() / 2))
                    {
                        if (question->lineOffset() > 0)
                        {
                            question->setLineOffset(question->lineOffset() - 4);
                        }
                    }
                    else if (question->lineOffset() < question->numLines() - 4)
                    {
                        question->setLineOffset(question->lineOffset() + 4);
                    }
                });

            question->mouseMoveHandler().add([this, question](Event::Mouse* event)
                {
                    if (question->numLines() > 4)
                    {
                        auto mouse = Game::getInstance()->mouse();
                        Point relPos = event->position() - question->position();
                        auto state = relPos.y() < (question->size().height() / 2)
                            ? Input::Mouse::Cursor::SMALL_UP_ARROW
                            : Input::Mouse::Cursor::SMALL_DOWN_ARROW;

                        if (mouse->state() != state)
                        {
                            mouse->setState(state);
                        }
                    }
                });

             question->mouseOutHandler().add([question](Event::Mouse* event)
                {
                    Game::getInstance()->mouse()->setState(Input::Mouse::Cursor::BIG_ARROW);
                });

            // Interface buttons
            auto reviewButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_REVIEW_BUTTON, 13, 154);
            reviewButton->mouseClickHandler().add(std::bind(&CritterDialog::onReviewButtonClick, this, std::placeholders::_1));
            addUI(reviewButton);

            auto barterButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_RED_BUTTON, 593, 40);
            barterButton->mouseClickHandler().add(std::bind(&CritterDialog::onBarterButtonClick, this, std::placeholders::_1));
            addUI(barterButton);
        }

        void CritterDialog::think()
        {
            State::think();
        }

        // TODO: add auto-text scrolling after 10 seconds (when it's longer than 4 lines)
        void CritterDialog::setQuestion(const std::string& value)
        {
            auto question = getTextArea("question");
            question->setText(std::string("  ") + value);
            question->setLineOffset(0);
        }

        void CritterDialog::onAnswerIn(Event::Mouse* event)
        {
            auto sender = dynamic_cast<UI::TextArea*>(event->target());
            sender->setFont("font1.aaf", {0xff, 0xff, 0x7f, 0xff});
        }

        void CritterDialog::onAnswerOut(Event::Mouse* event)
        {
            auto sender = dynamic_cast<UI::TextArea*>(event->target());
            sender->setFont("font1.aaf", {0x3f,0xf8, 0x00, 0xff});
        }

        std::vector<int>* CritterDialog::functions()
        {
            return &_functions;
        }

        std::vector<int>* CritterDialog::reactions()
        {
            return &_reactions;
        }

        void CritterDialog::deleteAnswers()
        {
            while(!_answers.empty())
            {
                _answers.pop_back();
                popUI();
            }
            _functions.clear();
            _reactions.clear();
        }

        void CritterDialog::onReviewButtonClick(Event::Mouse* event)
        {
            // FIXME : don't create new state each time the button is clicked
            auto state = new CritterDialogReview();
            Game::getInstance()->pushState(state);
        }

        void CritterDialog::onBarterButtonClick(Event::Mouse* event)
        {
            // FIXME : don't create new state each time the button is clicked
            auto state = new CritterBarter();
            Game::getInstance()->pushState(state);
        }

        void CritterDialog::onKeyDown(Event::Keyboard* event)
        {
            static std::vector<uint32_t> numkeys = {
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

            auto question = dynamic_cast<UI::TextArea*>(getUI("question"));
            if (key == SDLK_UP && question->lineOffset() > 0)
            {
                question->setLineOffset(question->lineOffset() - 4);
            }
            else if (key == SDLK_DOWN && question->lineOffset() < question->numLines() - 4)
            {
                question->setLineOffset(question->lineOffset() + 4);
            }
        }

        void CritterDialog::_selectAnswer(size_t i)
        {
            if (i >= _answers.size()) throw Exception("No answer with number " + std::to_string(i));

            auto game = Game::getInstance();
            auto dialog = dynamic_cast<CritterInteract*>(game->topState(1));

            // @todo optimize
            int newOffset = dialog->script()->script()->procedures()->at(_functions.at(i))->bodyOffset();
            int oldOffset = dialog->script()->programCounter() - 2;
            deleteAnswers();
            dialog->script()->dataStack()->push(0); // arguments counter;
            dialog->script()->returnStack()->push(oldOffset); // return adrress
            dialog->script()->setProgramCounter(newOffset);
            dialog->script()->run();
        }


        void CritterDialog::addAnswer(const std::string& text)
        {
            std::string line = "";
            line += 0x95;
            line += " ";
            line += text;

            int y = 50;
            for (auto answer : _answers)
            {
                y += answer->textSize().height() + 5;
            }

            auto answer = new UI::TextArea(line, 140, y);
            answer->setWordWrap(true);
            answer->setSize({370, 0});

            answer->mouseInHandler().add(std::bind(&CritterDialog::onAnswerIn, this, std::placeholders::_1));
            answer->mouseOutHandler().add(std::bind(&CritterDialog::onAnswerOut, this, std::placeholders::_1));
            answer->mouseClickHandler().add(std::bind(&CritterDialog::onAnswerClick, this, std::placeholders::_1));
            _answers.push_back(answer);
            addUI(answer);
        }

        bool CritterDialog::hasAnswers()
        {
            return _answers.size() > 0;
        }

        void CritterDialog::onAnswerClick(Event::Mouse* event)
        {
            auto sender = dynamic_cast<UI::TextArea*>(event->target());

            size_t i = 0;
            for (auto answer : _answers)
            {
                if (answer == sender)
                {
                    _selectAnswer(i);
                    return;
                }
                ++i;
            }
        }
    }
}
