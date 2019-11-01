#pragma once

#include "../Event/Handler.h"

namespace Falltergeist
{
    namespace Game
    {
        class AbstractTimer
        {
            public:
                AbstractTimer(unsigned int interval);

                void start();

                void start(unsigned int interval, bool repeat = false);

                void stop();

                bool enabled() const;

                unsigned int interval() const;

                void setInterval(unsigned int interval);

                bool repeat() const;

                void setRepeat(bool repeat);

                Event::Handler& tickHandler();

                void think(uint32_t nanosecondsPassed);

            protected:
                virtual unsigned int _getTime() = 0;

                Event::Handler _tickHandler;

                bool _enabled = false;
                bool _repeat = false;
                unsigned int _interval;
                unsigned int _lastTick;
        };
    }
}
