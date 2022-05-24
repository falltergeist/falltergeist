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
        class BigCounter;
    }
    namespace State
    {
        class PlayerEditAge final: public State
        {
            public:
                PlayerEditAge(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~PlayerEditAge() = default;

                void init() override;

                void onIncButtonClick(Event::Mouse* event);
                void onDecButtonClick(Event::Mouse* event);
                void onDoneButtonClick(Event::Mouse* event);
                void doInc();
                void doDec();
                void doDone();
                void doBack();
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                UI::BigCounter* _counter = nullptr;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
