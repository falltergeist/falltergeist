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

// Related headers
#include "Shader.h"

// C++ standard includes
#include <fstream>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../Exception.h"
#include "../Logger.h"
#include "../Game/Game.h"
#include "Renderer.h"

// Third-party includes
#include <glm/gtc/type_ptr.hpp>


namespace Falltergeist {
    namespace Graphics {

        Shader::Shader(std::string fname) {
            _load(fname);
        }

        Shader::~Shader() {
            for (auto it = _shaders.begin(); it != _shaders.end(); ++it) {
                glDetachShader(_progId, *it);
            }

            for (auto it = _shaders.begin(); it != _shaders.end(); ++it) {
                glDeleteShader(*it);
            }

            if (_progId) {
                glDeleteProgram(_progId);
            }
        }

        GLuint Shader::_loadShader(const char *src, unsigned int type) {
            GLuint shader = glCreateShader(type);

            glShaderSource(shader, 1, &src, NULL);
            glCompileShader(shader);

            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (!status) {
                GLint len;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
                GLchar *log = (GLchar *) malloc(len);
                glGetShaderInfoLog(shader, len, NULL, log);
                Logger::error("RENDERER") << "Failed to compile shader: '" << log << std::endl;
                free(log);
                shader = 0;
                throw Exception("Failed to compile shader.");
            }
            return shader;
        }


        bool Shader::_load(std::string fname) {
            _progId = 0;

            std::string rpath = "21/";
            switch (Game::getInstance()->renderer()->renderPath())
            {
                case Renderer::RenderPath::OGL21:
                    rpath = "21/";
                    break;
                case Renderer::RenderPath::OGL32 :
                    rpath = "32/";
                    break;
                default:
                    break;
            }
            // TODO: use resource manager
            std::string fprog = std::string(CrossPlatform::findFalltergeistDataPath() + "/data/shaders/" +rpath +fname+".fp");
            std::string vprog = std::string(CrossPlatform::findFalltergeistDataPath() + "/data/shaders/" +rpath +fname+".vp");

            Logger::info("RENDERER") << "Loading shader " << fprog << std::endl;
            Logger::info("RENDERER") << "Loading shader " << vprog << std::endl;

            std::ifstream fpfile(fprog);
            std::ifstream vpfile(vprog);

            if (!fpfile.is_open())
            {
                throw Exception("Can't open shader source "+fprog);
            }
            if (!vpfile.is_open())
            {
                throw Exception("Can't open shader source "+vprog);
            }

            std::string fpsrc;
            std::string vpsrc;

            fpfile.seekg(0, std::ios::end);
            fpsrc.reserve(fpfile.tellg());
            fpfile.seekg(0, std::ios::beg);

            fpsrc.assign((std::istreambuf_iterator<char>(fpfile)),
                       std::istreambuf_iterator<char>());
            fpfile.close();

            vpfile.seekg(0, std::ios::end);
            vpsrc.reserve(vpfile.tellg());
            vpfile.seekg(0, std::ios::beg);

            vpsrc.assign((std::istreambuf_iterator<char>(vpfile)),
                         std::istreambuf_iterator<char>());
            vpfile.close();


            _shaders.push_back( _loadShader(fpsrc.c_str(), GL_FRAGMENT_SHADER) );
            _shaders.push_back( _loadShader(vpsrc.c_str(), GL_VERTEX_SHADER) );

            _progId = glCreateProgram();

                //attach
                for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                    glAttachShader(_progId, *it);
                glLinkProgram(_progId);

                GLint status;
                glGetProgramiv(_progId, GL_LINK_STATUS, &status);

                if (!status) {
                    GLint len;
                    glGetProgramiv(_progId, GL_INFO_LOG_LENGTH, &len);
                    GLchar *log = (GLchar *) malloc(len);
                    glGetProgramInfoLog(_progId, len, NULL, log);
                    Logger::error("RENDERER") << "Can't link program " << fname << ": " << log << std::endl;
                    free(log);
                    for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                        glDetachShader(_progId, *it);

                    for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                        glDeleteShader(*it);
                    glDeleteProgram(_progId);
                    _progId = 0;
                    throw Exception("Failed to link shader");
                    return false;
                }
            return true;
        }

