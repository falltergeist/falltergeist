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

#ifndef FALLTERGEIST_GRAPHICS_LIGHTMAP_H
#define FALLTERGEIST_GRAPHICS_LIGHTMAP_H

// C++ standard includes

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"

// Third party includes

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
    GLuint _coords;
    GLuint _lights;
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
#endif //FALLTERGEIST_GRAPHICS_LIGHTMAP_H
