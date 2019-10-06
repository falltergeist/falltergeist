#pragma once

#include <map>
#include "../State/State.h"

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
        class TextArea;
    }
    namespace State
    {
        class SettingsMenu : public State
        {
            public:
                SettingsMenu();
                ~SettingsMenu() override;

                void init() override;
                void think() override;

                void onDefaultButtonClick(Event::Mouse* event);
                void doCancel();
                void doSave();

                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
            protected:
                std::map<std::string, UI::TextArea*> _labels;
                UI::TextArea* _addLabel(const std::string& name, UI::TextArea* label);
                UI::TextArea* _addTextArea(const std::string& message, unsigned int x, unsigned int y);
                UI::TextArea* _addTextArea(UI::TextArea* parent, unsigned int x, unsigned int y);
        };
    }
}
