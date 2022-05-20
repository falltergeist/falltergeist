#pragma once

#include <string>
#include "../Graphics/Texture.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Movie
        {
            public:
                Movie();
                ~Movie() = default;
                void render(const Point& point);
                const Size& size() const;
                void loadFromSurface(SDL_Surface* surface);

            private:
                std::unique_ptr<Texture> _texture;
                const Size _size;
        };
    }
}
