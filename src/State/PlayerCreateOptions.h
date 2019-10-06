#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class PlayerCreateOptions : public State
        {
            public:
                PlayerCreateOptions();
                ~PlayerCreateOptions() override;

                void init() override;

                void onSaveButtonClick(Event::Mouse* event);
                void onLoadButtonClick(Event::Mouse* event);
                void onPrintToFileButtonClick(Event::Mouse* event);
                void onEraseButtonClick(Event::Mouse* event);
                void onDoneButtonClick(Event::Mouse* event);
                void onKeyDown(Event::Keyboard* event) override;
        };
    }
}
