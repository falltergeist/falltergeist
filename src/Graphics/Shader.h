#ifndef _CSHADER_H_
#define _CSHADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>

namespace Falltergeist {
    namespace Graphics {


        class Shader {

        private:

            GLuint _progId;

            GLuint _loadShader(const char *, unsigned int);

            std::vector<GLuint> _shaders;

            bool _load(std::string fname);

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

            void setUniform(const std::string &uniform, const glm::vec4 &vec);

            void setUniform(const std::string &uniform, const glm::mat4 &mat);

            GLint getAttrib(const std::string &attrib) const;

            GLint getUniform(const std::string &uniform) const;

        private:
            mutable std::map<std::string, GLint> _uniforms;
            mutable std::map<std::string, GLint> _attribs;
        };
    }
}
#endif
