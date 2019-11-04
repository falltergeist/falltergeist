#pragma once

#include "../Event/Handler.h"

namespace Falltergeist
{
    namespace Game
    {
        class AbstractTimer
        {
            public:
                explicit AbstractTimer(float interval);

                void start();

                void start(float interval, bool repeat = false);

                void stop();

                bool enabled() const;

                void setInterval(float interval);

                Event::Handler& tickHandler();

                void think(const float &deltaTime);

            protected:
                Event::Handler _tickHandler;

                bool _enabled = false;
                bool _repeat = false;
                float _interval = 0;
                float _timeTracked = 0;
        };
    }
}
