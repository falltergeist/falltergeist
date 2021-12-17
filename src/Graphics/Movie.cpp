#include "../Game/Game.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/Movie.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../ResourceManager.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexArray.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Movie::Movie()
        {
            _texture = std::make_unique<Graphics::Texture>(640,320);
        }

        Movie::~Movie()
        {
        }

        unsigned int Movie::width() const
        {
            return _texture->width();
        }

        unsigned int Movie::height() const
        {
            return _texture->height();
        }

        void Movie::loadFromSurface(SDL_Surface* surface)
        {
            _texture->loadFromSurface(surface);
        }

        void Movie::render(int x, int y)
        {
            std::vector<glm::vec2> vertices;
            std::vector<glm::vec2> UV;

            int width = 640;
            int height = 320;

            glm::vec2 vertex_up_left    = glm::vec2( (float)x, (float)y);
            glm::vec2 vertex_up_right   = glm::vec2( (float)(x+width), (float)y);
            glm::vec2 vertex_down_right = glm::vec2( (float)(x+width), (float)(y+height));
            glm::vec2 vertex_down_left  = glm::vec2( (float)x, (float)(y+height));

            vertices.push_back(vertex_up_left   );
            vertices.push_back(vertex_down_left );
            vertices.push_back(vertex_up_right  );
            vertices.push_back(vertex_down_right);

            glm::vec2 uv_up_left    = glm::vec2( 0.0, 0.0 );
            glm::vec2 uv_up_right   = glm::vec2( (float)_texture->width()/(float)_texture->textureWidth(), 0.0 );
            glm::vec2 uv_down_right = glm::vec2( (float)_texture->width()/(float)_texture->textureWidth(), (float)_texture->height()/(float)_texture->textureHeight() );
            glm::vec2 uv_down_left  = glm::vec2( 0.0, (float)_texture->height()/(float)_texture->textureHeight() );

            UV.push_back(uv_up_left   );
            UV.push_back(uv_down_left );
            UV.push_back(uv_up_right  );
            UV.push_back(uv_down_right);

            // TODO: different shader

            auto spriteShader = ResourceManager::getInstance()->shader("sprite");
            spriteShader->use();

            _texture->bind(0);

            spriteShader->setUniform("tex",0);
            spriteShader->setUniform("fade",Game::getInstance()->renderer()->fadeColor());
            spriteShader->setUniform("MVP", Game::getInstance()->renderer()->getMVP());

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    vertices.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                    (unsigned int) spriteShader->getAttrib("Position"),
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            });
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &UV[0],
                    UV.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({
                    (unsigned int) spriteShader->getAttrib("TexCoord"),
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            });
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = { 0, 1, 2, 3, 2, 1 };
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }
    }
}
