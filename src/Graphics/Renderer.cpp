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
#include "../Graphics/Renderer.h"

// C++ standard includes
#include <cmath>
#include <sys/stat.h>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../Base/StlFeatures.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/Point.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/State.h"

// Third party includes
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_image.h>

namespace Falltergeist
{
namespace Graphics
{

using namespace Base;

Renderer::Renderer(unsigned int width, unsigned int height)
{
    _size.setWidth(width);
    _size.setHeight(height);

    std::string message = "Renderer initialization - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        Logger::critical("VIDEO") << message + "[FAIL]" << std::endl;
        throw Exception(SDL_GetError());
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;
}

Renderer::Renderer(const Size& size) : Renderer((unsigned)size.width(), (unsigned)size.height())
{
}

Renderer::~Renderer()
{
    GL_CHECK(glDeleteBuffers(1, &_coord_vbo));
    GL_CHECK(glDeleteBuffers(1, &_texcoord_vbo));
    GL_CHECK(glDeleteBuffers(1, &_ebo));

    GL_CHECK(glDeleteVertexArrays(1, &_vao));
}

void Renderer::init()
{
    // TODO: android/ios
    // _width = deviceWidth;
    // _height = deviceHeight;
    // Game::getInstance()->engineSettings()->setFullscreen(true);
    // Game::getInstance()->engineSettings()->setScale(1); //or 2, if fullhd device

    std::string message =  "SDL_CreateWindow " + std::to_string(_size.width()) + "x" + std::to_string(_size.height()) + "x" +std::to_string(32)+ " - ";

    uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if (Game::getInstance()->settings()->fullscreen())
    {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    _sdlWindow = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _size.width(), _size.height(), flags);
    if (!_sdlWindow)
    {
        throw Exception(message + "[FAIL]");
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;

    message =  "Init OpenGL - ";
    // specifically request 3.2, because fucking Mesa ignores core flag with version < 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    _glcontext = SDL_GL_CreateContext(_sdlWindow);

    if (!_glcontext)
    {
        // ok, try and create 2.1 context then
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        _glcontext = SDL_GL_CreateContext(_sdlWindow);

        if (!_glcontext)
        {
            throw Exception(message + "[FAIL]");
        }
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;
    SDL_GL_SetSwapInterval(0);

/*
 * TODO: newrender
    if (Game::getInstance()->settings()->scale() != 0)
    {
        switch (Game::getInstance()->settings()->scale())
        {
            default:
            case 1:
                _size.setWidth((int)(_size.width() / (_size.height() / 480.0)));
                _size.setHeight(480);
                break;
            case 2:
                _size.setWidth((int)(_size.width() / (_size.height() / 960.0)));
                _size.setHeight(960);
                break;
        }
        SDL_RenderSetLogicalSize(_sdlRenderer, _size.width(), _size.height());
        SDL_RenderGetScale(_sdlRenderer, &_scaleX, &_scaleY);
    }
*/

    char *version_string = (char*)glGetString(GL_VERSION);
    if (version_string[0]-'0' >=3) //we have atleast gl 3.0
    {
        glGetIntegerv(GL_MAJOR_VERSION, &_major);
        glGetIntegerv(GL_MINOR_VERSION, &_minor);
        if (_major==3 && _minor<2) // anything lower 3.2
        {
            _renderpath = RenderPath::OGL21;
        }
        else
        {
            _renderpath = RenderPath::OGL32;
        }
    }
    else
    {
        _major = version_string[0]-'0';
        _minor = version_string[2]-'0';
        _renderpath = RenderPath::OGL21;
    }


    Logger::info("RENDERER") << "Using OpenGL " << _major << "." << _minor << std::endl;
    Logger::info("RENDERER") << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    Logger::info("RENDERER") << "Version string: " << glGetString(GL_VERSION) << std::endl;
    Logger::info("RENDERER") << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    switch (_renderpath)
    {
        case RenderPath::OGL21:
            Logger::info("RENDERER") << "Render path: OpenGL 2.1"  << std::endl;
            break;
        case RenderPath::OGL32:
            Logger::info("RENDERER") << "Render path: OpenGL 3.0+" << std::endl;
            break;
        default:
            break;
    }


    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTexSize);


    message =  "Init GLEW - ";
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    glGetError(); // glew sometimes throws bad enum, so clean it
    if (GLEW_OK != err)
    {
        throw Exception(message + "[FAIL]: " + std::string((char*)glewGetErrorString(err)));
    }
    Logger::info("RENDERER") << message + "[OK]" << std::endl;
    Logger::info("RENDERER") << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    Logger::info("RENDERER") << "Extensions: " << std::endl;

    if (_renderpath==RenderPath::OGL32)
    {
        GLint count;
        glGetIntegerv(GL_NUM_EXTENSIONS, &count);

        GLint i;
        for (i = 0; i < count; i++)
        {
            Logger::info("RENDERER") << (const char *) glGetStringi(GL_EXTENSIONS, i) << std::endl;
        }
    }
    else
    {
        Logger::info("RENDERER") << (const char *) glGetString(GL_EXTENSIONS) << std::endl;
    }


    Logger::info("RENDERER") << "Loading default shaders" << std::endl;
    ResourceManager::getInstance()->shader("default");
    ResourceManager::getInstance()->shader("sprite");
    ResourceManager::getInstance()->shader("font");
    ResourceManager::getInstance()->shader("animation");
    ResourceManager::getInstance()->shader("tilemap");
    ResourceManager::getInstance()->shader("lightmap");
    Logger::info("RENDERER") << "[OK]" << std::endl;

    Logger::info("RENDERER") << "Generating buffers" << std::endl;

    // generate VBOs for verts and tex
    GL_CHECK(glGenVertexArrays(1, &_vao));

    GL_CHECK(glBindVertexArray(_vao));

    GL_CHECK(glGenBuffers(1, &_coord_vbo));
    GL_CHECK(glGenBuffers(1, &_texcoord_vbo));

    // pre-populate element buffer. 6 elements, because we draw as triangles
    GL_CHECK(glGenBuffers(1, &_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GLushort indexes[6] = { 0, 1, 2, 3, 2, 1 };
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indexes, GL_STATIC_DRAW));

    // generate projection matrix
    _MVP = glm::ortho(0.0, (double)_size.width(), (double)_size.height(), 0.0, -1.0, 1.0);

    // load egg
    _egg = ResourceManager::getInstance()->texture("data/egg.png");


}

void Renderer::think()
{
    if (_fadeDone) return;

    unsigned int ticks = SDL_GetTicks();
    if (ticks - _fadeTimer > _fadeDelay)
    {
        _fadeAlpha += _fadeStep;
        if (_fadeAlpha <= 0 || _fadeAlpha > 255)
        {
            _fadeAlpha = (_fadeAlpha <= 0 ? 0 : 255);
            _fadeDone = true;

            auto state = Game::getInstance()->topState();
            state->emitEvent(make_unique<Event::State>("fadedone"), state->fadeDoneHandler());
            return;
        }
        _fadeTimer = ticks;
    }
    _fadeColor.a = _fadeAlpha;
}

bool Renderer::fadeDone()
{
    return _fadeDone && _fadeAlpha == 0;
}

bool Renderer::fading()
{
    return !_fadeDone && !_inmovie;
}

void Renderer::fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie)
{
    _inmovie = inmovie;
    _fadeColor = {r, g, b, 255};
    _fadeAlpha = 255;
    _fadeStep = -1;
    _fadeDone = false;
    _fadeDelay = round(time / 256);
}

void Renderer::fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie)
{
    _inmovie = inmovie;
    _fadeColor = {r, g, b, 0};
    _fadeAlpha = 0;
    _fadeStep = 1;
    _fadeDone = false;
    _fadeDelay = round(time / 256);
}


void Renderer::beginFrame()
{
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL_CHECK(glEnable(GL_BLEND));
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    think();
}

void Renderer::endFrame()
{
    GL_CHECK(glDisable(GL_BLEND));
    SDL_GL_SwapWindow(_sdlWindow);
}

int Renderer::width()
{
    return _size.width();
}

int Renderer::height()
{
    return _size.height();
}

const Size& Renderer::size() const
{
    return _size;
}

void Renderer::screenshot()
{
    std::string filename;
    Uint32 rmask, gmask, bmask, amask;
    SDL_Surface* output;

    int iter = 0;
    do
    {
        std::string siter = std::to_string(iter);
        if(siter.size() < 3)
        {
            siter.insert(0, 3 - siter.size(), '0');
        }
        filename = "screenshot" + siter + ".png";
        iter++;
    }
    while (CrossPlatform::fileExists(filename) && iter < 1000);

    if (CrossPlatform::fileExists(filename))
    {
        Logger::warning("GAME") << "Too many screenshots" << std::endl;
        return;
    }


#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    output = SDL_CreateRGBSurface(0, width(), height(), 32, rmask, gmask, bmask, amask);
    uint8_t *destPixels = (uint8_t*)output->pixels;
    uint8_t *srcPixels = new uint8_t[width() * height() * 4];

    glReadBuffer(GL_BACK);
    glReadPixels(0, 0, width(), height(), GL_RGBA, GL_UNSIGNED_BYTE, srcPixels);

    for(int y=0; y<height(); ++y)
    {
        for(int x=0; x<width(); ++x)
        {
            uint8_t* pDestPix = &destPixels[((width() * y) + x) * 4];
            uint8_t* pSrcPix = &srcPixels[((width() * ((height()-1) - y)) + x) * 4];
            pDestPix[0] = pSrcPix[0];
            pDestPix[1] = pSrcPix[1];
            pDestPix[2] = pSrcPix[2];
            pDestPix[3] = 255;
        }
    }

    IMG_SavePNG(output,filename.c_str());
    delete[] srcPixels;
    SDL_FreeSurface(output);
    Logger::info("GAME") << "Screenshot saved to " + filename << std::endl;

    return;

}

void Renderer::setCaption(const std::string& caption)
{
    SDL_SetWindowTitle(_sdlWindow, caption.c_str());
}

SDL_Window* Renderer::sdlWindow()
{
    return _sdlWindow;
}

float Renderer::scaleX()
{
    return _scaleX;
}

float Renderer::scaleY()
{
    return _scaleY;
}

GLuint Renderer::getVAO()
{
    return _vao;
}

GLuint Renderer::getVVBO()
{
    return _coord_vbo;
}

GLuint Renderer::getTVBO()
{
    return _texcoord_vbo;
}

glm::mat4 Renderer::getMVP()
{
    return _MVP;
}

GLuint Renderer::getEBO()
{
    return _ebo;
}

void Renderer::drawRect(int x, int y, int w, int h, SDL_Color color)
{
    std::vector<glm::vec2> vertices;

    glm::vec4 fcolor = glm::vec4((float)color.r/255.0f, (float)color.g/255.0f, (float)color.b/255.0f, (float)color.a/255.0f);

    vertices.push_back(glm::vec2((float)x, (float)y));
    vertices.push_back(glm::vec2((float)x, (float)y+(float)h));
    vertices.push_back(glm::vec2((float)x+(float)w, (float)y));
    vertices.push_back(glm::vec2((float)x+(float)w, (float)y+(float)h));


    GL_CHECK(ResourceManager::getInstance()->shader("default")->use());

    GL_CHECK(ResourceManager::getInstance()->shader("default")->setUniform("color", fcolor));

    GL_CHECK(ResourceManager::getInstance()->shader("default")->setUniform("MVP", getMVP()));


    GLint curvao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
    GLint vao = getVAO();
    if (curvao != vao)
    {
        GL_CHECK(glBindVertexArray(vao));
    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("default")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::getInstance()->renderer()->getEBO()));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("default")->getAttrib("Position")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("default")->getAttrib("Position")));

}

void Renderer::drawRect(const Point &pos, const Size &size, SDL_Color color)
{
    drawRect(pos.x(), pos.y(), size.width(), size.height(), color);
}

glm::vec4 Renderer::fadeColor()
{
    return glm::vec4((float)_fadeColor.r/255.0, (float)_fadeColor.g/255.0, (float)_fadeColor.b/255.0, (float)_fadeColor.a/255.0);
}

int32_t Renderer::maxTextureSize()
{
    return 1024;
    return _maxTexSize;
}

Texture *Renderer::egg()
{
    return _egg;
}

Renderer::RenderPath Renderer::renderPath()
{
    return _renderpath;
}

}
}
