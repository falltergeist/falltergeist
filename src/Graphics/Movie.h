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
                std::unique_ptr<Texture> _texture;
                unsigned int _width;
                unsigned int _height;
        };
    }
}
