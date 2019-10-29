#pragma once

#include "../UI/Image.h"

namespace Falltergeist
{
    namespace UI
    {
        /**
         * Hidden mask is used to handle events in particular screen area
         * @todo Must be inherited from UI
         */
        class HiddenMask : public Base//Image
        {
            public:
                HiddenMask(unsigned int width = 0, unsigned int height = 0, int x = 0, int y = 0);
                ~HiddenMask() override;

                void render(bool eggTransparency = false) override;

                virtual bool opaque(const Point &pos) override;

                void think(uint32_t nanosecondsPassed) override;
        };
    }
}
