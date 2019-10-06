#pragma once

#include "../Format/Enums.h"
#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class Skilldex : public State
        {
            public:
                Skilldex();
                ~Skilldex() override;

                void init() override;


                void onKeyDown(Event::Keyboard* event) override;
                void onStateActivate(Event::State* event) override;

                void onCancelButtonClick();
                void onSkillButtonClick(SKILL skill);
        };
    }
}
