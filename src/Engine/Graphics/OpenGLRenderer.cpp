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

// Falltergeist includes
#include "../../Engine/Exception.h"
#include "../../Engine/Font.h"
#include "../../Engine/Game.h"
#include "../../Engine/Graphics/OpenGLRenderer.h"
#include "../../Engine/Logger.h"
#include "../../Engine/ResourceManager.h"

// Third party includes
#include "SDL.h"
#ifndef __APPLE__
    #include "GL/gl.h"
    #include "GL/glu.h"
#else
    #include "OpenGL/gl.h"
    #include "OpenGL/glu.h"
#endif

namespace Falltergeist
{

int NearestPowerOf2(int n) {
    if (!n) return n; //(0 == 2^0)
    int x = 1;
    while (x < n) {
        x <<= 1;
    }
    return x;
}

OpenGLRenderer::OpenGLRenderer(unsigned int width, unsigned int height) : Renderer(width, height)
{
    std::string message = "OpenGL Renderer initialization - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        Logger::critical("VIDEO") << message + "[FAIL]" << std::endl;
        throw Exception(SDL_GetError());
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;

}

void OpenGLRenderer::init()
{
    Renderer::init();

    std::string message =  "SDL_CreateWindow " + std::to_string(_width) + "x" + std::to_string(_height) + "x" +std::to_string(32)+ " - ";
    _window = SDL_CreateWindow("",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!_window)
    {
        throw Exception(message + "[FAIL]");
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;

    message =  "SDL_GL_CreateContext - ";
    _context = SDL_GL_CreateContext(_window);
    if (!_context)
    {
        throw Exception(message + "[FAIL]");
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
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
    SDL_GL_SwapWindow(_window);
}

void OpenGLRenderer::registerTexture(std::shared_ptr<Texture> texture)
{
    Renderer::registerTexture(texture);
    if (texture->id()) return; // if registered

    unsigned int textureId;
    glGenTextures(1, &textureId);
    texture->setId(textureId);

    int bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_RGBA8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    SDL_Surface* resizedSurf = NULL;
    SDL_Rect area;

    //SDL_Surface* tmpSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, texture->width(), texture->height(), 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    SDL_Surface* tmpSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, texture->width(), texture->height(), 32, Rmask, Gmask, Bmask, Amask);
    if (tmpSurface == 0) throw Exception(SDL_GetError());
    // Copying data from texture to surface
    unsigned int* pixels = (unsigned int*) tmpSurface->pixels;
    for (unsigned int i = 0; i != texture->width()*texture->height(); ++i)
    {
        pixels[i] = texture->data()[i];
    }

    int newH = NearestPowerOf2(texture->height());
    int newW = NearestPowerOf2(texture->width());

    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_ABGR8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    resizedSurf = SDL_CreateRGBSurface(0, newW, newH, bpp, Rmask, Gmask, Bmask, Amask);
    area.x = 0;
    area.y = 0;
    area.w = tmpSurface->w;
    area.h = tmpSurface->h;
    SDL_SetSurfaceAlphaMod( tmpSurface, 0xFF );
    SDL_SetSurfaceBlendMode( tmpSurface, SDL_BLENDMODE_NONE );
    SDL_BlitSurface(tmpSurface, &area, resizedSurf, &area);

    glBindTexture(GL_TEXTURE_2D, textureId);

    //glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, texture->width(), texture->height(), 0);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture->width(), texture->height(), GL_ABGR_EXT, GL_UNSIGNED_BYTE, texture->data());

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resizedSurf->w, resizedSurf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, resizedSurf->pixels);
    //gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texture->width(), texture->height(), GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, texture->data());

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture( GL_TEXTURE_2D, 0);
    texture->texWidth(newW);
    texture->texHeight(newH);
}

void OpenGLRenderer::unregisterTexture(Texture* texture)
{
    if (!texture->id()) return;

    GLuint textureId = texture->id();
    glDeleteTextures(1, &textureId);
    texture->setId(0);
}

void OpenGLRenderer::drawTexture(std::shared_ptr<Texture> texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    Renderer::drawTexture(texture, x, y);
    if (!texture->id()) registerTexture(texture);

    glBindTexture( GL_TEXTURE_2D, texture->id());
    glBegin(GL_POLYGON);
         glTexCoord2i(0, 0);
         glVertex2i(x, y);

         glTexCoord2i(1, 0);
         glVertex2i(x + texture->texWidth(), y);

         glTexCoord2i(1, 1);
         glVertex2i(x + texture->texWidth(), y + texture->texHeight());

         glTexCoord2i(0, 1);
         glVertex2i(x, y + texture->texHeight());
    glEnd();
}

std::shared_ptr<Texture> OpenGLRenderer::screenshot()
{
    unsigned int width = Game::getInstance()->renderer()->width();
    unsigned int height = Game::getInstance()->renderer()->height();

    // get current masks (they are different for LE and BE)
    int bpp;
    uint32_t Rmask, Gmask, Bmask, Amask;
    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_RGBA8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    // Read data from screen
    SDL_Surface* flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, Rmask, Gmask, Bmask, Amask);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, flipped->pixels);

    // Flip image verticaly
    SDL_Surface* surface = SDL_CreateRGBSurface(flipped->flags, flipped->w, flipped->h, 32, flipped->format->Rmask, flipped->format->Gmask,flipped->format->Bmask, flipped->format->Amask);
    if(SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

    for(int x = 0; x < surface->w; x++)
    {
        for(int y = 0, ry = surface->h - 1; y < surface->h; y++, ry--)
        {
            ((unsigned int*)surface->pixels)[(ry*surface->w) + x ] = ((unsigned int*)flipped->pixels)[(y*flipped->w) + x];
        }
    }
    if(SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

    auto texture = std::shared_ptr<Texture>(new Texture(width, height));
    texture->loadFromRGBA((unsigned int*)surface->pixels);

    SDL_FreeSurface(flipped);
    SDL_FreeSurface(surface);

    return texture;
}

std::string OpenGLRenderer::name()
{
    return _name;
}


}
