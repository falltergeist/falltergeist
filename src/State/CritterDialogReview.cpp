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
#include "../State/CritterDialogReview.h"

// C++ standard includes

// Falltergeist includes
#include "../Game/Game.h"
#include "../Game/DudeObject.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Size.h"
#include "../State/CritterInteract.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"
#include "../UI/TextAreaList.h"

// Third party includes

namespace Falltergeist
{
using Graphics::Size;
    namespace State
    {
        CritterDialogReview::CritterDialogReview() : State()
        {
        }

        CritterDialogReview::~CritterDialogReview()
        {
        }

        void CritterDialogReview::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(false);

            auto background = new UI::Image("art/intrface/review.frm");
            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background->size()) / 2);
            background->setPosition(backgroundPos);

            // Interface buttons
            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DONE_BUTTON, backgroundPos + Point(500, 398));
            doneButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onDoneButtonClick, this, std::placeholders::_1));

            auto upButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_BIG_UP_ARROW, backgroundPos + Point(476, 154));
            upButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onUpButtonClick, this, std::placeholders::_1));

            auto downButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_BIG_DOWN_ARROW, backgroundPos + Point(476, 192));
            downButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onDownButtonClick, this, std::placeholders::_1));

            addUI(background);
            addUI(doneButton);
            addUI(upButton);
            addUI(downButton);
            auto list = new UI::TextAreaList(Point(88,76));
            list->setSize(Size(340,340));
            addUI("list",list);
        }


        void CritterDialogReview::onStateActivate(Event::State *event)
        {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollTo(0);
        }


        void CritterDialogReview::onDoneButtonClick(Event::Mouse* event)
        {
            if (auto interact = dynamic_cast<CritterInteract*>(Game::getInstance()->topState(1)))
            {
                interact->switchSubState(CritterInteract::SubState::DIALOG);
            }
        }


        void CritterDialogReview::onUpButtonClick(Event::Mouse *event)
        {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollUp(4);
        }

        void CritterDialogReview::onDownButtonClick(Event::Mouse *event)
        {
            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->scrollDown(4);
        }


        void CritterDialogReview::setCritterName(const std::string &value)
        {
            _critterName = value;
        }

        void CritterDialogReview::addAnswer(const std::string &value)
        {
            auto dudeName = new UI::TextArea(0, 0);
            dudeName->setWidth(340);
            dudeName->setWordWrap(true);
            dudeName->setFont("font1.aaf", {0xa0,0xa0, 0xa0, 0xff});
            dudeName->setText(Game::getInstance()->player()->name()+":");

            auto answer = new UI::TextArea(0, 0);
            answer->setWidth(316);
            answer->setOffset(26,0);
            answer->setWordWrap(true);
            answer->setFont("font1.aaf", {0x74,0x74, 0x74, 0xff});
            answer->setText(value);

            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->addArea(std::unique_ptr<UI::TextArea>(dudeName));
            list->addArea(std::unique_ptr<UI::TextArea>(answer));
        }

        void CritterDialogReview::addQuestion(const std::string &value)
        {
            auto crName = new UI::TextArea(0, 0);
            crName->setWidth(340);
            crName->setWordWrap(true);
            crName->setFont("font1.aaf", {0x3f,0xf8, 0x00, 0xff});
            crName->setText(_critterName+":");

            auto question = new UI::TextArea(0, 0);
            question->setWidth(316);
            question->setOffset(26,0);
            question->setWordWrap(true);
            question->setFont("font1.aaf", {0x00,0xa4, 0x00, 0xff});
            question->setText(value);

            auto list = dynamic_cast<UI::TextAreaList*>(getUI("list"));
            list->addArea(std::unique_ptr<UI::TextArea>(crName));
            list->addArea(std::unique_ptr<UI::TextArea>(question));

        }


    }
}
