#pragma once

#include <memory>
#include "../Event/Handler.h"

namespace Falltergeist
{
    namespace Game
    {
        class Time;

        class TimerAbstract
        {
            public:
                TimerAbstract(unsigned int interval);

                void start();

                void start(unsigned int interval, bool repeat = false);

                void stop();

                bool enabled() const;

                unsigned int interval() const;

                void setInterval(unsigned int interval);

                bool repeat() const;

                void setRepeat(bool repeat);

                Event::Handler& tickHandler();

                void think();

            protected:
                virtual unsigned int _getTime() = 0;

                Event::Handler _tickHandler;

                bool _enabled = false;
                bool _repeat = false;
                unsigned int _interval;
                unsigned int _lastTick;
        };

        /**
         * @brief Real-time timer.
         * Operates in milliseconds (1000 is one real-time second).
         */
        class Timer : public TimerAbstract
        {
            public:
                Timer(unsigned interval = 1000);

            protected:
                unsigned int _getTime() override;
        };

        /**
         * @brief Game-time timer.
         * Operates in game ticks (10 ticks is one game second).
         * Game second equals to real-time second, but game time is frozen during pause or turn-based mode.
         */
        class GameTimer : public TimerAbstract
        {
            public:
                GameTimer(std::shared_ptr<Time> gameTime, unsigned interval = 1000);

            protected:
                std::shared_ptr<Time> _gameTime;

                unsigned int _getTime() override;
        };
    }
}
