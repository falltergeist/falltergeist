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
#include <string>

// Falltergeist includes
#include "../../Engine/Exception.h"
#include "../../Engine/Game.h"
#include "../../Engine/Graphics/SDLRenderer.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Settings/Settings.h"

//Third party includes
#include "SDL.h"

namespace Falltergeist
{

SDLRenderer::SDLRenderer(unsigned int width, unsigned int height) : Renderer(width, height)
{
    std::string message = "SDL Renderer initialization - ";
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        Logger::critical("VIDEO") << message + "[FAIL]" << std::endl;
        throw Exception(SDL_GetError());
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;
}

SDLRenderer::~SDLRenderer()
{
}

void SDLRenderer::init()
{
    Renderer::init();

    // TODO: android/ios
    // _width = deviceWidth;
    // _height = deviceHeight;
    // Game::getInstance()->engineSettings()->setFullscreen(true);
    // Game::getInstance()->engineSettings()->setScale(1); //or 2, if fullhd device

    std::string message =  "SDL_CreateWindow " + std::to_string(_width) + "x" + std::to_string(_height) + "x" +std::to_string(32)+ " - ";
    if (Game::getInstance()->engineSettings()->fullscreen())
    {
        _window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        _window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
    }
    if (!_window)
    {
        throw Exception(message + "[FAIL]");
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;

    message =  "SDL_CreateRenderer - ";
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
    {
        throw Exception(message + "[FAIL]");
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;

    if (Game::getInstance()->engineSettings()->scale() != 0)
    {
        switch (Game::getInstance()->engineSettings()->scale())
        {
            default:
            case 1:
                _width = _width / (_height / 480.0);
                _height= 480;
                break;
            case 2:
                _width = _width / (_height / 960.0);
                _height= 960;
                break;
        }
        SDL_RenderSetLogicalSize(_renderer, _width, _height);
        SDL_RenderGetScale(_renderer, &_scaleX, &_scaleY);
    }

    SDL_RendererInfo rendererInfo;
    SDL_GetRendererInfo(_renderer, &rendererInfo);

    Logger::info("RENDERER") << "name: " << rendererInfo.name << std::endl;
    if (rendererInfo.flags & SDL_RENDERER_SOFTWARE)
    {
        Logger::info("RENDERER") << "flags: SDL_RENDERER_SOFTWARE" << std::endl;
    }
    if (rendererInfo.flags & SDL_RENDERER_ACCELERATED)
    {
        Logger::info("RENDERER") << "flags: SDL_RENDERER_ACCELERATED" << std::endl;
    }
    Logger::info("RENDERER") << "num_texture_formats: " << rendererInfo.num_texture_formats << std::endl;
    for (unsigned int i = 0; i != 16; i++)
    {
        auto& info = Logger::info("RENDERER");
        info << "texture_formats[" << i << "]: ";
        auto format = rendererInfo.texture_formats[i];

        switch (format)
        {
            case SDL_PIXELFORMAT_INDEX1LSB:
                info << "SDL_PIXELFORMAT_INDEX1LSB";
                break;
            case SDL_PIXELFORMAT_INDEX1MSB:
                info << "SDL_PIXELFORMAT_INDEX1MSB";
                break;
            case SDL_PIXELFORMAT_INDEX4LSB:
                info << "SDL_PIXELFORMAT_INDEX4LSB";
                break;
            case SDL_PIXELFORMAT_INDEX4MSB:
                info << "SDL_PIXELFORMAT_INDEX4MSB";
                break;
            case SDL_PIXELFORMAT_INDEX8:
                info << "SDL_PIXELFORMAT_INDEX8";
                break;
            case SDL_PIXELFORMAT_RGBA8888:
                info << "SDL_PIXELFORMAT_RGBA8888";
                break;
            case SDL_PIXELFORMAT_ARGB8888:
                info << "SDL_PIXELFORMAT_ARGB8888";
                break;
            case SDL_PIXELFORMAT_RGB888:
                info << "SDL_PIXELFORMAT_RGB888";
                break;
            default:
                info << format;
                break;
        }
        info << std::endl;
    }
    Logger::info("RENDERER") << "max_texture_width: " << rendererInfo.max_texture_width << std::endl;
    Logger::info("RENDERER") << "max_texture_height: " << rendererInfo.max_texture_height << std::endl;
}

void SDLRenderer::beginFrame()
{
    SDL_RenderClear(_renderer);
    Renderer::beginFrame();
}

void SDLRenderer::endFrame()
{
    Renderer::endFrame();
    if (!fadeDone())
    {
        uint8_t        r,g,b,a;
        SDL_GetRenderDrawColor(_renderer,&r,&g,&b,&a);
        SDL_SetRenderDrawBlendMode(_renderer,SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(_renderer, _fadeColor.r,_fadeColor.g, _fadeColor.b,_fadeColor.a);
        SDL_RenderFillRect(_renderer, NULL);
        SDL_SetRenderDrawColor(_renderer, r, g, b, a);
    }
    SDL_RenderPresent(_renderer);
}

void SDLRenderer::registerTexture(Texture* texture)
{
    Renderer::registerTexture(texture);
    if (texture->id()) return; // if registered

    SDL_Texture* sdlTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, texture->width(), texture->height());
    if (sdlTexture == 0) throw Exception(SDL_GetError());

    SDL_UpdateTexture(sdlTexture, NULL, texture->data(), texture->width() * 4);
    _surfaces.push_back(sdlTexture);

    SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);

    texture->setId(_texturesCounter);
    _texturesCounter++;
}

void SDLRenderer::unregisterTexture(Texture* texture)
{
    if (!texture->id()) return;

    SDL_DestroyTexture(_surfaces.at(texture->id() - 1));
    _surfaces.at(texture->id() -1) = 0;
    texture->setId(0);
}

void SDLRenderer::drawTexture(Texture* texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
{
    Renderer::drawTexture(texture, x, y);

    if (!texture->id()) registerTexture(texture);

    if (!sourceX && !sourceY && !sourceWidth && !sourceHeight)
    {
        SDL_Rect dest = {(short)x, (short)y, (unsigned short)texture->width(), (unsigned short)texture->height()};
        SDL_RenderCopy(_renderer, _surfaces.at(texture->id() - 1), NULL, &dest);
    }
    else
    {
        SDL_Rect dest = {(short)x, (short)y, (unsigned short)sourceWidth, (unsigned short)sourceHeight};
        SDL_Rect src = {(short)sourceX, (short)sourceY, (unsigned short)sourceWidth, (unsigned short)sourceHeight};
        SDL_RenderCopy(_renderer, _surfaces.at(texture->id() - 1), &src, &dest);
    }
}

Texture* SDLRenderer::screenshot()
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

    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, Rmask, Gmask, Bmask, Amask);
    SDL_RenderReadPixels(_renderer, NULL, surface->format->format, surface->pixels, surface->pitch);

    auto texture = new Texture(width, height);
    texture->loadFromRGBA((unsigned int*)surface->pixels);

    SDL_FreeSurface(surface);

    return texture;
}

std::string SDLRenderer::name()
{
    return _name;
}

}
