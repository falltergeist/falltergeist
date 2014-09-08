/*
 * Copyright 2012-2014 Falltergeist Developers.
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

// C++ standard includes
#include <iostream>

// Falltergeist includes
#include "../../Engine/Graphics/OpenGLRenderer.h"
#include "../../Engine/CrossPlatform.h"
#include "../../Engine/Exception.h"
#include "../../Engine/ResourceManager.h"
#include "../../Engine/Game.h"
#include "../../Engine/Font.h"

// Third party includes
#include "SDL.h"
#include "GL/gl.h"
#include "GL/glu.h"

namespace Falltergeist
{

OpenGLRenderer::OpenGLRenderer(unsigned int width, unsigned int height) : Renderer(width, height)
{
    std::string message = "[VIDEO] - OpenGL Renderer initialization - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        debug(message + "[FAIL]", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
    debug(message + "[OK]", DEBUG_INFO);

}

void OpenGLRenderer::init()
{
    Renderer::init();

    std::string message =  "[VIDEO] - SDL_SetVideoMode " + std::to_string(_width) + "x" + std::to_string(_height) + "x" +std::to_string(32)+ " - ";
    if (!SDL_SetVideoMode(_width, _height, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL))
    {
        throw Exception(message + "[FAIL]");
    }
    debug(message + "[OK]", DEBUG_INFO);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, _width, _height);

    // OpenGL initialization
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // black and opaque

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, _width, _height, 0, 0.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.375, 0.375, 0);
}

void OpenGLRenderer::beginFrame()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Renderer::beginFrame();
}

void OpenGLRenderer::endFrame()
{
    Renderer::endFrame();
    SDL_GL_SwapBuffers();
}

void OpenGLRenderer::registerTexture(Texture* texture)
{
    Renderer::registerTexture(texture);
    if (texture->id()) return; // if registered

    unsigned int textureId;
    glGenTextures(1, &textureId);
    texture->setId(textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, texture->width(), texture->height(), 0);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->width(), texture->height(), GL_ABGR_EXT, GL_UNSIGNED_BYTE, texture->data());

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture->width(), texture->height(), GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texture->data());

    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture( GL_TEXTURE_2D, 0);

}

void OpenGLRenderer::unregisterTexture(Texture* texture)
{
    if (!texture->id()) return;

    GLuint textureId = texture->id();
    glDeleteTextures(1, &textureId);
    texture->setId(0);
}

void OpenGLRenderer::drawTexture(unsigned int x, unsigned int y, Texture* texture)
{
    Renderer::drawTexture(x, y, texture);
    if (!texture->id()) registerTexture(texture);

    glBindTexture( GL_TEXTURE_2D, texture->id());
    glBegin(GL_POLYGON);
         glTexCoord2i(0, 0);
         glVertex2i(x, y);

         glTexCoord2i(1, 0);
         glVertex2i(x + texture->width(), y);

         glTexCoord2i(1, 1);
         glVertex2i(x + texture->width(), y + texture->height());

         glTexCoord2i(0, 1);
         glVertex2i(x, y + texture->height());
    glEnd();
}

}
