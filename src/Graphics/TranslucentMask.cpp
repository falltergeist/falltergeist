// Project includes
#include "TranslucentMask.h"
#include "GLCheck.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "../Game/Game.h"
#include "../ResourceManager.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        TranslucentMask::TranslucentMask(const std::string& filename)
        {
            _texture = ResourceManager::getInstance()->texture(filename);
            _shader = ResourceManager::getInstance()->shader("translucentmask");

            _uniformTex = _shader->getUniform("tex");
            _uniformCol = _shader->getUniform("col");

            _attribPos = _shader->getAttrib("Position");
            _attribTex = _shader->getAttrib("TexCoord");
        }

        void TranslucentMask::setColor(const float r, const float g, const float b, const float a)
        {
            _color = glm::vec4(r, g, b, a);
        }

        void TranslucentMask::render(const Point& point)
        {
            Rectangle& rectangle = Rectangle(point, _texture->size());

            glm::vec2 vertices[4] = {glm::vec2((float)rectangle.position().x(), (float)rectangle.position().y()),
                                     glm::vec2((float)rectangle.position().x(), (float)(rectangle.position().y() + rectangle.size().height())),
                                     glm::vec2((float)(rectangle.position().x() + rectangle.size().width()), (float)rectangle.position().y()),
                                     glm::vec2((float)(rectangle.position().x() + rectangle.size().width()),
                                               (float)(rectangle.position().y() + rectangle.size().height()))};
            glm::vec2 UV[4] = {glm::vec2(0.0, 0.0), glm::vec2(0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec2(1.0, 1.0)};

            _shader->use();
            _shader->setUniform(_uniformCol, _color);
            _texture->bind(0);
            _shader->setUniform(_uniformTex, 0);
            _shader->setUniform("MVP", Game::getInstance()->renderer()->getMVP());

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], sizeof(vertices), VertexBuffer::UsagePattern::DynamicDraw);

            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({(unsigned int)_attribPos, 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&UV[0], sizeof(UV), VertexBuffer::UsagePattern::DynamicDraw);
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({(unsigned int)_attribTex, 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }
    }
}
