#pragma once

#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace UI
    {
        class FpsCounter final : public TextArea
        {
            public:
                FpsCounter(const Point& pos);
                virtual ~FpsCounter() = default;

                void think(const float &deltaTime) override;
                unsigned int frames();

            private:
                float _millisecondsTracked = 0;
                uint32_t _frames = 0;
        };
    }
}
