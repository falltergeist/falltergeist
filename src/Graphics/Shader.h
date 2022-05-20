#pragma once

#include <map>
#include <string>
#include <vector>
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

                Shader(const std::string& fname);

                ~Shader();

                void use() const;

                void unuse();

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

                bool _load(const std::string& fname);
                mutable std::map<std::string, GLint> _uniforms;
                mutable std::map<std::string, GLint> _attribs;
        };
    }
}
