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

#ifndef FALLTERGEIST_STATE_CRITTERDIALOG_H
#define FALLTERGEIST_STATE_CRITTERDIALOG_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../State/State.h"

// Third party includes

namespace Falltergeist
{
    namespace Event
    {
        class Event;
        class Keyboard;
    }
    namespace UI
    {
        class TextArea;
    }
    namespace State
    {
        class CritterDialog : public State
        {
            public:
                CritterDialog();
                ~CritterDialog() override;
                void init() override;
                void think() override;

                void setQuestion(const std::string& value);

                std::vector<int>* functions();
                std::vector<int>* reactions();

                void deleteAnswers();
                bool hasAnswers();
                void addAnswer(const std::string& text);

                void onReviewButtonClick(Event::Mouse* event);
                void onBarterButtonClick(Event::Mouse* event);
                void onAnswerIn(Event::Mouse* event);
                void onAnswerOut(Event::Mouse* event);
                void onAnswerClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                std::vector<int> _functions;
                std::vector<int> _reactions;
                std::vector<UI::TextArea*> _answers;

                void _selectAnswer(size_t i);
        };
    }
}
#endif // FALLTERGEIST_STATE_CRITTERDIALOG_H
