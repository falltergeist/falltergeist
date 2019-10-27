#pragma once

#include <map>
#include "../State/State.h"

namespace Falltergeist
{
    namespace UI
    {
        class Rectangle;
        class TextArea;
    }
    namespace State
    {
        class PlayerEditName : public State
        {
            public:
                PlayerEditName();
                ~PlayerEditName() override;

                void init() override;
                void think(uint32_t nanosecondsPassed) override;

                void onDoneButtonClick(Event::Mouse* event);
                void onTextAreaKeyDown(Event::Keyboard* event);

                void doDone();
                void doBack();

            protected:
                uint32_t _blinkingCursorNanosecondsTracked = 0;
                UI::TextArea* _name = nullptr;
                UI::Rectangle* _cursor = nullptr;
                std::map<char,char> _keyCodes;
        };
    }
}
