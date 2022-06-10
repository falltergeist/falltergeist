#pragma once

// Project includes
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        class TranslucentMask
        {
            public:
                TranslucentMask(const std::string& filename);

                void setColor(float r, float g, float b, float a);

                void render(const Point& point);

            private:
                GLint _uniformTex;

                GLint _uniformCol;

                GLint _attribPos;

                GLint _attribTex;

                Texture* _texture;

                glm::vec4 _color;

                Shader* _shader;
        };
    }
}
