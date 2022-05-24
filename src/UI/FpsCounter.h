#pragma once

// Project includes
#include "../UI/TextArea.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace UI
    {
        class FpsCounter final : public TextArea
        {
            public:
                FpsCounter(const Graphics::Point& pos);

                virtual ~FpsCounter() = default;

                void think(const float &deltaTime) override;

                unsigned int frames();

            private:
                float _millisecondsTracked = 0;

                uint32_t _frames = 0;
        };
    }
}
