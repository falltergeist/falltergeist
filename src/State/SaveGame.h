#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class SaveGame : public State
        {
            public:
                SaveGame();
                ~SaveGame() override;

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
                void onCancelButtonClick(Event::Mouse* event);

                void onStateActivate(Event::State* event) override;
                void onStateDeactivate(Event::State* event) override;
                void onKeyDown(Event::Keyboard* event) override;
        };
    }
}
