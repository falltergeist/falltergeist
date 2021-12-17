#include <algorithm>
#include <SDL.h>
#include "../CrossPlatform.h"
#include "../Event/Mouse.h"
#include "../Game/Game.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/TextArea.h"
#include "../ResourceManager.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        TextArea::TextArea()
        {
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GL_CHECK(glGenVertexArrays(1, &_vao));
                GL_CHECK(glBindVertexArray(_vao));
            }

            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(nullptr, 0);
            _textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(nullptr, 0);
            _indexBuffer = std::make_unique<IndexBuffer>(nullptr, 0);

            _shader = ResourceManager::getInstance()->shader("font");

            _uniformTex = _shader->getUniform("tex");
            if (Game::getInstance()->renderer()->renderPath() == Graphics::Renderer::RenderPath::OGL21)
            {
                _uniformTexSize = _shader->getUniform("texSize");
            }
            _uniformFade = _shader->getUniform("fade");
            _uniformMVP = _shader->getUniform("MVP");
            _uniformOffset = _shader->getUniform("offset");
            _uniformColor = _shader->getUniform("color");
            _uniformOutline = _shader->getUniform("outlineColor");

            _attribPos = _shader->getAttrib("Position");
            _attribTex = _shader->getAttrib("TexCoord");
        }

        TextArea::~TextArea()
        {
        }


        void TextArea::render(Point& pos, Graphics::Font* font, SDL_Color _color, SDL_Color _outlineColor)
        {
            if (_indexBuffer->count() == 0) {
                return;
            }

            _shader->use();

            font->texture()->bind(0);

            _shader->setUniform(_uniformTex, 0);

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());
            _shader->setUniform(_uniformOffset, glm::vec2((float)pos.x(), (float(pos.y()))));
            _shader->setUniform(_uniformColor, glm::vec4((float)_color.r / 255.f, (float)_color.g / 255.f, (float)_color.b / 255.f, (float)_color.a / 255.f));
            _shader->setUniform(_uniformOutline, glm::vec4((float)_outlineColor.r / 255.f, (float)_outlineColor.g / 255.f, (float)_outlineColor.b / 255.f, (float)_outlineColor.a / 255.f));
            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());
            if (Game::getInstance()->renderer()->renderPath() == Graphics::Renderer::RenderPath::OGL21)
            {
                _shader->setUniform(_uniformTexSize, glm::vec2((float)font->texture()->textureWidth(), (float)font->texture()->textureHeight()));
            }

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
            GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

            _textureCoordinatesVertexBuffer->bind();
            GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

            _indexBuffer->bind();

            GL_CHECK(glEnableVertexAttribArray(_attribPos));
            GL_CHECK(glEnableVertexAttribArray(_attribTex));

            GL_CHECK(glDrawElements(GL_TRIANGLES, _indexBuffer->count(), GL_UNSIGNED_INT, nullptr));

            GL_CHECK(glDisableVertexAttribArray(_attribPos));
            GL_CHECK(glDisableVertexAttribArray(_attribTex));
        }

        void TextArea::updateBuffers(std::vector<glm::vec2> vertices, std::vector<glm::vec2> UV,  std::vector<unsigned int> indexes)
        {
            if (vertices.empty())
            {
                return;
            }

            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
            {
                GLint curvao;
                glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
                if ((GLuint)curvao != _vao)
                {
                    GL_CHECK(glBindVertexArray(_vao));
                }
            }

            // TODO pass GL_DYNAMIC_DRAW
            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(glm::vec2));
            // TODO pass GL_DYNAMIC_DRAW
            _textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(&UV[0], UV.size() * sizeof(glm::vec2));

            // TODO pass GL_DYNAMIC_DRAW
            _indexBuffer = std::make_unique<IndexBuffer>(&indexes[0], indexes.size());
        }
    }
}
