#pragma once

#include <string>
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
        class PlayerEditAlert final : public State
        {
            public:
                PlayerEditAlert(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse,
                    const std::string& message
                );

                virtual ~PlayerEditAlert() = default;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);

            private:
                std::string _message;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
