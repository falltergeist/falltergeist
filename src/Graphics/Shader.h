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

#ifndef FALLTERGEIST_GRAPHICS_SHADER_H
#define FALLTERGEIST_GRAPHICS_SHADER_H

// C++ standard includes
#include <map>
#include <string>
#include <vector>

// Falltergeist includes

// Third-party includes
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL.h>

namespace Falltergeist
{
namespace Graphics
{

class Shader
{

public:

    Shader(std::string fname);

    ~Shader();

    void use();

    void unuse();

    GLuint id();


    void setUniform(const std::string &uniform, int i);

    void setUniform(const std::string &uniform, float x);

    void setUniform(const std::string &uniform, float x, float y);

    void setUniform(const std::string &uniform, float x, float y, float z);

    void setUniform(const std::string &uniform, float x, float y, float z, float w);

    void setUniform(const std::string &uniform, const glm::vec2 &vec);

    void setUniform(const std::string &uniform, const glm::vec3 &vec);
    void setUniform(const std::string &uniform, std::vector<GLuint> vec);

    void setUniform(const std::string &uniform, const glm::vec4 &vec);

    void setUniform(const std::string &uniform, const glm::mat4 &mat);

    void setUniform(const GLint &uniform, int i);

    void setUniform(const GLint &uniform, float x);

    void setUniform(const GLint &uniform, float x, float y);

    void setUniform(const GLint &uniform, float x, float y, float z);

    void setUniform(const GLint &uniform, float x, float y, float z, float w);

    void setUniform(const GLint &uniform, const glm::vec2 &vec);

    void setUniform(const GLint &uniform, const glm::vec3 &vec);
    void setUniform(const GLint &uniform, std::vector<GLuint> vec);

    void setUniform(const GLint &uniform, const glm::vec4 &vec);

    void setUniform(const GLint &uniform, const glm::mat4 &mat);

    GLint getAttrib(const std::string &attrib) const;

    GLint getUniform(const std::string &uniform) const;

private:
    GLuint _progId;
    GLuint _loadShader(const char *, unsigned int);

    std::vector<GLuint> _shaders;

    bool _load(std::string fname);
    mutable std::map<std::string, GLint> _uniforms;
    mutable std::map<std::string, GLint> _attribs;

};

}
}
#endif //FALLTERGEIST_GRAPHICS_SHADER_H
