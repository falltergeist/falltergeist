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
#include <ResourceManager.h>

// Falltergeist includes
#include "../Base/StlFeatures.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Input/Mouse.h"
#include "../Logger.h"
#include "../Settings.h"
#include "../State/State.h"

// Third party includes
#include <glm/gtc/matrix_transform.hpp>

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    _glcontext = SDL_GL_CreateContext(_sdlWindow);

    if (!_glcontext)
    {
        throw Exception(message + "[FAIL]");
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;

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

    glGetIntegerv(GL_MAJOR_VERSION, &_major);
    glGetIntegerv(GL_MINOR_VERSION, &_minor);

    Logger::info("RENDERER") << "Using OpenGL " << _major << "." << _minor << std::endl;
    Logger::info("RENDERER") << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    Logger::info("RENDERER") << "Version: " << glGetString(GL_VERSION) << std::endl;
    Logger::info("RENDERER") << "Vendor: " << glGetString(GL_VENDOR) << std::endl;


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

    GLint count;
    glGetIntegerv( GL_NUM_EXTENSIONS,&count );

    GLint i;
    for (i = 0; i<count; i++)
    {
        Logger::info("RENDERER") << (const char*)glGetStringi( GL_EXTENSIONS, i ) << std::endl;
    }


    Logger::info("RENDERER") << "Loading default shaders" << std::endl;
    ResourceManager::getInstance()->shader("default");
    ResourceManager::getInstance()->shader("sprite");
    ResourceManager::getInstance()->shader("font");
    Logger::info("RENDERER") << "[OK]" << std::endl;

    Logger::info("RENDERER") << "Generating buffers" << std::endl;

    // generate VBOs for verts and tex
    GL_CHECK(glGenVertexArrays(1, &_vao));

    GL_CHECK(glBindVertexArray(_vao));

    GL_CHECK(glGenBuffers(1, &_coord_vbo));
    GL_CHECK(glGenBuffers(1, &_texcoord_vbo));

    // pre-populate texture-coord buffer, because for sprites texture == polygon size
    glm::vec2 uv_up_left    = glm::vec2( 0.0, 0.0 );
    glm::vec2 uv_up_right   = glm::vec2( 1.0, 0.0 );
    glm::vec2 uv_down_right = glm::vec2( 1.0, 1.0 );
    glm::vec2 uv_down_left  = glm::vec2( 0.0, 1.0 );

    std::vector<glm::vec2> UVs;

    UVs.push_back(uv_up_left   );
    UVs.push_back(uv_down_left );
    UVs.push_back(uv_up_right  );
    UVs.push_back(uv_down_right);

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texcoord_vbo));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW));

    // pre-populate element buffer. 6 elements, because we draw as triangles
    GL_CHECK(glGenBuffers(1, &_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GLushort indexes[6] = { 0, 1, 2, 3, 2, 1 };
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indexes, GL_STATIC_DRAW));


    // generate projection matrix
    _MVP = glm::ortho(0.0, (double)_size.width(), (double)_size.height(), 0.0, -1.0, 1.0);



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
    // @fixme: rgb color is not used here
    _inmovie = inmovie;
    _fadeColor.a = 255;
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
    if (!fadeDone())
    {
        //TODO: newrender
    }
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

    /*
void Renderer::drawTexture(Texture* texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    if (!texture) return;
    if (!sourceX && !sourceY && !sourceWidth && !sourceHeight)
    {
        SDL_Rect dest = {(short)x, (short)y, (unsigned short)texture->width(), (unsigned short)texture->height()};
        SDL_RenderCopy(_sdlRenderer, texture->sdlTexture(), NULL, &dest);
    }
    else
    {
        SDL_Rect dest = {(short)x, (short)y, (unsigned short)sourceWidth, (unsigned short)sourceHeight};
        SDL_Rect src = {(short)sourceX, (short)sourceY, (unsigned short)sourceWidth, (unsigned short)sourceHeight};
        SDL_RenderCopy(_sdlRenderer, texture->sdlTexture(), &src, &dest);
    }
}

void Renderer::drawTexture(Texture* texture, const Point& pos, const Point& src, const Size& srcSize)
{
    drawTexture(texture, pos.x(), pos.y(), src.x(), src.y(), (unsigned int)srcSize.width(), (unsigned int)srcSize.height());
}
*/

void Renderer::screenshot()
{
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

GLuint Renderer::getVAO() {
    return _vao;
}

GLuint Renderer::getVVBO() {
    return _coord_vbo;
}

GLuint Renderer::getTVBO() {
    return _texcoord_vbo;
}

glm::mat4 Renderer::getMVP() {
    return _MVP;
}

GLuint Renderer::getEBO() {
    return _ebo;
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, SDL_Color color)
{
    std::vector<glm::vec2> vertices;

    // TODO: scaling
    glm::vec2 start    = glm::vec2( (float)x1, (float)y1);
    glm::vec2 end   = glm::vec2( (float)(x2), (float)y2);
    glm::vec4 fcolor = glm::vec4((float)color.r/255.0f, (float)color.g/255.0f, (float)color.b/255.0f, (float)color.a/255.0f);

    vertices.push_back(start);
    vertices.push_back(end);

    GL_CHECK(ResourceManager::getInstance()->shader("default")->use());

    GL_CHECK(ResourceManager::getInstance()->shader("default")->setUniform("color", fcolor));

    GL_CHECK(ResourceManager::getInstance()->shader("default")->setUniform("MVP", getMVP()));


    GL_CHECK(glBindVertexArray(getVAO()));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("default")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("default")->getAttrib("Position")));

    GL_CHECK(glDrawArrays(GL_LINES, 0, 2));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("default")->getAttrib("Position")));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(ResourceManager::getInstance()->shader("default")->unuse());
}

void Renderer::drawLine(const Point &start, const Point &end, SDL_Color color)
{
    drawLine(start.x(), start.y(), end.x(), end.y(), color);
}

}
}
