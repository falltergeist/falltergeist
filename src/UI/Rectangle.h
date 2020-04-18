#pragma once

#include <SDL.h>
#include "../Graphics/Point.h"
#include "../UI/Base.h"

namespace Falltergeist
{
    namespace UI
    {
        class Rectangle final : public Base
        {
            public:
                Rectangle(Point pos, Size size, SDL_Color color);
                void render(bool eggTransparency = false) override;

                bool opaque(unsigned int x, unsigned int y);
                bool opaque(const Point &pos) override;

                Size size() const override;

            private:
                Size _size;
                SDL_Color _color;
        };
    }
}
