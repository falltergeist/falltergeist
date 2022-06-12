#pragma once

// Project includes
#include "../State/State.h"
#include "../UI/IResourceManager.h"

// Third-party includes

// stdlib
#include <map>

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
        class Mouse;
        class State;
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
        class SettingsMenu final : public State
        {
            public:
                SettingsMenu(std::shared_ptr<UI::IResourceManager> resourceManager);

                virtual ~SettingsMenu() = default;

                void init() override;

                void onDefaultButtonClick(Event::Mouse* event);

                void doCancel();

                void doSave();

                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

            private:
                std::shared_ptr<UI::TextArea> _addLabel(const std::string& name, std::shared_ptr<UI::TextArea> label);

                std::shared_ptr<UI::TextArea> _addTextArea(const std::string& message, unsigned int x, unsigned int y);

                std::shared_ptr<UI::TextArea> _addTextArea(std::shared_ptr<UI::TextArea> parent, unsigned int x, unsigned int y);

                std::map<std::string, std::shared_ptr<UI::TextArea>> _labels;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
