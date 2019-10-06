#pragma once

#include <vector>
#include "../State/State.h"

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
