#include "../Game/Game.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/Lightmap.h"
#include "../ResourceManager.h"
#include "../State/Location.h"
#include <stdexcept>

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Lightmap::Lightmap(std::vector<glm::vec2> coords, std::vector<GLuint> indexes)
        {
            if (coords.empty() ) {
                throw std::logic_error("Coordinates should not be empty");
            }
            if (indexes.empty()) {
                throw std::logic_error("Indexes should not be empty");
            }

            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GL_CHECK(glGenVertexArrays(1, &_vao));
                GL_CHECK(glBindVertexArray(_vao));
            }

            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &coords[0],
                    coords.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::StaticDraw
            );

            _lightsVertexBuffer = std::make_unique<VertexBuffer>(nullptr, 0);

            _indexBuffer = std::make_unique<IndexBuffer>(
                &indexes[0],
                indexes.size(),
                IndexBuffer::UsagePattern::DynamicDraw
            );

            _shader = ResourceManager::getInstance()->shader("lightmap");

            _uniformFade = _shader->getUniform("fade");
            _uniformMVP = _shader->getUniform("MVP");
            _uniformOffset = _shader->getUniform("offset");

            _attribPos = _shader->getAttrib("Position");
            _attribLights = _shader->getAttrib("lights");
        }

        Lightmap::~Lightmap()
        {
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GL_CHECK(glDeleteVertexArrays(1, &_vao));
            }
        }

        void Lightmap::render(const Point &pos)
        {
            GL_CHECK(glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR));

            _shader->use();

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());

            // set camera offset
            _shader->setUniform(_uniformOffset, glm::vec2((float)pos.x(), (float)pos.y()));

            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());

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

            _lightsVertexBuffer->bind();
            GL_CHECK(glEnableVertexAttribArray(_attribLights));
            GL_CHECK(glVertexAttribPointer(_attribLights, 1, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

            _indexBuffer->bind();

            GL_CHECK(glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, nullptr));
            GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        }

        void Lightmap::update(std::vector<float> lights)
        {
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GLint curvao;
                glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
                if ((GLuint)curvao != _vao)
                {
                    GL_CHECK(glBindVertexArray(_vao));
                }
            }

            _lightsVertexBuffer = std::make_unique<VertexBuffer>(
                &lights[0],
                lights.size() * sizeof(float),
                VertexBuffer::UsagePattern::StaticDraw
            );
        }
    }
}
