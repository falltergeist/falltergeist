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
                PipBoy(std::shared_ptr<UI::IResourceManager> resourceManager);
                ~PipBoy() override;

                void init() override;

                void onCloseButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;

                std::string getSpecialGreeting(int month, int day);
        };
    }
}
