#pragma once

#include <string>
#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class PlayerEditAlert : public State
        {
            public:
                PlayerEditAlert();
                ~PlayerEditAlert() override;

                void setMessage(const std::string& message);

                void init() override;

                void onDoneButtonClick(Event::Mouse* event);
            protected:
                std::string _message;
        };
    }
}
