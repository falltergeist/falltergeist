#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <CrossPlatform.h>
#include <Logger.h>
#include <fstream>

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
                Logger::warning("RENDERER") << "Failed to compile shader: '" << log << std::endl;
                free(log);
                shader = 0;
            }
            return shader;
        }


        bool Shader::_load(std::string fname) {
            _progId = 0;

            std::string fprog = std::string(CrossPlatform::findFalltergeistDataPath() + "/" +fname+".fp");
            std::string vprog = std::string(CrossPlatform::findFalltergeistDataPath() + "/" +fname+".vp");

            std::ifstream fpfile(fprog);
            std::ifstream vpfile(vprog);

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
                    return false;
                }
            return true;
        }

        void Shader::use() {
            glUseProgram(_progId);
        }

        void Shader::unuse() {
            glUseProgram(0);
        }

        GLuint Shader::id() {
            return _progId;
        }

        GLint Shader::getUniform(const std::string &uniform) const {
            auto it = _uniforms.find(uniform);

            if (it == _uniforms.end()) {
                GLint loc = glGetUniformLocation(_progId, uniform.c_str());
                if (loc == -1)
                    Logger::warning("RENDERER") << "Attention: uniform '" << uniform << "' does not exist in " << _progId << std::endl;

                _uniforms[uniform] = loc;
                return loc;
            }
            else return it->second;
        }

        GLint Shader::getAttrib(const std::string &attrib) const {
            auto it = _attribs.find(attrib);

            if (it == _attribs.end()) {
                GLint loc = glGetAttribLocation(_progId, attrib.c_str());
                if (loc == -1)
                    Logger::warning("RENDERER") << "Attention: attrib '" << attrib << "' does not exist in " << _progId << std::endl;


                _attribs[attrib] = loc;
                return loc;
            }
            else return it->second;
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

        void Shader::setUniform(const std::string &uniform, const glm::vec4 &vec) {
            glUniform4fv(getUniform(uniform), 1, glm::value_ptr(vec));
        }

        void Shader::setUniform(const std::string &uniform, const glm::mat4 &mat) {
            glUniformMatrix4fv(getUniform(uniform), 1, GL_FALSE, glm::value_ptr(mat));
        }


    }
}