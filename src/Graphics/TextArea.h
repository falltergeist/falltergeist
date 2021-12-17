#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Graphics/Font.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class TextArea
        {
            public:
                TextArea();
                ~TextArea();

                void render(Point& pos, Graphics::Font* font, SDL_Color _color, SDL_Color _outlineColor);
                void updateBuffers(std::vector<glm::vec2> vertices, std::vector<glm::vec2> UV,  std::vector<unsigned int> indexes);

            protected:
                GLuint _vao;
                std::unique_ptr<VertexBuffer> _coordinatesVertexBuffer;
                std::unique_ptr<VertexBuffer> _textureCoordinatesVertexBuffer;
                std::unique_ptr<IndexBuffer> _indexBuffer;

                GLint _uniformTex;
                GLint _uniformTexSize;
                GLint _uniformFade;
                GLint _uniformMVP;
                GLint _uniformOffset;
                GLint _uniformColor;
                GLint _uniformOutline;

                GLint _attribPos;
                GLint _attribTex;
                Graphics::Shader*_shader;
        };
    }
}
