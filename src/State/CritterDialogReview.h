#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class CritterDialogReview : public State
        {
            public:
                CritterDialogReview();
                ~CritterDialogReview() override;

                void init() override;

                virtual void onStateActivate(Event::State *event) override;

                void onDoneButtonClick(Event::Mouse* event);
                void onUpButtonClick(Event::Mouse* event);
                void onDownButtonClick(Event::Mouse* event);

                void setCritterName(const std::string& value);

                void addAnswer(const std::string& value);
                void addQuestion(const std::string& value);
            private:
                std::string _critterName;

        };
    }
}
