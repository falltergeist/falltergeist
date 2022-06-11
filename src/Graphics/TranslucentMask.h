#pragma once

// Project includes
#include "Texture.h"

// Third-party includes
#include <GL/glew.h>
#include <glm/vec4.hpp>

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        class Shader;
        class Color;

        class TranslucentMask
        {
            public:
                TranslucentMask(const std::string& filename);

                void setColor(Color color);

                const Size& size() const;

                void render(const Point& point) const;

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
