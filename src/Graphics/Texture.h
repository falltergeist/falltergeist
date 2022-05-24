#pragma once

// Project includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"
#include "../Graphics/Pixels.h"

// Third-party includes
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

// stdlib
#include <memory>
#include <vector>

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture final
        {
            public:
                explicit Texture(const Pixels& pixels);
                ~Texture();

                void bind(uint8_t unit=0) const;
                void unbind(uint8_t unit=0);

                bool opaque(unsigned int x, unsigned int y);
                void setMask(std::vector<bool> mask);

                const Size& size() const;

            private:
                GLuint _textureID = 0;
                Size _size;
                std::vector<bool> _mask;
        };
    }
}
