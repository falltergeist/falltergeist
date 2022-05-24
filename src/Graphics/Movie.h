#pragma once

// Project includes
#include "../Graphics/Texture.h"

// Third-party includes

// stdlib
#include <string>

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
