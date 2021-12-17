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

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Tilemap::Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords)
        {
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GL_CHECK(glGenVertexArrays(1, &_vao));
                GL_CHECK(glBindVertexArray(_vao));
            }

            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(&coords[0], coords.size() * sizeof(glm::vec2));
            _textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(&textureCoords[0], textureCoords.size() * sizeof(glm::vec2));

            if (coords.size()<=0 || textureCoords.size() <=0) return;

            _coordinatesVertexBuffer->bind();

            _shader = ResourceManager::getInstance()->shader("tilemap");

            _uniformTex = _shader->getUniform("tex");
            _uniformFade = _shader->getUniform("fade");
            _uniformMVP = _shader->getUniform("MVP");
            _uniformCnt = _shader->getUniform("cnt");
            _uniformLight = _shader->getUniform("global_light");
            _uniformOffset = _shader->getUniform("offset");

            _attribPos = _shader->getAttrib("Position");
            _attribTex = _shader->getAttrib("TexCoord");

        }

        Tilemap::~Tilemap()
        {
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GL_CHECK(glDeleteVertexArrays(1, &_vao));
            }
        }

        void Tilemap::render(const Point &pos, std::vector<GLuint> indexes, uint32_t atlas)
        {
            if (indexes.size()<=0) return;

            GL_CHECK(_shader->use());

            GL_CHECK(_textures.at(atlas).get()->bind(0));

            GL_CHECK(_shader->setUniform(_uniformTex, 0));

            GL_CHECK(_shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

            // set camera offset
            GL_CHECK(_shader->setUniform(_uniformOffset, glm::vec2((float)pos.x()+1.0, (float)pos.y()+2.0) ));

            GL_CHECK(_shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

            GL_CHECK(_shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters()));

            int lightLevel = 100;
            if (auto state = Game::getInstance()->locationState())
            {
                if ( state->lightLevel() < 0xA000 )
                {
                    lightLevel = (state->lightLevel() - 0x4000) * 100 / 0x6000;

                }
                else if ( state->lightLevel() == 0xA000 )
                {
                    lightLevel = 50;
                }
                else
                {
                    lightLevel = (state->lightLevel() - 0xA000) * 100 / 0x6000;
                }
            }
            GL_CHECK(_shader->setUniform(_uniformLight, lightLevel));

            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GLint curvao;
                glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
                if ((GLuint)curvao != _vao)
                {
                    GL_CHECK(glBindVertexArray(_vao));
                }
            }

            _coordinatesVertexBuffer->bind();
            GL_CHECK(glEnableVertexAttribArray(_attribPos));
            GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

            _textureCoordinatesVertexBuffer->bind();
            GL_CHECK(glEnableVertexAttribArray(_attribTex));
            GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

            IndexBuffer indexBuffer(&indexes[0], indexes.size());

            GL_CHECK(glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indexes.size()), GL_UNSIGNED_INT, 0 ));
        }

        void Tilemap::addTexture(SDL_Surface *surface)
        {
            _textures.push_back(std::make_unique<Texture>(surface->w, surface->h));
            _textures.back().get()->loadFromSurface(surface);
        }
    }
}
