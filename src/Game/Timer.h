#pragma once

// Project includes
#include "../Event/Handler.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Game
    {
        class Timer final
        {
            public:
                explicit Timer(const float &milliseconds = 1000.0f);

                void start();

                void start(const float &interval, bool repeat = false);

                void stop();

                bool enabled() const;

                void setInterval(const float &interval);

                Event::Handler& tickHandler();

                void think(const float &deltaTime);

            private:
                Event::Handler _tickHandler;

                bool _enabled = false;
                bool _repeat = false;
                float _interval = 0;
                float _timeTracked = 0;
        };
    }
}