        void Shader::use() {
            GLint cur;
            glGetIntegerv(GL_CURRENT_PROGRAM, &cur);
            if ((GLuint)cur!=_progId)
            {
                glUseProgram(_progId);
            }
        }

        void Shader::unuse() {
            glUseProgram(0);
        }

        GLuint Shader::id() {
            return _progId;
        }

        GLint Shader::getUniform(const std::string &uniform) const {
            if (!_uniforms.count(uniform)) {
                GLint loc = glGetUniformLocation(_progId, uniform.c_str());
                if (loc == -1)
                    Logger::warning("RENDERER") << "Attention: uniform '" << uniform << "' does not exist in " << _progId << std::endl;

                _uniforms[uniform] = loc;
                return loc;
            }
            else return _uniforms.at(uniform);
        }

        GLint Shader::getAttrib(const std::string &attrib) const {
            if (!_attribs.count(attrib)) {
                GLint loc = glGetAttribLocation(_progId, attrib.c_str());
                if (loc == -1)
                    Logger::warning("RENDERER") << "Attention: attrib '" << attrib << "' does not exist in " << _progId << std::endl;


                _attribs[attrib] = loc;
                return loc;
            }
            else return _attribs.at(attrib);
        }

        void Shader::setUniform(const std::string &uniform, int i) {
            glUniform1i(getUniform(uniform), i);
        }

        void Shader::setUniform(const std::string &uniform, float x) {
            glUniform1f(getUniform(uniform), x);
        }

        void Shader::setUniform(const std::string &uniform, float x, float y) {
            glUniform2f(getUniform(uniform), x, y);
        }

        void Shader::setUniform(const std::string &uniform, float x, float y, float z) {
            glUniform3f(getUniform(uniform), x, y, z);
        }

        void Shader::setUniform(const std::string &uniform, float x, float y, float z, float w) {
            glUniform4f(getUniform(uniform), x, y, z, w);
        }

        void Shader::setUniform(const std::string &uniform, const glm::vec2 &vec) {
            glUniform2fv(getUniform(uniform), 1, glm::value_ptr(vec));
        }


        void Shader::setUniform(const std::string &uniform, const glm::vec3 &vec) {
            glUniform3fv(getUniform(uniform), 1, glm::value_ptr(vec));
        }

        void Shader::setUniform(const std::string &uniform, std::vector<GLuint> vec) {
            glUniform1iv(getUniform(uniform), vec.size(), (const int*)&vec[0]);
        }

        void Shader::setUniform(const std::string &uniform, const glm::vec4 &vec) {
            glUniform4fv(getUniform(uniform), 1, glm::value_ptr(vec));
        }

        void Shader::setUniform(const std::string &uniform, const glm::mat4 &mat) {
            glUniformMatrix4fv(getUniform(uniform), 1, GL_FALSE, glm::value_ptr(mat));
        }

    void Shader::setUniform(const GLint &uniform, int i) {
        glUniform1i((uniform), i);
    }

    void Shader::setUniform(const GLint &uniform, float x) {
        glUniform1f((uniform), x);
    }

    void Shader::setUniform(const GLint &uniform, float x, float y) {
        glUniform2f((uniform), x, y);
    }

    void Shader::setUniform(const GLint &uniform, float x, float y, float z) {
        glUniform3f((uniform), x, y, z);
    }

    void Shader::setUniform(const GLint &uniform, float x, float y, float z, float w) {
        glUniform4f((uniform), x, y, z, w);
    }

    void Shader::setUniform(const GLint &uniform, const glm::vec2 &vec) {
        glUniform2fv((uniform), 1, glm::value_ptr(vec));
    }


    void Shader::setUniform(const GLint &uniform, const glm::vec3 &vec) {
        glUniform3fv((uniform), 1, glm::value_ptr(vec));
    }

    void Shader::setUniform(const GLint &uniform, std::vector<GLuint> vec) {
        glUniform1iv((uniform), vec.size(), (const int*)&vec[0]);
    }

    void Shader::setUniform(const GLint &uniform, const glm::vec4 &vec) {
        glUniform4fv((uniform), 1, glm::value_ptr(vec));
    }

    void Shader::setUniform(const GLint &uniform, const glm::mat4 &mat) {
        glUniformMatrix4fv((uniform), 1, GL_FALSE, glm::value_ptr(mat));
    }


    }
}