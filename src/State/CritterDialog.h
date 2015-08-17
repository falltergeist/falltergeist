/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_CritterDialog_H
#define FALLTERGEIST_CritterDialog_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../State/State.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Event;
    class Keyboard;
}

namespace State
{

class CritterDialog : public State
{
protected:

    std::vector<int> _functions;
    std::vector<int> _reactions;
    std::vector<TextArea*> _answers;

    void _selectAnswer(size_t i);

public:
    CritterDialog();
    virtual ~CritterDialog();
    virtual void init();
    virtual void think();

    void setQuestion(const std::string& value);

    std::vector<int>* functions();
    std::vector<int>* reactions();

    void deleteAnswers();
    bool hasAnswers();
    void addAnswer(const std::string& text);

    void onReviewButtonClick(Event::Event* event);
    void onBarterButtonClick(Event::Event* event);
    void onAnswerIn(Event::Event* event);
    void onAnswerOut(Event::Event* event);
    void onAnswerClick(Event::Event* event);
    void onKeyDown(Event::Keyboard* event) override;

};

}
}
#endif // FALLTERGEIST_CritterDialog_H
