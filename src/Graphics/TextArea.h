/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_GRAPHICS_TEXTAREA_H
#define FALLTERGEIST_GRAPHICS_TEXTAREA_H

// C++ standard includes
#include <cstdint>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Graphics/Font.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"

// Third party includes

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
#endif // FALLTERGEIST_GRAPHICS_TEXTAREA_H
