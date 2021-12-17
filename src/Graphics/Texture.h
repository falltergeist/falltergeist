#pragma once

#include <memory>
#include <vector>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture final
        {
            public:
                typedef std::vector<uint32_t> RgbaPixels;

                Texture(std::unique_ptr<RgbaPixels>& pixels, unsigned int width, unsigned int height);
                Texture(unsigned int width, unsigned int height);
                Texture(SDL_Surface* surface);
                ~Texture();

                unsigned int width() const;
                unsigned int height() const;

                void loadFromSurface(SDL_Surface* surface);
                void loadFromRGBA(unsigned int* data);

                void bind(uint8_t unit=0);
                void unbind(uint8_t unit=0);

                bool opaque(unsigned int x, unsigned int y);
                void setMask(std::vector<bool> mask);

                Size size() const;

            private:
                std::unique_ptr<RgbaPixels> _pixels;
                GLuint _textureID = 0;
                unsigned int _width = 0;
                unsigned int _height = 0;
                Size _size;

                std::vector<bool> _mask;
        };
    }
}
