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
#include "../Graphics/Renderer.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"

// Third party includes

namespace Falltergeist
{
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
            setModal(true);

            auto background = new UI::Image("art/intrface/review.frm");
            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background->size()) / 2);
            background->setPosition(backgroundPos);

            // Interface buttons
            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_DONE_BUTTON, backgroundPos + Point(500, 398));
            doneButton->mouseClickHandler().add(std::bind(&CritterDialogReview::onDoneButtonClick, this, std::placeholders::_1));

            auto upButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_BIG_UP_ARROW, backgroundPos + Point(476, 154));

            auto downButton = new UI::ImageButton(UI::ImageButton::Type::DIALOG_BIG_DOWN_ARROW, backgroundPos + Point(476, 192));

            addUI(background);
            addUI(doneButton);
            addUI(upButton);
            addUI(downButton);
        }

        void CritterDialogReview::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }
    }
}
