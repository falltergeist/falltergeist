#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/VertexArray.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Lightmap
        {
            public:
                Lightmap(std::vector<glm::vec2> coords, std::vector<GLuint> indexes);
                ~Lightmap();
                void render(const Point &pos);
                void update(std::vector<float> lights);

            private:
                std::unique_ptr<VertexArray> _vertexArray;
                std::unique_ptr<VertexBuffer> _coordinatesVertexBuffer;
                std::unique_ptr<VertexBuffer> _lightsVertexBuffer;
                std::unique_ptr<IndexBuffer> _indexBuffer;

                GLint _uniformFade;
                GLint _uniformMVP;
                GLint _uniformOffset;

                GLint _attribPos;
                GLint _attribLights;
                Graphics::Shader*_shader;
        };
    }
}
