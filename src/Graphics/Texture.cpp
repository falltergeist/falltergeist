#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GLCheck.h"

namespace Falltergeist
{
    namespace Graphics
    {
        int NearestPowerOf2(int n)
        {
            if (!n) return n; //(0 == 2^0)
            int x = 1;
            while (x < n)
            {
                x <<= 1;
            }
            return x;
        }

        Texture::Texture(std::unique_ptr<RgbaPixels>& pixels, unsigned int width, unsigned int height)
        : _pixels(std::move(pixels)), _width(width), _height(height) {
            GL_CHECK(glGenTextures(1, &_textureID));
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, _pixels->data()));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        }

        Texture::Texture(unsigned int width, unsigned int height) : _size(width, height)
        {
            _width = width;
            _height = height;

            glGenTextures(1, &_textureID);
        }

        Texture::Texture(SDL_Surface* surface): _size(surface->w, surface->h)
        {
            _width = surface->w;
            _height = surface->h;
            glGenTextures(1, &_textureID);
            loadFromSurface(surface);
        }

        Texture::~Texture()
        {
            if (_textureID > 0)
            {
                glDeleteTextures(1, &_textureID);
                _textureID = 0;
            }
        }

        unsigned int Texture::width() const
        {
            return _width;
        }

        unsigned int Texture::height() const
        {
            return _height;
        }

        Size Texture::size() const
        {
            return _size;
        }

        void Texture::loadFromSurface(SDL_Surface* surface)
        {
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, surface->pixels));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

            _width = surface->w;
            _height = surface->h;
        }

        void Texture::loadFromRGBA(unsigned int* data)
        {
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
            GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_ABGR_EXT, GL_UNSIGNED_BYTE, data));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        }

        void Texture::bind(uint8_t unit)
        {
        /*    if (unit > GL_MAX_TEXTURE_UNITS)
            {
                // die horribly
                return;
            }
        */
            GLint curunit;
            GLint curtexture;

            if (_textureID > 0)
            {
                GL_CHECK(glGetIntegerv(GL_ACTIVE_TEXTURE, &curunit));
                GL_CHECK(glGetIntegerv(GL_TEXTURE_BINDING_2D, &curtexture));

                if (curunit != GL_TEXTURE0 + unit)
                {
                    GL_CHECK(glActiveTexture(GL_TEXTURE0 + unit));
                }
                if (curunit != GL_TEXTURE0 + unit || (GLuint)curtexture != _textureID)
                {
                    GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
                }
            }
        }

        void Texture::unbind(uint8_t unit)
        {
        /*    if (unit > GL_MAX_TEXTURE_UNITS)
            {
                // die horribly
                return;
            }
        */
            if (_textureID > 0)
            {
                glActiveTexture(GL_TEXTURE0+unit);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        bool Texture::opaque(unsigned int x, unsigned int y)
        {
            if (x >= width() || y >= height() || y*width() + x >= _mask.size()) {
                return false;
            }

            return _mask.at(y * width() + x);
        }

        void Texture::setMask(std::vector<bool> mask)
        {
            _mask = mask;
        }
    }
}
