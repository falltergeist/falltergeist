#pragma once

#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace UI
    {
        class FpsCounter : public TextArea
        {
            public:
                FpsCounter(const Point& pos = Point(598, 2));
                FpsCounter(int x, int y);
                ~FpsCounter() override;

                void think(uint32_t nanosecondsPassed) override;
                unsigned int frames();

            protected:
                uint32_t _nanosecondsTracked = 0;
                uint32_t _frames = 0;
        };
    }
}
