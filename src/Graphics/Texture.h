#pragma once

#include <memory>
#include <vector>
#include <glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture
        {
            public:
                Texture(unsigned int width, unsigned int height);
                Texture(SDL_Surface* surface);
                ~Texture();

                unsigned int width() const;
                unsigned int height() const;

                unsigned int textureWidth() const;
                unsigned int textureHeight() const;

                void loadFromSurface(SDL_Surface* surface);
                void loadFromRGB(unsigned int* data);
                void loadFromRGBA(unsigned int* data);

                void bind(uint8_t unit=0);
                void unbind(uint8_t unit=0);

                bool opaque(unsigned int x, unsigned int y);
                void setMask(std::vector<bool> mask);

                Size size() const;

            protected:
                GLuint _textureID;
                unsigned int _width = 0;
                unsigned int _height = 0;
                Size _size;

                unsigned int _textureWidth = 0;
                unsigned int _textureHeight = 0;
                std::vector<bool> _mask;
        };
    }
}
