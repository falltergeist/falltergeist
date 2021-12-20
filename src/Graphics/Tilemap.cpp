#include <memory>
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Tilemap.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

namespace Falltergeist {
    namespace Graphics {
        using Game::Game;

        Tilemap::Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords) {
            if (coords.empty()) {
                throw std::logic_error("Coordinates should not be empty");
            }
            if (textureCoords.empty()) {
                throw std::logic_error("Texture coordinates should not be empty");
            }

            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(&coords[0], coords.size() * sizeof(glm::vec2));
            _textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(&textureCoords[0], textureCoords.size() * sizeof(glm::vec2));
            _vertexArray = std::make_unique<VertexArray>();

            _shader = ResourceManager::getInstance()->shader("tilemap");

            _uniformTex = _shader->getUniform("tex");
            _uniformFade = _shader->getUniform("fade");
            _uniformMVP = _shader->getUniform("MVP");
            _uniformCnt = _shader->getUniform("cnt");
            _uniformLight = _shader->getUniform("global_light");
            _uniformOffset = _shader->getUniform("offset");

            _attribPos = _shader->getAttrib("Position");
            _attribTex = _shader->getAttrib("TexCoord");

            VertexBufferAttribute coordinatesAttribute(
                    (unsigned int) _attribPos,
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            );
            VertexBufferLayout coordinatesBufferLayout;
            coordinatesBufferLayout.addAttribute(coordinatesAttribute);
            _vertexArray->addBuffer(_coordinatesVertexBuffer, coordinatesBufferLayout);

            VertexBufferAttribute textureCoordinatesAttribute(
                    (unsigned int) _attribTex,
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            );
            VertexBufferLayout textureCoordinatesBufferLayout;
            textureCoordinatesBufferLayout.addAttribute(textureCoordinatesAttribute);
            _vertexArray->addBuffer(_textureCoordinatesVertexBuffer, textureCoordinatesBufferLayout);
        }

        Tilemap::~Tilemap() {
        }

        void Tilemap::render(const Point &pos, std::vector<GLuint> indexes, uint32_t atlas) {
            if (indexes.empty()) {
                throw std::logic_error("Indexes should not be empty");
            };

            _shader->use();

            _textures.at(atlas).get()->bind(0);

            _shader->setUniform(_uniformTex, 0);

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());

            // set camera offset
            _shader->setUniform(_uniformOffset, glm::vec2((float) pos.x() + 1.0, (float) pos.y() + 2.0));

            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());

            _shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters());

            int lightLevel = 100;
            if (auto state = Game::getInstance()->locationState()) {
                if (state->lightLevel() < 0xA000) {
                    lightLevel = (state->lightLevel() - 0x4000) * 100 / 0x6000;

                } else if (state->lightLevel() == 0xA000) {
                    lightLevel = 50;
                } else {
                    lightLevel = (state->lightLevel() - 0xA000) * 100 / 0x6000;
                }
            }
            _shader->setUniform(_uniformLight, lightLevel);

            _vertexArray->bind();

            IndexBuffer indexBuffer(&indexes[0], indexes.size(), IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, nullptr));
        }

        void Tilemap::addTexture(SDL_Surface *surface) {
            _textures.push_back(std::make_unique<Texture>(
                Pixels(
                    surface->pixels,
                    Size(surface->w, surface->h),
                    Pixels::Format::RGBA
                )
            ));
        }
    }
}
