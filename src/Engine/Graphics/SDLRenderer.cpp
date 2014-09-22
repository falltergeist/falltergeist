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

void SDLRenderer::init()
{
    Renderer::init();

    std::string message =  "SDL_CreateWindow " + std::to_string(_width) + "x" + std::to_string(_height) + "x" +std::to_string(32)+ " - ";
    _window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, SDL_WINDOW_SHOWN);
    if (!_window)
    {
        throw Exception(message + "[FAIL]");
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;

    message =  "SDL_CreateRenderer - ";
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer)
    {
        throw Exception(message + "[FAIL]");
    }
    Logger::info("VIDEO") << message + "[OK]" << std::endl;
}

void SDLRenderer::beginFrame()
{
    SDL_RenderClear(_renderer);
    Renderer::beginFrame();
}

void SDLRenderer::endFrame()
{
    Renderer::endFrame();
    SDL_RenderPresent(_renderer);
}

void SDLRenderer::registerTexture(std::shared_ptr<Texture> texture)
{
    Renderer::registerTexture(texture);
    if (texture->id()) return; // if registered

    // get current masks (they are different for LE and BE)
    int bpp;
    uint32_t Rmask, Gmask, Bmask, Amask;
    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_ABGR8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    // Creating SDL surface
    SDL_Surface* tmpSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, texture->width(), texture->height(), 32, Rmask, Gmask, Bmask, Amask);
    if (tmpSurface == 0) throw Exception(SDL_GetError());
    // Copying data from texture to surface
    unsigned int* pixels = (unsigned int*) tmpSurface->pixels;
    for (unsigned int i = 0; i != texture->width()*texture->height(); ++i)
    {
        pixels[i] = texture->data()[i];
    }
    // Saving pointer to surface
    SDL_Texture* surface = SDL_CreateTextureFromSurface(_renderer, tmpSurface);
    if (surface == 0) throw Exception(SDL_GetError());
    SDL_FreeSurface(tmpSurface);
    _surfaces.push_back(surface);

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

void SDLRenderer::drawTexture(unsigned int x, unsigned int y, std::shared_ptr<Texture> texture)
{
    Renderer::drawTexture(x, y, texture);

    if (!texture->id()) registerTexture(texture);

    SDL_Rect dest = {(short)x, (short)y, (unsigned short)texture->width(), (unsigned short)texture->height()};
    SDL_RenderCopy(_renderer, _surfaces.at(texture->id() - 1), NULL, &dest);
}

std::shared_ptr<Texture> SDLRenderer::screenshot()
{
    unsigned int width = Game::getInstance()->renderer()->width();
    unsigned int height = Game::getInstance()->renderer()->height();

    // get current masks (they are different for LE and BE)
    int bpp;
    uint32_t Rmask, Gmask, Bmask, Amask;
    SDL_PixelFormatEnumToMasks(
        SDL_PIXELFORMAT_ABGR8888, &bpp,
        &Rmask, &Gmask, &Bmask, &Amask
    );

    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, Rmask, Gmask, Bmask, Amask);
    SDL_RenderReadPixels(_renderer, NULL, surface->format->format, surface->pixels, surface->pitch);

    auto texture = std::shared_ptr<Texture>(new Texture(width, height));
    texture->loadFromRGBA((unsigned int*)surface->pixels);

    SDL_FreeSurface(surface);

    return texture;
}

std::string SDLRenderer::name()
{
    return _name;
}

}
