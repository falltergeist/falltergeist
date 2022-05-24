#pragma once

#include "../State/State.h"
#include "../UI/IResourceManager.h"

namespace Falltergeist
{
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
    }

    namespace State
    {
        class CritterDialogReview final : public State
        {
            public:
                CritterDialogReview(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

                virtual ~CritterDialogReview() = default;

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

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
