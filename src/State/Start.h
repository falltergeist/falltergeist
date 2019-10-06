#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace State
    {
        class Start : public State
        {
            public:
                Start();
                ~Start() override;

                void think() override;
                void init() override;

            protected:
                unsigned int _splashTicks = 0;
        };
    }
}
