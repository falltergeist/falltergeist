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
                ~Movie();
                void render(int x, int y);
                unsigned int width() const;
                unsigned int height() const;
                void loadFromSurface(SDL_Surface* surface);

            private:
                Texture* _texture;
        };
    }
}
