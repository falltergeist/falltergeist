/*
 * Copyright 2012-2015 Falltergeist Developers.
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

    uint32_t flags = SDL_WINDOW_SHOWN;
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

    message =  "SDL_CreateRenderer - ";
    _sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!_sdlRenderer)
    {
        throw Exception(message + "[FAIL]");
    }

    Logger::info("RENDERER") << message + "[OK]" << std::endl;

    SDL_SetRenderDrawBlendMode(_sdlRenderer, SDL_BLENDMODE_BLEND);

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

    SDL_RendererInfo rendererInfo;
    SDL_GetRendererInfo(_sdlRenderer, &rendererInfo);

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
    SDL_RenderClear(_sdlRenderer);
    think();
}

void Renderer::endFrame()
{
    if (!fadeDone())
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(_sdlRenderer, &color.r, &color.g, &color.b, &color.a);
        SDL_SetRenderDrawColor(_sdlRenderer, _fadeColor.r, _fadeColor.g, _fadeColor.b, _fadeColor.a);
        SDL_RenderFillRect(_sdlRenderer, NULL);
        SDL_SetRenderDrawColor(_sdlRenderer, color.r, color.g, color.b, color.a);
    }
    SDL_RenderPresent(_sdlRenderer);
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

std::unique_ptr<Texture> Renderer::screenshot()
{
    SDL_Surface* window = SDL_GetWindowSurface(sdlWindow());
    if (!window)
    {
        throw Exception(SDL_GetError());
    }

    std::unique_ptr<Texture> texture(new Texture(window->w, window->h));
    auto surface = texture->sdlSurface();
    SDL_RenderReadPixels(_sdlRenderer, NULL, surface->format->format, surface->pixels, surface->pitch);
    SDL_FreeSurface(window);
    return texture;
}

std::string Renderer::name()
{
    return _name;
}

void Renderer::setCaption(const std::string& caption)
{
    SDL_SetWindowTitle(_sdlWindow, caption.c_str());
}

SDL_Window* Renderer::sdlWindow()
{
    return _sdlWindow;
}

SDL_Renderer* Renderer::sdlRenderer()
{
    return _sdlRenderer;
}

float Renderer::scaleX()
{
    return _scaleX;
}

float Renderer::scaleY()
{
    return _scaleY;
}

}
}
