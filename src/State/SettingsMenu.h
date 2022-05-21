#pragma once

#include <map>
#include "../State/State.h"
#include "../UI/IResourceManager.h"

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
                SettingsMenu(
                    std::shared_ptr<UI::IResourceManager> resourceManager,
                    std::shared_ptr<Input::Mouse> mouse
                );

                virtual ~SettingsMenu() = default;

                void init() override;

                void onDefaultButtonClick(Event::Mouse* event);

                void doCancel();

                void doSave();

                void onKeyDown(Event::Keyboard* event) override;

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

            private:
                UI::TextArea* _addLabel(const std::string& name, UI::TextArea* label);

                UI::TextArea* _addTextArea(const std::string& message, unsigned int x, unsigned int y);

                UI::TextArea* _addTextArea(UI::TextArea* parent, unsigned int x, unsigned int y);

                std::map<std::string, UI::TextArea*> _labels;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;
        };
    }
}
