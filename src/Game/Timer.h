#pragma once

#include "../Game/AbstractTimer.h"

namespace Falltergeist
{
    namespace Game
    {
        /**
         * @brief Real-time timer.
         * Operates in milliseconds (1000 is one real-time second).
         */
        class Timer : public AbstractTimer
        {
            public:
                Timer(unsigned interval = 1000);

            protected:
                unsigned int _getTime() override;
        };
    }
}
