#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib

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
        class PlayerCreateOptions final : public State
        {
            public:
                PlayerCreateOptions(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~PlayerCreateOptions() = default;

                void init() override;

                void onSaveButtonClick(Event::Mouse* event);

                void onLoadButtonClick(Event::Mouse* event);

                void onPrintToFileButtonClick(Event::Mouse* event);

                void onEraseButtonClick(Event::Mouse* event);

                void onDoneButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
