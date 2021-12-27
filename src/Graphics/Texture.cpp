#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Texture.h"
#include "../Graphics/GLCheck.h"
#include <stdexcept>

namespace Falltergeist {
    namespace Graphics {
        Texture::Texture(const Pixels &pixels) : _size(pixels.size()) {
            GL_CHECK(glGenTextures(1, &_textureID));
            GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));

            switch (pixels.format()) {
                case Pixels::Format::RGB:
                    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.width(), _size.height(), 0, GL_BGRA,
                                          GL_UNSIGNED_INT_8_8_8_8, pixels.data()));
                    break;
                case Pixels::Format::RGBA:
                    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _size.width(), _size.height(), 0, GL_RGBA,
                                          GL_UNSIGNED_INT_8_8_8_8, pixels.data()));
                    break;
                default:
                    throw std::logic_error("Unsupported pixels format");
            }
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        }

        Texture::~Texture() {
            if (_textureID > 0) {
                glDeleteTextures(1, &_textureID);
                _textureID = 0;
            }
        }

        const Size &Texture::size() const {
            return _size;
        }

        void Texture::bind(uint8_t unit) const {
            /*    if (unit > GL_MAX_TEXTURE_UNITS)
                {
                    // die horribly
                    return;
                }
            */
            GLint curunit = 0;
            GLint curtexture = 0;

            if (_textureID > 0) {
                GL_CHECK(glGetIntegerv(GL_ACTIVE_TEXTURE, &curunit));
                GL_CHECK(glGetIntegerv(GL_TEXTURE_BINDING_2D, &curtexture));

                if (curunit != GL_TEXTURE0 + unit) {
                    GL_CHECK(glActiveTexture(GL_TEXTURE0 + unit));
                }
                if (curunit != GL_TEXTURE0 + unit || (GLuint) curtexture != _textureID) {
                    GL_CHECK(glBindTexture(GL_TEXTURE_2D, _textureID));
                }
            }
        }

        void Texture::unbind(uint8_t unit) {
            /*    if (unit > GL_MAX_TEXTURE_UNITS)
                {
                    // die horribly
                    return;
                }
            */
            if (_textureID > 0) {
                glActiveTexture(GL_TEXTURE0 + unit);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        bool Texture::opaque(unsigned int x, unsigned int y) {
            if (x >= _size.width() || y >= _size.height() || y * _size.width() + x >= _mask.size()) {
                return false;
            }

            return _mask.at(y * _size.width() + x);
        }

        void Texture::setMask(std::vector<bool> mask) {
            _mask = std::move(mask);
        }
    }
}
