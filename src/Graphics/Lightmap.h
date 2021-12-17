#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/VertexBuffer.h"

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
                GLuint _vao;
                std::unique_ptr<VertexBuffer> _coordinatesVertexBuffer;
                std::unique_ptr<VertexBuffer> _lightsVertexBuffer;
                GLuint _ebo;

                GLint _uniformFade;
                GLint _uniformMVP;
                GLint _uniformOffset;

                GLint _attribPos;
                GLint _attribLights;
                unsigned int _indexes;
                Graphics::Shader*_shader;
        };
    }
}
