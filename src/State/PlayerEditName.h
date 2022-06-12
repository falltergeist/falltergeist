#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib
#include <map>

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

                void doDone();

                void doBack();

            private:
                void _onTextAreaKeyDown(Event::Keyboard* event, std::shared_ptr<UI::TextArea> target);

                float _blinkingCursorMillisecondsTracked = 0;

                std::shared_ptr<UI::TextArea> _name = nullptr;

                std::shared_ptr<UI::Rectangle> _cursor = nullptr;

                std::map<char,char> _keyCodes;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
