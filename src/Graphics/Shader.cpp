// Project includes
#include "../CrossPlatform.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/Shader.h"
#include "../Graphics/ShaderFile.h"
#include "../Logger.h"

// Third-party includes
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

// stdlib

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Shader::Shader(const std::string& fname)
        {
            _load(fname);
        }

        Shader::~Shader()
        {
            for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
            {
                glDetachShader(_progId, *it);
            }

            for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
            {
                glDeleteShader(*it);
            }

            if (_progId)
            {
                glDeleteProgram(_progId);
            }
        }

        GLuint Shader::_loadShader(const char *src, unsigned int type)
        {
            GLuint shader = glCreateShader(type);

            glShaderSource(shader, 1, &src, NULL);
            glCompileShader(shader);

            GLint status = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (!status)
            {
                GLint len = 0;
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

        bool Shader::_load(const std::string& fname)
        {
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

            std::string pathToFile = "data/shaders/" + rpath + fname + ".shader";
            Logger::info("RENDERER") << "Loading shader " << pathToFile << std::endl;
            ShaderFile shaderFile(pathToFile);

            _shaders.push_back( _loadShader(shaderFile.fragmentSection().c_str(), GL_FRAGMENT_SHADER) );
            _shaders.push_back( _loadShader(shaderFile.vertexSection().c_str(), GL_VERTEX_SHADER) );

            _progId = glCreateProgram();

                //attach
                for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                {
                    glAttachShader(_progId, *it);
                }
                glLinkProgram(_progId);

                GLint status = 0;
                glGetProgramiv(_progId, GL_LINK_STATUS, &status);

                if (!status)
                {
                    GLint len = 0;
                    glGetProgramiv(_progId, GL_INFO_LOG_LENGTH, &len);
                    GLchar *log = (GLchar *) malloc(len);
                    glGetProgramInfoLog(_progId, len, NULL, log);
                    Logger::error("RENDERER") << "Can't link program " << fname << ": " << log << std::endl;
                    free(log);
                    for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                    {
                        glDetachShader(_progId, *it);
                    }

                    for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
                    {
                        glDeleteShader(*it);
                    }
                    glDeleteProgram(_progId);
                    _progId = 0;
                    throw Exception("Failed to link shader");
                    return false;
                }
            return true;
        }

        void Shader::use() const
        {
            GLint cur = 0;
            GL_CHECK(glGetIntegerv(GL_CURRENT_PROGRAM, &cur));
            if ((GLuint)cur!=_progId)
            {
                GL_CHECK(glUseProgram(_progId));
            }
        }

        void Shader::unuse()
        {
            glUseProgram(0);
        }

        GLint Shader::getUniform(const std::string &uniform) const
        {
            if (!_uniforms.count(uniform))
            {
                GLint loc = glGetUniformLocation(_progId, uniform.c_str());
                if (loc == -1)
                {
                    Logger::warning("RENDERER") << "Attention: uniform '" << uniform << "' does not exist in " << _progId << std::endl;
                }

                _uniforms[uniform] = loc;
                return loc;
            }
            else
            {
                return _uniforms.at(uniform);
            }
        }

        GLint Shader::getAttrib(const std::string &attrib) const
        {
            if (!_attribs.count(attrib))
            {
                GLint loc = glGetAttribLocation(_progId, attrib.c_str());
                if (loc == -1)
                {
                    Logger::warning("RENDERER") << "Attention: attrib '" << attrib << "' does not exist in " << _progId << std::endl;
                }

                _attribs[attrib] = loc;
                return loc;
            }
            else {
                return _attribs.at(attrib);
            }
        }

        void Shader::setUniform(const std::string &uniform, int i)
        {
            GL_CHECK(glUniform1i(getUniform(uniform), i));
        }

        void Shader::setUniform(const std::string &uniform, float x)
        {
            GL_CHECK(glUniform1f(getUniform(uniform), x));
        }

        void Shader::setUniform(const std::string &uniform, float x, float y)
        {
            GL_CHECK(glUniform2f(getUniform(uniform), x, y));
        }

        void Shader::setUniform(const std::string &uniform, float x, float y, float z)
        {
            GL_CHECK(glUniform3f(getUniform(uniform), x, y, z));
        }

        void Shader::setUniform(const std::string &uniform, float x, float y, float z, float w)
        {
            GL_CHECK(glUniform4f(getUniform(uniform), x, y, z, w));
        }

        void Shader::setUniform(const std::string &uniform, const glm::vec2 &vec)
        {
            GL_CHECK(glUniform2fv(getUniform(uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const std::string &uniform, const glm::vec3 &vec)
        {
            GL_CHECK(glUniform3fv(getUniform(uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const std::string &uniform, std::vector<GLuint> vec)
        {
            GL_CHECK(glUniform1iv(getUniform(uniform), static_cast<GLsizei>(vec.size()), (const int*)&vec[0]));
        }

        void Shader::setUniform(const std::string &uniform, const glm::vec4 &vec)
        {
            GL_CHECK(glUniform4fv(getUniform(uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const std::string &uniform, const glm::mat4 &mat)
        {
            GL_CHECK(glUniformMatrix4fv(getUniform(uniform), 1, GL_FALSE, glm::value_ptr(mat)));
        }

        void Shader::setUniform(const GLint &uniform, int i)
        {
            GL_CHECK(glUniform1i((uniform), i));
        }

        void Shader::setUniform(const GLint &uniform, float x)
        {
            GL_CHECK(glUniform1f((uniform), x));
        }

        void Shader::setUniform(const GLint &uniform, float x, float y)
        {
            GL_CHECK(glUniform2f((uniform), x, y));
        }

        void Shader::setUniform(const GLint &uniform, float x, float y, float z)
        {
            GL_CHECK(glUniform3f((uniform), x, y, z));
        }

        void Shader::setUniform(const GLint &uniform, float x, float y, float z, float w)
        {
            GL_CHECK(glUniform4f((uniform), x, y, z, w));
        }

        void Shader::setUniform(const GLint &uniform, const glm::vec2 &vec)
        {
            GL_CHECK(glUniform2fv((uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const GLint &uniform, const glm::vec3 &vec)
        {
            GL_CHECK(glUniform3fv((uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const GLint &uniform, std::vector<GLuint> vec)
        {
            GL_CHECK(glUniform1iv((uniform), static_cast<GLsizei>(vec.size()), (const int*)&vec[0]));
        }

        void Shader::setUniform(const GLint &uniform, const glm::vec4 &vec)
        {
            GL_CHECK(glUniform4fv((uniform), 1, glm::value_ptr(vec)));
        }

        void Shader::setUniform(const GLint &uniform, const glm::mat4 &mat)
        {
            GL_CHECK(glUniformMatrix4fv((uniform), 1, GL_FALSE, glm::value_ptr(mat)));
        }
    }
}
