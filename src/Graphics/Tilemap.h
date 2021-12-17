#pragma once

#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/VertexBuffer.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Tilemap
        {
            public:
                Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords);
                ~Tilemap();
                void render(const Point &pos, std::vector<GLuint> indexes, uint32_t atlas);
                void addTexture(SDL_Surface* surface);

            private:
                GLuint _vao;
                std::unique_ptr<VertexBuffer> _coordinatesVertexBuffer;
                std::unique_ptr<VertexBuffer> _textureCoordinatesVertexBuffer;
                std::vector<std::unique_ptr<Texture>> _textures;

                GLint _uniformTex;
                GLint _uniformFade;
                GLint _uniformMVP;
                GLint _uniformCnt;
                GLint _uniformLight;
                GLint _uniformOffset;

                GLint _attribPos;
                GLint _attribTex;
                Graphics::Shader*_shader;
        };
    }
}
