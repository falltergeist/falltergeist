#pragma once

#include <map>
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
        class Rectangle;
        class TextArea;
    }
    namespace State
    {
        class PlayerEditName final : public State
        {
            public:
                PlayerEditName(std::shared_ptr<UI::IResourceManager> resourceManager);
                virtual ~PlayerEditName() = default;

                void init() override;
                void think(const float &deltaTime) override;

                void onDoneButtonClick(Event::Mouse* event);
                void onTextAreaKeyDown(Event::Keyboard* event);

                void doDone();
                void doBack();

            protected:
                float _blinkingCursorMillisecondsTracked = 0;
                UI::TextArea* _name = nullptr;
                UI::Rectangle* _cursor = nullptr;
                std::map<char,char> _keyCodes;

            private:
                std::shared_ptr<UI::IResourceManager> resourceManager;
                std::unique_ptr<UI::Factory::ImageButtonFactory> imageButtonFactory;
        };
    }
}
