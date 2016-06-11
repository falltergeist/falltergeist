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

#ifndef FALLTERGEIST_GRAPHICS_RENDERER_H
#define FALLTERGEIST_GRAPHICS_RENDERER_H

// C++ standard includes
#include <memory>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

// Third party includes
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL.h>

namespace Falltergeist
{
namespace Graphics
{

class Texture;

#define GL_CHECK(x) do { \
    x; \
    int _err = glGetError(); \
    if (_err) { \
        printf("GL Error %d at %d, %s in %s", _err, __LINE__, __func__, __FILE__); \
        exit(-1); \
    } \
} while (0)

class Renderer
{
public:
    enum class RenderPath
    {
        OGL21 = 0,
        OGL32,
        GLES1,
        GLES2
    };

    Renderer(unsigned int width, unsigned int height);
    Renderer(const Size& size);
    ~Renderer();

    void init();

    void beginFrame();
    void endFrame();
    void think();

    int width();
    int height();
    const Size& size() const;

    float scaleX();
    float scaleY();

    bool fadeDone();
    bool fading();

    void fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);
    void fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);

    void setCaption(const std::string& caption);
    SDL_Window* sdlWindow();

    GLuint getVAO();
    GLuint getVVBO();
    GLuint getTVBO();
    GLuint getEBO();
    glm::mat4 getMVP();

    void drawRect(int x, int y, int w, int h, SDL_Color color);
    void drawRect(const Point &pos, const Size &size, SDL_Color color);

    glm::vec4 fadeColor();



//    void drawTexture(Texture* texture, int x, int y, int sourceX = 0, int sourceY = 0, int unsigned sourceWidth = 0, unsigned int sourceHeight = 0);
//    void drawTexture(Texture* texture, const Point& pos, const Point& src = Point(), const Size& srcSize = Size());

    void screenshot();

    int32_t maxTextureSize();

    Texture* egg();

    RenderPath renderPath();

protected:
    Size _size;
    RenderPath _renderpath = RenderPath::OGL21;

    short _fadeStep = 0;
    unsigned int _fadeTimer = 0;
    unsigned int _fadeDelay = 0;
    unsigned int _fadeAlpha = 0;
    bool _fadeDone = true;
    SDL_Color _fadeColor = {0, 0, 0, 0};

    bool _inmovie = false;

    float _scaleX = 1.0;
    float _scaleY = 1.0;

    SDL_Window* _sdlWindow;
    SDL_GLContext _glcontext;
    GLuint _vao;
    GLuint _ebo;
    GLuint _texcoord_vbo;
    GLuint _coord_vbo;
    glm::mat4 _MVP;
    GLint _major;
    GLint _minor;
    int32_t _maxTexSize;

    Texture* _egg;

};

}
}
#endif // FALLTERGEIST_GRAPHICS_RENDERER_H
