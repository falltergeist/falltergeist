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
        class PipBoy final: public State
        {
            public:
                PipBoy(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

                ~PipBoy() override;

                void init() override;

                void onCloseButtonClick(Event::Mouse* event);

                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::string _getSpecialGreeting(int month, int day);

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
