#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Graphics/Color.h"
#include "../Graphics/Font.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Shader.h"

namespace Falltergeist::Graphics {
    class TextArea final {
    public:
        TextArea();

        ~TextArea();

        void render(Point& pos, Graphics::Font* font, const Graphics::Color &color, const Graphics::Color &outlineColor);

        void updateBuffers(std::vector<glm::vec2> vertices, std::vector<glm::vec2> UV,  std::vector<unsigned int> indexes);

    protected:
        std::unique_ptr<VertexArray> _vertexArray;

        std::unique_ptr<VertexBuffer> _coordinatesVertexBuffer;

        std::unique_ptr<VertexBuffer> _textureCoordinatesVertexBuffer;

        std::unique_ptr<IndexBuffer> _indexBuffer;

        Graphics::Shader*_shader;

        GLint _uniformTex;

        GLint _uniformTexSize;

        GLint _uniformFade;

        GLint _uniformMVP;

        GLint _uniformOffset;

        GLint _uniformColor;

        GLint _uniformOutline;

        GLint _attribPos;

        GLint _attribTex;
    };
}
