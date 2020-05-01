#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Graphics/Font.h"
#include "../Graphics/Renderer.h"
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
                void updateBuffers(std::vector<glm::vec2> vertices, std::vector<glm::vec2> UV,  std::vector<GLushort> indexes);

            protected:
                GLuint _vao;
                GLuint _coords;
                GLuint _texCoords;
                GLuint _ebo;
                int _cnt = 0;

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
