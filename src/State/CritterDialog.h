#pragma once

#include <vector>
#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace Event
    {
        class Event;
        class Keyboard;
    }
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }

        class TextArea;
    }
    namespace State
    {
        class CritterDialog final : public State
        {
            public:
                CritterDialog(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~CritterDialog() = default;

                void init() override;

                void setQuestion(const std::string& value);

                std::vector<int>* functions();

                std::vector<int>* reactions();

                void deleteAnswers();

                bool hasAnswers();

                void addAnswer(const std::string& text);

                void onReviewButtonClick(Event::Mouse* event);

                void onBarterButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

            protected:
                std::vector<int> _functions;

                std::vector<int> _reactions;

                std::vector<UI::TextArea*> _answers;

                void _selectAnswer(size_t i);

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;

                void onAnswerIn(UI::TextArea* target);

                void onAnswerOut(UI::TextArea* target);

                void onAnswerClick(UI::TextArea* target);
        };
    }
}
